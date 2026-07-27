// 弹窗脚本 - 处理用户界面交互
console.log('🎯 智能后台点击器弹窗已加载');

let currentTab = null;
let clickArea = null;
let isClicking = false;
let clickCount = 0;
let settings = {
    interval: 10,
    randomRange: 5,
    // 间歇模式配置
    intervalMode: {
        enabled: false,         // 间歇模式开关
        clickDuration: 15,      // 连点时长（秒）
        pauseDuration: 3        // 暂停时长（秒）
    }
};

// 间歇模式状态
let intervalModeState = {
    currentPhase: 'idle',       // 当前阶段：'idle'|'clicking'|'pausing'
    remainingTime: 0,           // 当前阶段剩余时间
    cycleCount: 0               // 循环次数统计
};

// DOM元素 - 将在DOMContentLoaded事件中初始化
let selectAreaBtn, startClickBtn, stopClickBtn;
let intervalInput, randomRangeInput, areaInfo, status, clickCountDisplay;
let intervalModeToggle, intervalModeSettings, clickDurationInput, pauseDurationInput, intervalModeStatus;

// 初始化
document.addEventListener('DOMContentLoaded', async () => {
    console.log('[初始化] 弹窗DOM加载完成，开始初始化...');

    try {
        // 初始化所有DOM元素引用
        selectAreaBtn = document.getElementById('selectArea');
        startClickBtn = document.getElementById('startClick');
        stopClickBtn = document.getElementById('stopClick');
        intervalInput = document.getElementById('interval');
        randomRangeInput = document.getElementById('randomRange');
        areaInfo = document.getElementById('areaInfo');
        status = document.getElementById('status');
        clickCountDisplay = document.getElementById('clickCount');

        // 间歇模式相关DOM元素
        intervalModeToggle = document.getElementById('intervalModeToggle');
        intervalModeSettings = document.getElementById('intervalModeSettings');
        clickDurationInput = document.getElementById('clickDuration');
        pauseDurationInput = document.getElementById('pauseDuration');
        intervalModeStatus = document.getElementById('intervalModeStatus');

        console.log('[初始化] ✅ DOM元素引用初始化完成');
        console.log('[初始化] intervalInput:', intervalInput);
        console.log('[初始化] randomRangeInput:', randomRangeInput);
        console.log('[初始化] clickDurationInput:', clickDurationInput);
        console.log('[初始化] pauseDurationInput:', pauseDurationInput);

        // 检查关键DOM元素是否存在
        const requiredElements = [
            { name: 'selectArea', element: selectAreaBtn },
            { name: 'startClick', element: startClickBtn },
            { name: 'stopClick', element: stopClickBtn },
            { name: 'interval', element: intervalInput },
            { name: 'randomRange', element: randomRangeInput },
            { name: 'intervalModeToggle', element: intervalModeToggle },
            { name: 'clickDuration', element: clickDurationInput },
            { name: 'pauseDuration', element: pauseDurationInput },
            { name: 'intervalModeSettings', element: intervalModeSettings }
        ];

        const missingElements = requiredElements.filter(item => !item.element);
        if (missingElements.length > 0) {
            console.error('[初始化] 缺少关键DOM元素:', missingElements.map(item => item.name));
            alert('页面初始化失败，请重新打开扩展！');
            return;
        }

        console.log('[初始化] ✅ 所有关键DOM元素检查通过');

        // 获取当前活动标签页
        try {
            const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
            currentTab = tab;
            console.log('[初始化] 当前标签页:', tab.url);
            console.log('[初始化] 标签页ID:', tab.id);
            console.log('[初始化] 标签页状态:', tab.status);
        } catch (error) {
            console.error('[初始化] 获取当前标签页失败:', error);
        }

        // 加载存储的数据
        loadStoredData();

        // 绑定事件监听器
        bindEventListeners();

        // 绑定预设按钮事件 - Chrome扩展正确做法
        bindPresetButtons();

        // 定期更新状态
        setInterval(updateStatus, 1000);

        console.log('[初始化] ✅ 页面初始化完成');

    } catch (error) {
        console.error('[初始化] 页面初始化失败:', error);
        alert('扩展初始化失败，请重新加载页面！');
    }
});

