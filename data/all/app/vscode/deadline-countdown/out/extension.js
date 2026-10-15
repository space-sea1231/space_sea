"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.activate = activate;
exports.deactivate = deactivate;
/**
 * DEADLINE · VSCode 背景倒计时  v0.3.2
 * ==================================================================
 *  v0.3.2 修复：
 *   1. 倒计时向右偏移：CSS 宽度由 100vw 改为 100%，贴合编辑器区域；
 *   2. 高频闪烁：定时器 250ms→1000ms，并加入渲染指纹去重；
 *   3. 滚动时闪烁：滚动事件加防抖，滚动过程中不重绘，
 *      停下 120ms 后重绘一次，位置仍随视口居中。
 * ==================================================================
 */
const vscode = require("vscode");
const KEY_TARGET = 'deadline.target';
const KEY_MINUTES = 'deadline.lastMinutes';
let targetTime = 0;
let pausedRemain = 0;
let lastMinutes = 25;
let notified = false;
let overlay;
let statusBar;
let ticker;
let panel;
let ext;
// ★ 渲染指纹与状态栏文本去重缓存
let lastRenderKey = '';
let lastStatusText = '';
// ★ 滚动防抖定时器
let renderTimer;
function scheduleRender(delay) {
    if (renderTimer)
        clearTimeout(renderTimer);
    renderTimer = setTimeout(() => {
        renderTimer = undefined;
        render();
    }, delay);
}
function activate(context) {
    ext = context;
    targetTime = context.globalState.get(KEY_TARGET, 0);
    lastMinutes = context.globalState.get(KEY_MINUTES, 25);
    statusBar = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left, 100);
    statusBar.name = 'DEADLINE';
    statusBar.command = 'deadline.settings';
    statusBar.tooltip = 'DEADLINE · 点击打开设置面板';
    context.subscriptions.push(statusBar, vscode.commands.registerCommand('deadline.settings', () => openPanel()), vscode.commands.registerCommand('deadline.start', () => promptMinutes()), vscode.commands.registerCommand('deadline.at', () => promptClock()), vscode.commands.registerCommand('deadline.toggle', () => toggle()), vscode.commands.registerCommand('deadline.stop', () => stop()), vscode.window.onDidChangeActiveTextEditor(() => render()), 
    // ★ 滚动时防抖：滚动过程中不重绘，停下 120ms 后才重绘一次，消除闪烁
    vscode.window.onDidChangeTextEditorVisibleRanges(() => scheduleRender(120)), vscode.window.onDidChangeTextEditorOptions(() => render()), vscode.workspace.onDidChangeConfiguration((e) => {
        if (e.affectsConfiguration('deadline'))
            render();
    }), {
        dispose: () => {
            if (ticker)
                clearInterval(ticker);
            // ★ 清理防抖定时器
            if (renderTimer) {
                clearTimeout(renderTimer);
                renderTimer = undefined;
            }
            clearOverlay();
            panel?.dispose();
        },
    });
    // ★ 250ms → 1000ms，倒计时按秒显示
    ticker = setInterval(tick, 1000);
    tick();
}
/* ==================================================================
 *  计时状态机
 * ================================================================== */
function remaining() {
    if (pausedRemain > 0)
        return pausedRemain;
    return targetTime > 0 ? targetTime - Date.now() : 0;
}
function tick() {
    if (targetTime > 0 && pausedRemain === 0 && targetTime - Date.now() <= 0) {
        targetTime = 0;
        void ext?.globalState.update(KEY_TARGET, 0);
        if (!notified) {
            notified = true;
            void onFinish();
        }
    }
    render();
    syncPanel();
}
function start(minutes) {
    lastMinutes = minutes;
    pausedRemain = 0;
    notified = false;
    targetTime = Date.now() + Math.round(minutes * 60000);
    void ext?.globalState.update(KEY_TARGET, targetTime);
    void ext?.globalState.update(KEY_MINUTES, lastMinutes);
    render();
    syncPanel();
}
function toggle() {
    if (pausedRemain > 0) {
        targetTime = Date.now() + pausedRemain;
        pausedRemain = 0;
    }
    else if (targetTime > Date.now()) {
        pausedRemain = targetTime - Date.now();
        targetTime = 0;
    }
    else {
        void promptMinutes();
        return;
    }
    void ext?.globalState.update(KEY_TARGET, targetTime);
    render();
    syncPanel();
}
function stop() {
    targetTime = 0;
    pausedRemain = 0;
    notified = false;
    void ext?.globalState.update(KEY_TARGET, 0);
    clearOverlay();
    lastRenderKey = '';
    lastStatusText = '';
    if (statusBar)
        statusBar.hide();
    syncPanel();
}
async function onFinish() {
    const pick = await vscode.window.showWarningMessage('⏰ DEADLINE · 时间到！', '再来 ' + lastMinutes + ' 分钟', '知道了');
    if (pick === '再来 ' + lastMinutes + ' 分钟')
        start(lastMinutes);
    else
        stop();
}
/* ==================================================================
 *  核心渲染
 * ================================================================== */