// 加载存储的数据
function loadStoredData() {
    chrome.storage.local.get(['clickArea', 'settings', 'isClicking', 'clickCount', 'intervalModeState'], (data) => {
        console.log('加载的数据:', data);

        if (data.clickArea) {
            clickArea = data.clickArea;
            updateAreaInfo();
        }

        if (data.settings) {
            // 保存当前输入框的值，防止被存储数据覆盖
            const currentInterval = parseInt(intervalInput.value);
            const currentRandomRange = parseInt(randomRangeInput.value);

            settings = { ...settings, ...data.settings };

            // 只有在输入框为空或默认值时才更新，避免覆盖用户刚设置的预设值
            if (!intervalInput.value || intervalInput.value === '10' || isNaN(currentInterval)) {
                intervalInput.value = settings.interval;
            }
            if (!randomRangeInput.value || randomRangeInput.value === '5' || isNaN(currentRandomRange)) {
                randomRangeInput.value = settings.randomRange;
            }

            // 加载间歇模式设置
            if (settings.intervalMode) {
                intervalModeToggle.checked = settings.intervalMode.enabled;
                clickDurationInput.value = settings.intervalMode.clickDuration;
                pauseDurationInput.value = settings.intervalMode.pauseDuration;
                updateIntervalModeUI();
            }

            console.log('[数据加载] 设置已加载，当前输入框值已保护');
        }

        if (data.isClicking !== undefined) {
            isClicking = data.isClicking;
        }

        if (data.clickCount !== undefined) {
            clickCount = data.clickCount;
        }

        if (data.intervalModeState) {
            intervalModeState = { ...intervalModeState, ...data.intervalModeState };
        }

        updateUI();
    });
}

// 绑定事件监听器
function bindEventListeners() {
    // 选择区域按钮
    selectAreaBtn.addEventListener('click', async () => {
        console.log('开始选择区域');
        
        if (!currentTab) {
            alert('无法获取当前标签页');
            return;
        }
        
        try {
            console.log('[选择区域] 准备发送消息到标签页:', currentTab.id);
            // 向内容脚本发送选择区域消息
            await chrome.tabs.sendMessage(currentTab.id, { type: 'selectArea' });
            console.log('[选择区域] ✅ 消息发送成功');
            window.close(); // 关闭弹窗让用户选择区域
        } catch (error) {
            console.error('[选择区域] 发送消息失败:', error);
            console.error('[选择区域] 错误详情:', error.message);
            console.error('[选择区域] 当前标签页:', currentTab);

            // 显示友好的错误提示和刷新选项
            showRefreshDialog(error.message);
        }
    });
    
    // 开始点击按钮
    startClickBtn.addEventListener('click', async () => {
        console.log('开始点击');

        if (!clickArea) {
            alert('请先选择点击区域!');
            return;
        }

        if (!currentTab) {
            alert('无法获取当前标签页');
            return;
        }

        // 更新设置
        updateSettings();

        console.log('[开始点击] 当前设置:', settings);
        console.log('[开始点击] 间歇模式状态:', settings.intervalMode);

        // 间歇模式参数验证
        if (settings.intervalMode.enabled) {
            if (settings.intervalMode.clickDuration < 1 || settings.intervalMode.clickDuration > 300) {
                alert('连点时长必须在1-300秒之间！');
                return;
            }
            if (settings.intervalMode.pauseDuration < 1 || settings.intervalMode.pauseDuration > 60) {
                alert('暂停时长必须在1-60秒之间！');
                return;
            }

            // 显示间歇模式确认信息（仅首次使用时）
            const hasConfirmed = localStorage.getItem('intervalModeConfirmed');
            if (!hasConfirmed) {
                const confirmMessage = `即将启动间歇模式：\n连点${settings.intervalMode.clickDuration}秒 → 暂停${settings.intervalMode.pauseDuration}秒\n点击间隔：${settings.interval}ms\n\n确定要开始吗？\n\n（此提示仅显示一次）`;
                if (!confirm(confirmMessage)) {
                    return;
                } else {
                    localStorage.setItem('intervalModeConfirmed', 'true');
                }
            }
        }

        try {
            // 向内容脚本发送开始点击消息
            await chrome.tabs.sendMessage(currentTab.id, {
                type: 'startClick',
                settings: settings
            });

            isClicking = true;
            updateUI();
        } catch (error) {
            console.error('发送开始点击消息失败:', error);
            showRefreshDialog(error.message);
        }
    });
    
    // 停止点击按钮
    stopClickBtn.addEventListener('click', async () => {
        console.log('停止点击');
        
        if (!currentTab) {
            alert('无法获取当前标签页');
            return;
        }
        
        try {
            // 向内容脚本发送停止点击消息
            await chrome.tabs.sendMessage(currentTab.id, { type: 'stopClick' });
            
            isClicking = false;
            updateUI();
        } catch (error) {
            console.error('发送停止点击消息失败:', error);
            showRefreshDialog(error.message);
        }
    });
    
    // 设置输入框变化
    intervalInput.addEventListener('change', () => {
        updateSettings();
    });
    randomRangeInput.addEventListener('change', () => {
        updateSettings();
    });

    // 间歇模式相关事件监听器
    intervalModeToggle.addEventListener('change', () => {
        settings.intervalMode.enabled = intervalModeToggle.checked;
        updateIntervalModeUI();
        updateSettings();
        console.log('间歇模式开关状态:', settings.intervalMode.enabled);
    });

    clickDurationInput.addEventListener('change', () => {
        const value = parseInt(clickDurationInput.value) || 15;
        if (validateIntervalModeTime(value, 1, 300, '连点时长')) {
            settings.intervalMode.clickDuration = value;
            // 立即保存设置，避免被异步操作覆盖
            chrome.storage.local.set({ settings: settings });
            console.log('[间歇设置] 连点时长已更新:', value);
        } else {
            // 恢复到之前的有效值
            clickDurationInput.value = settings.intervalMode.clickDuration;
        }
    });

    pauseDurationInput.addEventListener('change', () => {
        const value = parseInt(pauseDurationInput.value) || 3;
        if (validateIntervalModeTime(value, 1, 60, '暂停时长')) {
            settings.intervalMode.pauseDuration = value;
            // 立即保存设置，避免被异步操作覆盖
            chrome.storage.local.set({ settings: settings });
            console.log('[间歇设置] 暂停时长已更新:', value);
        } else {
            // 恢复到之前的有效值
            pauseDurationInput.value = settings.intervalMode.pauseDuration;
        }
    });

    // 初始化完成
}

// 更新设置
function updateSettings() {
    const newInterval = parseInt(intervalInput.value) || 10;
    const newRandomRange = parseInt(randomRangeInput.value) || 0;

    // 验证设置
    if (newInterval < 1) {
        intervalInput.value = 1;
        alert('点击间隔不能小于1ms');
        return;
    }

    if (newInterval > 10000) {
        intervalInput.value = 10000;
        alert('点击间隔不能大于10000ms');
        return;
    }

    if (newRandomRange < 0) {
        randomRangeInput.value = 0;
        alert('随机范围不能小于0');
        return;
    }

    if (newRandomRange > 100) {
        randomRangeInput.value = 100;
        alert('随机范围不能大于100ms');
        return;
    }

    // 更新设置，保持intervalMode配置不变
    settings = {
        ...settings,
        interval: newInterval,
        randomRange: newRandomRange
    };

    // 立即保存到存储，防止刷新后丢失
    chrome.storage.local.set({ settings: settings }, () => {
        console.log('[设置保存] ✅ 用户设置已保存:', settings);
    });
}

// 绑定预设按钮事件 - Chrome扩展正确做法
function bindPresetButtons() {
    console.log('[预设绑定] 开始绑定预设按钮事件...');

    // 绑定快速预设按钮
    const presetButtons = [
        { id: 'preset-extreme', interval: 1, random: 0, name: '极速' },
        { id: 'preset-super', interval: 5, random: 2, name: '超快' },
        { id: 'preset-fast', interval: 10, random: 5, name: '快速' },
        { id: 'preset-normal', interval: 50, random: 20, name: '正常' }
    ];

    presetButtons.forEach(preset => {
        const button = document.getElementById(preset.id);
        if (button) {
            button.addEventListener('click', () => {
                console.log(`[快速预设] 应用${preset.name}预设: ${preset.interval}ms, ${preset.random}ms`);

                // 直接更新输入框
                if (intervalInput && randomRangeInput) {
                    intervalInput.value = preset.interval;
                    randomRangeInput.value = preset.random;

                    // 更新settings对象
                    settings.interval = preset.interval;
                    settings.randomRange = preset.random;

                    // 保存到存储
                    chrome.storage.local.set({ settings: settings });

                    // 更新UI
                    updateUI();

                    console.log(`[快速预设] ✅ ${preset.name}预设已应用`);
                } else {
                    console.error('[快速预设] 输入框元素未找到');
                }
            });
            console.log(`[预设绑定] ✅ ${preset.name}预设按钮已绑定`);
        } else {
            console.error(`[预设绑定] 未找到按钮: ${preset.id}`);
        }
    });

    // 绑定间歇预设按钮
    const intervalPresetButtons = [
        { id: 'interval-preset-fast', click: 5, pause: 1, name: '快速间歇' },
        { id: 'interval-preset-standard', click: 15, pause: 3, name: '标准间歇' },
        { id: 'interval-preset-long', click: 30, pause: 5, name: '长时间歇' },
        { id: 'interval-preset-conservative', click: 10, pause: 5, name: '保守间歇' }
    ];

    intervalPresetButtons.forEach(preset => {
        const button = document.getElementById(preset.id);
        if (button) {
            button.addEventListener('click', () => {
                console.log(`[间歇预设] 应用${preset.name}: 连点${preset.click}秒, 暂停${preset.pause}秒`);

                // 直接更新输入框
                if (clickDurationInput && pauseDurationInput) {
                    clickDurationInput.value = preset.click;
                    pauseDurationInput.value = preset.pause;

                    // 更新settings对象
                    settings.intervalMode = {
                        ...settings.intervalMode,
                        clickDuration: preset.click,
                        pauseDuration: preset.pause
                    };

                    // 保存到存储
                    chrome.storage.local.set({ settings: settings });

                    // 更新UI
                    updateIntervalModeStatus();
                    updateUI();

                    console.log(`[间歇预设] ✅ ${preset.name}已应用`);
                } else {
                    console.error('[间歇预设] 输入框元素未找到');
                }
            });
            console.log(`[预设绑定] ✅ ${preset.name}按钮已绑定`);
        } else {
            console.error(`[预设绑定] 未找到按钮: ${preset.id}`);
        }
    });

    console.log('[预设绑定] ✅ 所有预设按钮事件绑定完成');
}