function render() {
    const cfg = vscode.workspace.getConfiguration('deadline');
    const remain = Math.max(0, remaining());
    const editor = vscode.window.activeTextEditor;
    const mode = cfg.get('mode', 'watermark');
    const isCover = mode === 'cover';
    const urgentSec = cfg.get('urgentSeconds', 60);
    const urgent = remain > 0 && remain <= urgentSec * 1000;
    updateStatusBar(cfg, remain, urgent);
    if (!editor || remain <= 0) {
        clearOverlay();
        lastRenderKey = '';
        return;
    }
    const text = format(remain);
    const dim = pausedRemain > 0 ? 0.55 : 1;
    const opacity = (isCover ? 1 : clamp(cfg.get('opacity', 0.12), 0.02, 1)) * dim;
    const size = clamp(cfg.get('fontSizeVw', 12), 3, 40);
    const userDx = cfg.get('offsetX', 0);
    const userDy = cfg.get('offsetY', 0);
    const themeColor = cfg.get('color', '');
    const color = urgent
        ? cfg.get('urgentColor', '#f87171')
        : themeColor || (isCover ? 'rgba(255,255,255,0.94)' : '');
    const scrim = clamp(cfg.get('coverDim', 0.55), 0, 1);
    const image = asUrl(cfg.get('image', ''));
    // 视口几何中心计算
    const vr = editor.visibleRanges[0];
    const docLines = editor.document.lineCount;
    const viewportSpan = vr ? Math.max(1, vr.end.line - vr.start.line) : 28;
    const halfSpan = Math.floor(viewportSpan / 2);
    const estLineHeight = 20;
    let anchorLine = 0;
    let verticalCompensationPx = 0;
    if (vr) {
        if (docLines > halfSpan) {
            anchorLine = Math.min(docLines - 1, vr.start.line + halfSpan);
            verticalCompensationPx = 0;
        }
        else {
            anchorLine = Math.max(0, docLines - 1);
            const missingLines = Math.max(0, halfSpan - anchorLine);
            verticalCompensationPx = missingLines * estLineHeight;
        }
    }
    const finalDy = userDy + verticalCompensationPx;
    const safeLine = Math.min(Math.max(0, anchorLine), docLines - 1);
    // ★ 渲染指纹：内容/位置/样式全部没变则跳过重建，消除闪烁
    const renderKey = [
        text, safeLine, userDx, finalDy,
        opacity.toFixed(3), size, color, isCover, scrim.toFixed(2), image,
        editor.document.uri.toString(),
    ].join('|');
    if (renderKey === lastRenderKey && overlay) {
        return;
    }
    lastRenderKey = renderKey;
    clearOverlay();
    const css = ";content:'" + text + "';" +
        ' position:absolute;' +
        // ★ 100vw → 100%，贴合编辑器宽度，修复向右偏移
        ' top:50%; left:0; width:100%; box-sizing:border-box;' +
        ' transform:translate(' + userDx + 'px, calc(-50% + ' + finalDy + 'px));' +
        ' display:flex; align-items:center; justify-content:center;' +
        ' white-space:nowrap; line-height:1; pointer-events:none;' +
        ' font-size:' + size + 'vw; font-weight:700; letter-spacing:0.06em;' +
        ' font-variant-numeric:tabular-nums;' +
        ' opacity:' + opacity.toFixed(3) + ';' +
        ' text-shadow:0 6px 48px rgba(0,0,0,0.45);' +
        (color ? ' color:' + color + ';' : '') +
        (isCover
            ? ' height:100vh; background-color:#020617;' +
                ' background-image:linear-gradient(rgba(2,6,23,' + scrim.toFixed(2) + '),' +
                'rgba(2,6,23,' + scrim.toFixed(2) + '))' +
                (image
                    ? ",url('" + image + "')"
                    : ',radial-gradient(1200px 520px at 50% 38%,rgba(34,211,238,0.14),transparent 70%),' +
                        'radial-gradient(900px 420px at 78% 82%,rgba(129,140,248,0.14),transparent 70%)') +
                '; background-size:cover; background-position:center; background-repeat:no-repeat;'
            : '');
    overlay = vscode.window.createTextEditorDecorationType({
        before: { contentText: text, textDecoration: css },
        rangeBehavior: vscode.DecorationRangeBehavior.ClosedClosed,
    });
    editor.setDecorations(overlay, [new vscode.Range(safeLine, 0, safeLine, 0)]);
}
function clearOverlay() {
    if (overlay) {
        overlay.dispose();
        overlay = undefined;
    }
}
function updateStatusBar(cfg, remain, urgent) {
    const sb = statusBar;
    if (!sb)
        return;
    if (!cfg.get('showStatusBar', true) || remain <= 0) {
        sb.hide();
        lastStatusText = '';
        return;
    }
    // ★ 文本去重：内容没变就不重新赋值，消除状态栏闪烁
    const next = (pausedRemain > 0 ? '$(debug-pause) ' : '$(watch) ') + format(remain);
    if (next !== lastStatusText) {
        sb.text = next;
        lastStatusText = next;
    }
    sb.tooltip = 'DEADLINE · 点击打开设置面板';
    sb.backgroundColor = urgent
        ? new vscode.ThemeColor('statusBarItem.warningBackground')
        : undefined;
    sb.show();
}
/* ==================================================================
 *  设置窗口（Webview 面板）
 * ================================================================== */