// 显示刷新对话框
function showRefreshDialog(errorMessage) {
    // 创建模态对话框
    const modal = document.createElement('div');
    modal.style.cssText = `
        position: fixed;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        background: rgba(0, 0, 0, 0.5);
        display: flex;
        justify-content: center;
        align-items: center;
        z-index: 10000;
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    `;

    const dialog = document.createElement('div');
    dialog.style.cssText = `
        background: white;
        padding: 25px;
        border-radius: 12px;
        box-shadow: 0 8px 32px rgba(0, 0, 0, 0.3);
        max-width: 400px;
        text-align: center;
        animation: slideIn 0.3s ease-out;
    `;

    dialog.innerHTML = `
        <div style="margin-bottom: 20px;">
            <div style="font-size: 48px; margin-bottom: 15px;">🔄</div>
            <h3 style="margin: 0 0 10px 0; color: #2d3748;">需要刷新页面</h3>
            <p style="margin: 0; color: #718096; font-size: 14px; line-height: 1.5;">
                当前首次使用，需要刷新页面来加载扩展功能<br>
                <small style="color: #a0aec0;">错误: ${errorMessage}</small>
            </p>
        </div>
        <div style="display: flex; gap: 10px; justify-content: center;">
            <button id="refreshBtn" style="
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                color: white;
                border: none;
                padding: 12px 24px;
                border-radius: 8px;
                cursor: pointer;
                font-weight: 500;
                font-size: 14px;
                transition: transform 0.2s;
            ">🔄 立即刷新</button>
            <button id="cancelBtn" style="
                background: #e2e8f0;
                color: #4a5568;
                border: none;
                padding: 12px 24px;
                border-radius: 8px;
                cursor: pointer;
                font-weight: 500;
                font-size: 14px;
                transition: transform 0.2s;
            ">取消</button>
        </div>
    `;

    // 添加动画样式
    const style = document.createElement('style');
    style.textContent = `
        @keyframes slideIn {
            from {
                opacity: 0;
                transform: scale(0.9) translateY(-20px);
            }
            to {
                opacity: 1;
                transform: scale(1) translateY(0);
            }
        }
        #refreshBtn:hover {
            transform: translateY(-2px);
        }
        #cancelBtn:hover {
            transform: translateY(-2px);
            background: #cbd5e0;
        }
    `;
    document.head.appendChild(style);

    modal.appendChild(dialog);
    document.body.appendChild(modal);

    // 绑定按钮事件
    document.getElementById('refreshBtn').addEventListener('click', async () => {
        try {
            console.log('[刷新] 开始刷新当前标签页');
            await chrome.tabs.reload(currentTab.id);
            console.log('[刷新] ✅ 页面刷新成功');

            // 显示刷新成功提示
            dialog.innerHTML = `
                <div style="margin-bottom: 20px;">
                    <div style="font-size: 48px; margin-bottom: 15px;">✅</div>
                    <h3 style="margin: 0 0 10px 0; color: #38a169;">刷新成功</h3>
                    <p style="margin: 0; color: #718096; font-size: 14px;">
                        页面已刷新，请稍等片刻后重试选择区域
                    </p>
                </div>
            `;

            // 2秒后关闭对话框
            setTimeout(() => {
                modal.remove();
                style.remove();
            }, 2000);

        } catch (error) {
            console.error('[刷新] 刷新失败:', error);
            alert('刷新失败，请手动刷新页面');
            modal.remove();
            style.remove();
        }
    });

    document.getElementById('cancelBtn').addEventListener('click', () => {
        modal.remove();
        style.remove();
    });

    // 点击背景关闭
    modal.addEventListener('click', (e) => {
        if (e.target === modal) {
            modal.remove();
            style.remove();
        }
    });
}

// 速度信息已移除 - 避免不准确的显示

// 间歇模式时间参数验证函数 - 增强版
function validateIntervalModeTime(value, min, max, fieldName) {
    // 检查是否为有效数字
    if (isNaN(value) || value === null || value === undefined) {
        alert(`${fieldName}必须是有效的数字！`);
        return false;
    }

    // 检查范围
    if (value < min) {
        alert(`${fieldName}不能小于${min}秒！\n当前值: ${value}秒`);
        return false;
    }
    if (value > max) {
        alert(`${fieldName}不能大于${max}秒！\n当前值: ${value}秒`);
        return false;
    }

    // 检查是否为整数
    if (!Number.isInteger(value)) {
        alert(`${fieldName}必须是整数！\n当前值: ${value}`);
        return false;
    }

    console.log(`[参数验证] ${fieldName}验证通过: ${value}秒`);
    return true;
}

// 更新间歇模式UI显示 - 修改为始终显示说明
function updateIntervalModeUI() {
    // 安全检查DOM元素
    if (!intervalModeToggle || !intervalModeSettings) {
        console.error('[UI更新] 间歇模式DOM元素未找到');
        return;
    }

    const isEnabled = intervalModeToggle.checked;
    console.log(`[UI更新] 间歇模式开关状态: ${isEnabled}`);

    // 间歇模式设置区域始终显示，不再隐藏
    // 这样用户可以随时查看说明和预设按钮
    intervalModeSettings.style.display = 'block';
    intervalModeSettings.style.maxHeight = 'none';
    intervalModeSettings.style.opacity = '1';
    intervalModeSettings.style.transform = 'translateY(0)';

    // 根据开关状态调整输入框的可用性
    if (clickDurationInput && pauseDurationInput) {
        clickDurationInput.disabled = !isEnabled;
        pauseDurationInput.disabled = !isEnabled;

        // 调整输入框样式
        const opacity = isEnabled ? '1' : '0.6';
        clickDurationInput.style.opacity = opacity;
        pauseDurationInput.style.opacity = opacity;
    }

    // 更新状态显示
    updateIntervalModeStatus();
}

// 更新间歇模式状态显示
function updateIntervalModeStatus() {
    if (!intervalModeStatus) return;

    const isEnabled = settings.intervalMode.enabled;
    const phase = intervalModeState.currentPhase;
    const remainingTime = intervalModeState.remainingTime;

    if (!isEnabled || !isClicking) {
        intervalModeStatus.style.display = 'none';
        return;
    }

    intervalModeStatus.style.display = 'block';
    intervalModeStatus.className = `interval-mode-status ${phase}`;

    let phaseText = '';
    let phaseIcon = '';

    switch (phase) {
        case 'clicking':
            phaseText = '连点中';
            phaseIcon = '🎯';
            break;
        case 'pausing':
            phaseText = '暂停中';
            phaseIcon = '⏸️';
            break;
        default:
            phaseText = '待机中';
            phaseIcon = '⏹️';
    }

    // 构建优化的状态显示结构
    let mainStatus = `${phaseIcon} ${phaseText}`;
    let detailInfo = '';

    if (remainingTime > 0) {
        // 添加倒计时显示
        const minutes = Math.floor(remainingTime / 60);
        const seconds = remainingTime % 60;
        const timeDisplay = minutes > 0 ? `${minutes}:${seconds.toString().padStart(2, '0')}` : `${seconds}秒`;
        mainStatus += ` (${timeDisplay})`;
    }

    // 构建详细信息
    const configInfo = `连点${settings.intervalMode.clickDuration}s/暂停${settings.intervalMode.pauseDuration}s`;
    if (intervalModeState.cycleCount > 0) {
        detailInfo = `第${intervalModeState.cycleCount}轮 | ${configInfo}`;
    } else {
        detailInfo = configInfo;
    }

    // 使用优化的HTML结构
    intervalModeStatus.innerHTML = `
        <div class="status-main">${mainStatus}</div>
        <div class="status-detail">${detailInfo}</div>
    `;
}