function openPanel() {
    if (panel) {
        panel.reveal(vscode.ViewColumn.Beside);
        syncPanel();
        return;
    }
    panel = vscode.window.createWebviewPanel('deadline.settings', 'DEADLINE · 设置', vscode.ViewColumn.Beside, { enableScripts: true, retainContextWhenHidden: true });
    panel.webview.html = panelHtml();
    panel.webview.onDidReceiveMessage((msg) => void onPanelMessage(msg));
    panel.onDidDispose(() => { panel = undefined; });
    syncPanel();
}
async function onPanelMessage(msg) {
    switch (msg.type) {
        case 'start':
            if (msg.minutes && msg.minutes > 0)
                start(msg.minutes);
            break;
        case 'at':
            if (msg.text)
                await applyClock(msg.text);
            break;
        case 'toggle':
            toggle();
            break;
        case 'stop':
            stop();
            break;
        case 'set':
            if (msg.key) {
                await vscode.workspace
                    .getConfiguration('deadline')
                    .update(msg.key, msg.value, vscode.ConfigurationTarget.Global);
            }
            render();
            syncPanel();
            break;
    }
}
function syncPanel() {
    if (!panel)
        return;
    const cfg = vscode.workspace.getConfiguration('deadline');
    const remain = Math.max(0, remaining());
    panel.webview.postMessage({
        type: 'state',
        remain: remain,
        paused: pausedRemain > 0,
        running: targetTime > 0,
        total: Math.max(remain, Math.round(lastMinutes * 60000)),
        mode: cfg.get('mode', 'watermark'),
        opacity: cfg.get('opacity', 0.12),
        fontSizeVw: cfg.get('fontSizeVw', 12),
        offsetX: cfg.get('offsetX', 0),
        offsetY: cfg.get('offsetY', 0),
        coverDim: cfg.get('coverDim', 0.55),
        color: cfg.get('color', ''),
        image: cfg.get('image', ''),
    });
}
function panelHtml() {
    return '<!DOCTYPE html>' +
        '<html lang="zh-CN">' +
        '<head>' +
        '<meta charset="UTF-8">' +
        '<meta http-equiv="Content-Security-Policy" content="default-src \'none\'; style-src \'unsafe-inline\'; script-src \'unsafe-inline\'; img-src https: data: file:;">' +
        '<style>' +
        '  :root { color-scheme: dark; }' +
        '  * { box-sizing: border-box; }' +
        '  body { margin:0; padding:18px 20px 28px; font-family:var(--vscode-font-family); color:var(--vscode-foreground); background:var(--vscode-editor-background); }' +
        '  h1 { font-size:13px; letter-spacing:.22em; margin:0 0 16px; opacity:.75; font-weight:600; }' +
        '  h2 { font-size:11px; letter-spacing:.18em; margin:22px 0 8px; opacity:.55; font-weight:600; }' +
        '  .card { border:1px solid var(--vscode-panel-border, rgba(128,128,128,.28)); border-radius:12px; padding:16px; background:var(--vscode-sideBar-background, rgba(255,255,255,.03)); }' +
        '  #time { font-family:var(--vscode-editor-font-family); font-size:34px; font-weight:700; letter-spacing:.04em; font-variant-numeric:tabular-nums; }' +
        '  #label { font-size:11px; opacity:.65; margin-left:8px; }' +
        '  #track { height:3px; border-radius:3px; background:rgba(128,128,128,.25); margin-top:10px; overflow:hidden; }' +
        '  #bar { height:100%; width:0%; background:var(--vscode-textLink-foreground,#4ec9b0); transition:width .3s linear; }' +
        '  .btns { display:flex; gap:8px; margin-top:14px; }' +
        '  button { font:inherit; font-size:12px; padding:6px 12px; border-radius:8px; cursor:pointer; border:1px solid var(--vscode-button-border, transparent); background:var(--vscode-button-secondaryBackground, rgba(128,128,128,.22)); color:var(--vscode-button-secondaryForeground, inherit); }' +
        '  button:hover { filter:brightness(1.18); }' +
        '  button.primary { background:var(--vscode-button-background,#0e639c); color:var(--vscode-button-foreground,#fff); font-weight:600; }' +
        '  .chips { display:flex; flex-wrap:wrap; gap:6px; }' +
        '  .chips button { border-radius:999px; padding:5px 12px; }' +
        '  .row { display:flex; gap:6px; margin-top:10px; }' +
        '  input[type=text], input[type=number] { flex:1; min-width:0; font:inherit; font-size:12px; padding:6px 9px; border-radius:7px; border:1px solid var(--vscode-input-border, rgba(128,128,128,.35)); background:var(--vscode-input-background, rgba(0,0,0,.2)); color:inherit; }' +
        '  input:focus { outline:1px solid var(--vscode-focusBorder); }' +
        '  .seg { display:flex; gap:6px; }' +
        '  .seg button { flex:1; }' +
        '  .seg button.on { background:var(--vscode-button-background,#0e639c); color:#fff; }' +
        '  label.field { display:grid; grid-template-columns:88px 1fr 52px; align-items:center; gap:10px; font-size:12px; margin-top:10px; }' +
        '  label.field span.v { text-align:right; opacity:.6; font-variant-numeric:tabular-nums; }' +
        '  input[type=range] { width:100%; accent-color:var(--vscode-textLink-foreground,#4ec9b0); }' +
        '  .full { margin-top:10px; }' +
        '  .tip { font-size:11px; opacity:.5; margin-top:16px; line-height:1.6; }' +
        '</style>' +
        '</head>' +
        '<body>' +
        '  <h1>DEADLINE · 倒计时设置</h1>' +
        '  <div class="card">' +
        '    <div><span id="time">--:--:--</span><span id="label">未启动</span></div>' +
        '    <div id="track"><div id="bar"></div></div>' +
        '    <div class="btns">' +
        '      <button class="primary" id="btnMain">开始 25 分钟</button>' +
        '      <button id="btnStop">停止</button>' +
        '    </div>' +
        '  </div>' +
        '  <h2>快捷时长</h2>' +
        '  <div class="chips" id="presets">' +
        '    <button data-m="1">1m</button><button data-m="5">5m</button><button data-m="15">15m</button>' +
        '    <button data-m="25">25m 番茄</button><button data-m="45">45m</button><button data-m="60">60m</button><button data-m="90">90m</button>' +
        '  </div>' +
        '  <div class="row">' +
        '    <input type="number" id="min" min="0.1" step="0.1" placeholder="自定义分钟">' +
        '    <button id="goMin">启动</button>' +
        '  </div>' +
        '  <h2>倒数到指定时刻</h2>' +
        '  <div class="row">' +
        '    <input type="text" id="at" placeholder="18:00 或 2026-06-01 09:00">' +
        '    <button id="goAt">设定</button>' +
        '  </div>' +
        '  <h2>渲染模式</h2>' +
        '  <div class="seg" id="mode">' +
        '    <button data-mode="watermark">水印 · 与 background-cover 协同</button>' +
        '    <button data-mode="cover">封面 · 内置 background-cover</button>' +
        '  </div>' +
        '  <h2>外观微调</h2>' +
        '  <div class="card">' +
        '    <label class="field">透明度<input type="range" id="opacity" min="0.02" max="1" step="0.01"><span class="v" id="oV"></span></label>' +
        '    <label class="field">字号 vw<input type="range" id="size" min="3" max="30" step="0.5"><span class="v" id="sV"></span></label>' +
        '    <label class="field">遮罩浓度<input type="range" id="dim" min="0" max="1" step="0.05"><span class="v" id="dV"></span></label>' +
        '    <label class="field">水平偏移<input type="range" id="dx" min="-500" max="500" step="5"><span class="v" id="xV"></span></label>' +
        '    <label class="field">垂直偏移<input type="range" id="dy" min="-500" max="500" step="5"><span class="v" id="yV"></span></label>' +
        '    <input class="full" type="text" id="color" placeholder="颜色：留空跟随主题，或 #67e8f9">' +
        '    <input class="full" type="text" id="image" placeholder="封面图：https://... 或 本地绝对路径">' +
        '    <div class="btns">' +
        '      <button id="goColor">应用配色</button>' +
        '      <button id="goImage">应用封面图</button>' +
        '      <button id="clrImage">清除图片</button>' +
        '    </div>' +
        '  </div>' +
        '  <p class="tip">所有改动即时写入 settings.json（deadline.*）。<br>' +
        '  协同提示：如果你已安装 background-cover 插件，模式选「水印」，两个插件各司其职，效果绝佳。</p>' +
        '<script>' +
        '(function () {' +
        '  var api = acquireVsCodeApi();' +
        '  function el(id) { return document.getElementById(id); }' +
        '  function post(m) { api.postMessage(m); }' +
        '  function fmt(ms) {' +
        '    var s = Math.max(0, Math.ceil(ms / 1000));' +
        '    function p(n) { return n < 10 ? "0" + n : String(n); }' +
        '    var d = Math.floor(s / 86400), h = Math.floor(s % 86400 / 3600), m = Math.floor(s % 3600 / 60);' +
        '    return (d > 0 ? d + "d " : "") + p(h) + ":" + p(m) + ":" + p(s % 60);' +
        '  }' +
        '  el("presets").addEventListener("click", function (e) {' +
        '    var b = e.target.closest("button"); if (b) post({ type: "start", minutes: Number(b.getAttribute("data-m")) });' +
        '  });' +
        '  el("goMin").addEventListener("click", function () {' +
        '    var v = Number(el("min").value); if (v > 0) post({ type: "start", minutes: v });' +
        '  });' +
        '  el("min").addEventListener("keydown", function (e) { if (e.key === "Enter") el("goMin").click(); });' +
        '  el("goAt").addEventListener("click", function () { post({ type: "at", text: el("at").value }); });' +
        '  el("at").addEventListener("keydown", function (e) { if (e.key === "Enter") el("goAt").click(); });' +
        '  el("btnMain").addEventListener("click", function () { post({ type: "toggle" }); });' +
        '  el("btnStop").addEventListener("click", function () { post({ type: "stop" }); });' +
        '  el("mode").addEventListener("click", function (e) {' +
        '    var b = e.target.closest("button"); if (b) post({ type: "set", key: "mode", value: b.getAttribute("data-mode") });' +
        '  });' +
        '  function slider(id, key, out, digits) {' +
        '    el(id).addEventListener("change", function () {' +
        '      post({ type: "set", key: key, value: Number(el(id).value) });' +
        '    });' +
        '    el(id).addEventListener("input", function () { el(out).textContent = Number(el(id).value).toFixed(digits); });' +
        '  }' +
        '  slider("opacity", "opacity", "oV", 2);' +
        '  slider("size", "fontSizeVw", "sV", 1);' +
        '  slider("dim", "coverDim", "dV", 2);' +
        '  slider("dx", "offsetX", "xV", 0);' +
        '  slider("dy", "offsetY", "yV", 0);' +
        '  el("goColor").addEventListener("click", function () { post({ type: "set", key: "color", value: el("color").value.trim() }); });' +
        '  el("goImage").addEventListener("click", function () { post({ type: "set", key: "image", value: el("image").value.trim() }); });' +
        '  el("clrImage").addEventListener("click", function () { el("image").value = ""; post({ type: "set", key: "image", value: "" }); });' +
        '  window.addEventListener("message", function (e) {' +
        '    var s = e.data; if (!s || s.type !== "state") return;' +
        '    el("time").textContent = s.remain > 0 ? fmt(s.remain) : "未启动";' +
        '    el("label").textContent = s.paused ? "已暂停" : (s.running ? "倒计时中" : "待启动");' +
        '    el("bar").style.width = s.total > 0 ? Math.max(0, Math.min(100, s.remain / s.total * 100)) + "%" : "0%";' +
        '    el("btnMain").textContent = s.paused ? "继续" : (s.running ? "暂停" : "启动");' +
        '    var btns = el("mode").querySelectorAll("button");' +
        '    for (var i = 0; i < btns.length; i++) btns[i].className = btns[i].getAttribute("data-mode") === s.mode ? "on" : "";' +
        '    el("opacity").value = s.opacity; el("oV").textContent = Number(s.opacity).toFixed(2);' +
        '    el("size").value = s.fontSizeVw; el("sV").textContent = Number(s.fontSizeVw).toFixed(1);' +
        '    el("dim").value = s.coverDim; el(' + "'dV'" + ').textContent = Number(s.coverDim).toFixed(2);' +
        '    el("dx").value = s.offsetX; el(' + "'xV'" + ').textContent = String(s.offsetX);' +
        '    el("dy").value = s.offsetY; el(' + "'yV'" + ').textContent = String(s.offsetY);' +
        '    if (document.activeElement !== el("color")) el("color").value = s.color || "";' +
        '    if (document.activeElement !== el("image")) el("image").value = s.image || "";' +
        '  });' +
        '})();' +
        '</script>' +
        '</body>' +
        '</html>';
}
/* ==================================================================
 *  命令与工具
 * ================================================================== */
async function promptMinutes() {
    const input = await vscode.window.showInputBox({
        title: 'DEADLINE · 设置倒计时',
        prompt: '输入分钟数，回车立即开始',
        value: String(lastMinutes),
        validateInput: (v) => /^\d+(\.\d+)?$/.test(v) && Number(v) > 0 ? undefined : '请输入大于 0 的数字',
    });
    if (input)
        start(Number(input));
}
async function promptClock() {
    const input = await vscode.window.showInputBox({
        title: 'DEADLINE · 倒数到指定时刻',
        prompt: '支持 HH:mm（已过则顺延到明天）或 YYYY-MM-DD HH:mm',
        placeHolder: '例如 18:00 或 2026-06-01 09:00',
    });
    if (input)
        await applyClock(input);
}
async function applyClock(raw) {
    const text = raw.trim();
    let t = NaN;
    if (/^\d{1,2}:\d{2}$/.test(text)) {
        const parts = text.split(':');
        const d = new Date();
        d.setHours(Number(parts[0]), Number(parts[1]), 0, 0);
        if (d.getTime() <= Date.now())
            d.setDate(d.getDate() + 1);
        t = d.getTime();
    }
    else {
        t = new Date(text.replace(' ', 'T')).getTime();
    }
    if (Number.isNaN(t) || t <= Date.now()) {
        void vscode.window.showErrorMessage('DEADLINE：时间无效或已经过去 —— ' + text);
        return false;
    }
    lastMinutes = Math.max(1, Math.round((t - Date.now()) / 60000));
    start((t - Date.now()) / 60000);
    void vscode.window.showInformationMessage('DEADLINE · 将在 ' + new Date(t).toLocaleString() + ' 归零');
    return true;
}
function clamp(v, lo, hi) {
    return Number.isFinite(v) ? Math.min(hi, Math.max(lo, v)) : lo;
}
function asUrl(raw) {
    const v = raw.trim().replace(/'/g, '');
    if (!v)
        return '';
    if (v.indexOf('://') > -1 || v.indexOf('data:') === 0)
        return v;
    return 'file://' + (v.charAt(0) === '/' ? '' : '/') + v;
}
function format(ms) {
    const total = Math.max(0, Math.ceil(ms / 1000));
    const p = (n) => (n < 10 ? '0' + n : String(n));
    const d = Math.floor(total / 86400);
    const h = Math.floor((total % 86400) / 3600);
    const m = Math.floor((total % 3600) / 60);
    return (d > 0 ? d + 'd ' : '') + p(h) + ':' + p(m) + ':' + p(total % 60);
}
function deactivate() {
    if (ticker)
        clearInterval(ticker);
    if (renderTimer) {
        clearTimeout(renderTimer);
        renderTimer = undefined;
    }
    clearOverlay();
    panel?.dispose();
}
//# sourceMappingURL=extension.js.map