// 间歇预设函数已在DOMContentLoaded事件中定义

// 全局函数已在DOMContentLoaded事件中暴露

// 更新区域信息显示
function updateAreaInfo() {
    if (clickArea) {
        areaInfo.innerHTML = `
            <strong>✅ 区域已设置</strong><br>
            位置: (${clickArea.x}, ${clickArea.y})<br>
            大小: ${clickArea.width} × ${clickArea.height} px
        `;
        areaInfo.style.background = '#f0fff4';
        areaInfo.style.borderColor = '#9ae6b4';
        areaInfo.style.color = '#22543d';
    } else {
        areaInfo.innerHTML = '<strong>⚠️ 请先选择点击区域</strong>';
        areaInfo.style.background = '#fef5e7';
        areaInfo.style.borderColor = '#f6ad55';
        areaInfo.style.color = '#c05621';
    }
}

// 更新UI状态
function updateUI() {
    // 更新按钮状态
    startClickBtn.disabled = isClicking || !clickArea;
    stopClickBtn.disabled = !isClicking;
    selectAreaBtn.disabled = isClicking;

    // 更新状态显示
    if (isClicking) {
        if (settings.intervalMode.enabled) {
            // 间歇模式状态显示
            const phase = intervalModeState.currentPhase;
            switch (phase) {
                case 'clicking':
                    status.textContent = '🎯 间歇模式 - 连点中...';
                    break;
                case 'pausing':
                    status.textContent = '⏸️ 间歇模式 - 暂停中...';
                    break;
                default:
                    status.textContent = '🔄 间歇模式 - 运行中...';
            }
        } else {
            status.textContent = '🚀 正在高速点击中...';
        }
        status.className = 'status active';
    } else {
        status.textContent = '⏸️ 点击已停止';
        status.className = 'status inactive';
    }

    // 更新点击次数
    if (clickCountDisplay) {
        clickCountDisplay.textContent = clickCount.toLocaleString();
    }

    // 更新区域信息
    updateAreaInfo();

    // 更新间歇模式状态
    updateIntervalModeStatus();
}

// 定期更新状态
async function updateStatus() {
    if (!currentTab) return;
    
    try {
        // 从内容脚本获取最新状态
        const response = await chrome.tabs.sendMessage(currentTab.id, { type: 'getStatus' });
        
        if (response) {
            if (response.clickArea) {
                clickArea = response.clickArea;
            }
            
            if (response.isClicking !== undefined) {
                isClicking = response.isClicking;
            }
            
            if (response.clickCount !== undefined) {
                clickCount = response.clickCount;
            }
            
            updateUI();
        }
    } catch (error) {
        // 内容脚本可能还没加载，忽略错误
        console.debug('获取状态失败:', error.message);
    }
}

// 监听来自后台脚本的消息
chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    console.log('弹窗收到消息:', message);

    switch (message.type) {
        case 'areaSelected':
            clickArea = message.area;
            updateUI();

            // 立即保存选择的区域到存储，防止刷新后丢失
            chrome.storage.local.set({ clickArea: clickArea }, () => {
                console.log('[区域选择] ✅ 选择区域已保存到存储:', clickArea);
            });
            break;

        case 'statusChanged':
            isClicking = message.isClicking;
            if (message.totalClicks !== undefined) {
                clickCount = message.totalClicks;
            }
            updateUI();
            break;

        case 'clickPerformed':
            clickCount = message.count;
            updateUI();
            break;

        case 'intervalModeUpdate':
            // 间歇模式状态更新
            if (message.intervalModeState) {
                intervalModeState = { ...intervalModeState, ...message.intervalModeState };
                updateUI();
            }
            break;

        case 'phaseChanged':
            // 阶段切换通知
            if (message.phase !== undefined) {
                intervalModeState.currentPhase = message.phase;
                intervalModeState.remainingTime = message.remainingTime || 0;
                intervalModeState.cycleCount = message.cycleCount || 0;
                updateUI();
                console.log(`间歇模式阶段切换: ${message.phase}, 剩余时间: ${message.remainingTime}秒`);
            }
            break;
    }
});
