// 内容脚本 - 真正的网页后台点击实现
console.log('🎯 智能后台点击器已加载');
console.log('[Content Script] 页面URL:', window.location.href);
console.log('[Content Script] 加载时间:', new Date().toISOString());

// 显示美化的通知
function showSuccessNotification(message) {
    const notification = document.createElement('div');
    notification.style.cssText = `
        position: fixed;
        top: 30px;
        right: 30px;
        background: linear-gradient(135deg, #48bb78 0%, #38a169 100%);
        color: white;
        padding: 20px 25px;
        border-radius: 12px;
        z-index: 1000000;
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        font-size: 14px;
        font-weight: 500;
        box-shadow: 0 8px 32px rgba(72, 187, 120, 0.4);
        backdrop-filter: blur(10px);
        border: 1px solid rgba(255, 255, 255, 0.2);
        max-width: 300px;
        animation: slideInRight 0.3s ease-out;
    `;

    notification.innerHTML = message.replace(/\n/g, '<br>');

    // 添加动画样式
    const style = document.createElement('style');
    style.textContent = `
        @keyframes slideInRight {
            from {
                opacity: 0;
                transform: translateX(100%);
            }
            to {
                opacity: 1;
                transform: translateX(0);
            }
        }
        @keyframes slideOutRight {
            from {
                opacity: 1;
                transform: translateX(0);
            }
            to {
                opacity: 0;
                transform: translateX(100%);
            }
        }
    `;
    document.head.appendChild(style);

    document.body.appendChild(notification);

    // 3秒后自动消失
    setTimeout(() => {
        notification.style.animation = 'slideOutRight 0.3s ease-out';
        setTimeout(() => {
            if (notification.parentNode) {
                notification.remove();
            }
        }, 300);
    }, 3000);
}

let clickArea = null;
let isClicking = false;
let clickInterval = null;
let clickCount = 0;
let startTime = 0;
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

// 间歇模式状态管理
let intervalModeState = {
    isActive: false,           // 间歇模式是否激活
    currentPhase: 'idle',      // 当前阶段：'idle'|'clicking'|'pausing'
    phaseTimer: null,          // 阶段切换定时器
    countdownTimer: null,      // 倒计时更新定时器
    phaseStartTime: 0,         // 当前阶段开始时间
    remainingTime: 0,          // 当前阶段剩余时间
    cycleCount: 0              // 循环次数统计
};

// 页面加载时清理点击相关状态，防止残留
function initializeCleanState() {
    console.log('[初始化] 清理点击相关残留状态');

    // 重置点击相关状态变量
    isClicking = false;
    clickCount = 0;
    startTime = 0;
    // 注意：不清理clickArea，保留用户选择的区域

    // 清理点击定时器
    if (clickInterval) {
        clearInterval(clickInterval);
        clearTimeout(clickInterval);
        clickInterval = null;
    }

    // 重置间歇模式的运行状态
    intervalModeState.isActive = false;
    intervalModeState.currentPhase = 'idle';
    intervalModeState.phaseStartTime = 0;
    intervalModeState.remainingTime = 0;
    intervalModeState.cycleCount = 0;

    // 清理间歇模式定时器
    if (intervalModeState.phaseTimer) {
        clearTimeout(intervalModeState.phaseTimer);
        intervalModeState.phaseTimer = null;
    }
    if (intervalModeState.countdownTimer) {
        clearInterval(intervalModeState.countdownTimer);
        intervalModeState.countdownTimer = null;
    }

    console.log('[初始化] ✅ 点击状态清理完成');
}

// 在变量声明后执行初始化清理
initializeCleanState();

// 从存储中恢复用户数据，防止刷新后丢失
function restoreUserData() {
    chrome.storage.local.get(['clickArea', 'settings'], (data) => {
        console.log('[数据恢复] 从存储中恢复用户数据:', data);

        if (data.clickArea) {
            clickArea = data.clickArea;
            console.log('[数据恢复] ✅ 恢复选择区域:', clickArea);
        }

        if (data.settings) {
            settings = { ...settings, ...data.settings };
            console.log('[数据恢复] ✅ 恢复用户设置:', settings);
        }
    });
}

// 恢复用户数据
restoreUserData();

// 创建选择区域的覆盖层
function createAreaSelector() {
    const overlay = document.createElement('div');
    overlay.id = 'click-area-selector';
    overlay.style.cssText = `
        position: fixed;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        background: rgba(0, 0, 255, 0.1);
        z-index: 999999;
        cursor: crosshair;
        border: 2px dashed #0066ff;
    `;
    
    const instruction = document.createElement('div');
    instruction.style.cssText = `
        position: fixed;
        top: 30px;
        left: 50%;
        transform: translateX(-50%);
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        color: white;
        padding: 15px 25px;
        border-radius: 12px;
        z-index: 1000000;
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        font-size: 16px;
        font-weight: 500;
        box-shadow: 0 8px 32px rgba(0, 0, 0, 0.3);
        backdrop-filter: blur(10px);
        border: 1px solid rgba(255, 255, 255, 0.2);
        text-align: center;
        animation: slideDown 0.3s ease-out;
    `;
    instruction.innerHTML = `
        <div style="margin-bottom: 8px; font-size: 18px;">🎯</div>
        <div>请拖拽选择点击区域</div>
        <div style="font-size: 12px; opacity: 0.8; margin-top: 5px;">按 ESC 取消选择</div>
    `;

    // 添加动画样式
    const style = document.createElement('style');
    style.textContent = `
        @keyframes slideDown {
            from {
                opacity: 0;
                transform: translateX(-50%) translateY(-20px);
            }
            to {
                opacity: 1;
                transform: translateX(-50%) translateY(0);
            }
        }
    `;
    document.head.appendChild(style);
    
    document.body.appendChild(overlay);
    document.body.appendChild(instruction);
    
    let startX, startY, isSelecting = false;

    // 清理函数
    function cleanupSelection() {
        console.log('[区域选择] 🧹 清理选择界面');

        if (overlay && overlay.parentNode) {
            overlay.remove();
        }
        if (instruction && instruction.parentNode) {
            instruction.remove();
        }
        const selectionBox = document.getElementById('selection-box');
        if (selectionBox) {
            selectionBox.remove();
        }
        const sizeDisplay = document.getElementById('size-display');
        if (sizeDisplay) {
            sizeDisplay.remove();
        }

        // 移除事件监听器
        document.removeEventListener('keydown', escHandler);
        document.removeEventListener('keyup', escHandler);

        console.log('[区域选择] ✅ 选择界面已清理');
    }

    // ESC取消选择 - 增强版
    function escHandler(e) {
        console.log('[区域选择] 🔍 键盘事件:', e.key, e.type);

        if (e.key === 'Escape') {
            e.preventDefault();
            e.stopPropagation();
            console.log('[区域选择] ❌ ESC键按下，取消选择');

            cleanupSelection();

            // 显示取消通知
            showSuccessNotification('❌ 区域选择已取消');
        }
    }

    // 添加键盘事件监听器（同时监听keydown和keyup确保兼容性）
    document.addEventListener('keydown', escHandler, true);
    document.addEventListener('keyup', escHandler, true);

    console.log('[区域选择] ⌨️ ESC键监听器已添加');

    overlay.addEventListener('mousedown', (e) => {
        startX = e.clientX;
        startY = e.clientY;
        isSelecting = true;
        e.preventDefault();
    });
    
    overlay.addEventListener('mousemove', (e) => {
        if (!isSelecting) return;
        
        const currentX = e.clientX;
        const currentY = e.clientY;
        
        const left = Math.min(startX, currentX);
        const top = Math.min(startY, currentY);
        const width = Math.abs(currentX - startX);
        const height = Math.abs(currentY - startY);
        
        overlay.style.background = `rgba(0, 255, 0, 0.2)`;
        overlay.style.border = `2px solid #00ff00`;
        
        // 显示选择框
        const selectionBox = document.getElementById('selection-box') || document.createElement('div');
        selectionBox.id = 'selection-box';
        selectionBox.style.cssText = `
            position: fixed;
            left: ${left}px;
            top: ${top}px;
            width: ${width}px;
            height: ${height}px;
            border: 3px solid #667eea;
            background: rgba(102, 126, 234, 0.15);
            z-index: 1000001;
            pointer-events: none;
            border-radius: 8px;
            box-shadow: 0 4px 20px rgba(102, 126, 234, 0.3);
        `;

        // 添加尺寸显示
        const sizeDisplay = document.getElementById('size-display') || document.createElement('div');
        sizeDisplay.id = 'size-display';
        sizeDisplay.style.cssText = `
            position: fixed;
            left: ${left + width + 10}px;
            top: ${top}px;
            background: rgba(102, 126, 234, 0.9);
            color: white;
            padding: 5px 10px;
            border-radius: 6px;
            font-family: 'Segoe UI', sans-serif;
            font-size: 12px;
            font-weight: 500;
            z-index: 1000002;
            pointer-events: none;
        `;
        sizeDisplay.textContent = `${width} × ${height}`;

        if (!document.getElementById('size-display')) {
            document.body.appendChild(sizeDisplay);
        }
        
        if (!document.getElementById('selection-box')) {
            document.body.appendChild(selectionBox);
        }
    });
    
    overlay.addEventListener('mouseup', (e) => {
        if (!isSelecting) return;
        
        const endX = e.clientX;
        const endY = e.clientY;
        
        clickArea = {
            x: Math.min(startX, endX),
            y: Math.min(startY, endY),
            width: Math.abs(endX - startX),
            height: Math.abs(endY - startY)
        };
        
        console.log('选择的点击区域:', clickArea);

        // 使用统一的清理函数
        cleanupSelection();

        // 通知扩展
        chrome.runtime.sendMessage({
            type: 'areaSelected',
            area: clickArea
        });

        // 显示美化的成功提示
        showSuccessNotification(`
            ✅ 区域选择完成！
            📍 位置: (${clickArea.x}, ${clickArea.y})
            📏 大小: ${clickArea.width} × ${clickArea.height} px
        `);
    });
    

}

// 间歇模式核心控制函数
function startIntervalMode() {
    console.log('[间歇模式] 🔄 启动间歇模式');

    intervalModeState.isActive = true;
    intervalModeState.cycleCount = 0;

    // 显示间歇模式启动通知
    showSuccessNotification(`
        🔄 间歇模式已启动！
        📋 配置: 连点${settings.intervalMode.clickDuration}秒 → 暂停${settings.intervalMode.pauseDuration}秒
        ⚡ 点击间隔: ${settings.interval}ms + 随机${settings.randomRange}ms
        🎯 即将开始第1轮连点...
    `);

    // 延迟1秒后开始第一个连点阶段，让用户看到通知
    setTimeout(() => {
        switchToClickingPhase();
    }, 1000);
}

// 切换到连点阶段
function switchToClickingPhase() {
    console.log('[间歇模式] 🎯 切换到连点阶段');

    intervalModeState.currentPhase = 'clicking';
    intervalModeState.phaseStartTime = Date.now();
    intervalModeState.remainingTime = settings.intervalMode.clickDuration;
    intervalModeState.cycleCount++;

    // 显示阶段切换通知
    showSuccessNotification(`
        🎯 间歇模式 - 第${intervalModeState.cycleCount}轮
        开始连点 ${settings.intervalMode.clickDuration} 秒
        ⏱️ 点击间隔: ${settings.interval}ms
    `);

    // 开始实际的点击操作
    startActualClicking();

    // 启动倒计时更新
    startPhaseCountdown();

    // 设置阶段切换定时器
    intervalModeState.phaseTimer = setTimeout(() => {
        // 安全检查：确保间歇模式仍然激活且正在点击
        if (intervalModeState.isActive && isClicking) {
            switchToPausingPhase();
        } else {
            console.log('[间歇模式] 阶段切换被取消：模式已停止');
        }
    }, settings.intervalMode.clickDuration * 1000);

    // 通知状态变化
    notifyPhaseChange();
}

// 切换到暂停阶段
function switchToPausingPhase() {
    console.log('[间歇模式] ⏸️ 切换到暂停阶段');

    intervalModeState.currentPhase = 'pausing';
    intervalModeState.phaseStartTime = Date.now();
    intervalModeState.remainingTime = settings.intervalMode.pauseDuration;

    // 显示阶段切换通知
    showSuccessNotification(`
        ⏸️ 间歇模式 - 第${intervalModeState.cycleCount}轮
        开始暂停 ${settings.intervalMode.pauseDuration} 秒
        📊 本轮点击: ${clickCount.toLocaleString()} 次
    `);

    // 停止实际的点击操作
    stopActualClicking();

    // 启动倒计时更新
    startPhaseCountdown();

    // 设置阶段切换定时器
    intervalModeState.phaseTimer = setTimeout(() => {
        // 安全检查：确保间歇模式仍然激活且正在点击
        if (intervalModeState.isActive && isClicking) {
            switchToClickingPhase(); // 继续下一轮循环
        } else {
            console.log('[间歇模式] 循环被终止：模式已停止');
        }
    }, settings.intervalMode.pauseDuration * 1000);

    // 通知状态变化
    notifyPhaseChange();
}

// 启动阶段倒计时更新
function startPhaseCountdown() {
    // 清理之前的倒计时定时器
    if (intervalModeState.countdownTimer) {
        clearInterval(intervalModeState.countdownTimer);
    }

    // 每秒更新一次剩余时间
    intervalModeState.countdownTimer = setInterval(() => {
        const elapsed = (Date.now() - intervalModeState.phaseStartTime) / 1000;
        const totalDuration = intervalModeState.currentPhase === 'clicking'
            ? settings.intervalMode.clickDuration
            : settings.intervalMode.pauseDuration;

        intervalModeState.remainingTime = Math.max(0, Math.ceil(totalDuration - elapsed));

        // 通知剩余时间更新
        notifyPhaseChange();

        // 如果时间到了，清理定时器
        if (intervalModeState.remainingTime <= 0) {
            clearInterval(intervalModeState.countdownTimer);
            intervalModeState.countdownTimer = null;
        }
    }, 1000);
}

// 通知阶段变化
function notifyPhaseChange() {
    try {
        // 检查扩展上下文是否有效
        if (!chrome.runtime?.id) {
            console.warn('[间歇模式] 扩展上下文已失效，停止通知');
            // 清理所有定时器和状态
            stopClicking();
            return;
        }

        chrome.runtime.sendMessage({
            type: 'phaseChanged',
            phase: intervalModeState.currentPhase,
            remainingTime: intervalModeState.remainingTime,
            cycleCount: intervalModeState.cycleCount
        });
    } catch (error) {
        console.error('[间歇模式] 通知状态变化失败:', error);
        // 如果是扩展上下文失效，清理状态
        if (error.message.includes('Extension context invalidated')) {
            console.warn('[间歇模式] 检测到扩展上下文失效，清理所有状态');
            stopClicking();
        }
    }
}

// 停止间歇模式
function stopIntervalMode() {
    console.log('[间歇模式] 🛑 停止间歇模式');

    intervalModeState.isActive = false;
    intervalModeState.currentPhase = 'idle';
    intervalModeState.remainingTime = 0;

    // 清理所有定时器
    if (intervalModeState.phaseTimer) {
        clearTimeout(intervalModeState.phaseTimer);
        intervalModeState.phaseTimer = null;
        console.log('[间歇模式] 阶段切换定时器已清理');
    }

    if (intervalModeState.countdownTimer) {
        clearInterval(intervalModeState.countdownTimer);
        intervalModeState.countdownTimer = null;
        console.log('[间歇模式] 倒计时定时器已清理');
    }

    // 停止实际点击
    stopActualClicking();

    // 通知状态变化
    notifyPhaseChange();

    console.log('[间歇模式] 所有资源已清理完成');
}

// 执行真正的后台点击 - 优化版
function performBackgroundClick() {
    if (!clickArea || !isClicking) return;

    const startTime = performance.now();

    // 在选定区域内生成随机坐标
    const randomX = clickArea.x + Math.random() * clickArea.width;
    const randomY = clickArea.y + Math.random() * clickArea.height;

    // 获取目标位置的元素
    const targetElement = document.elementFromPoint(randomX, randomY);

    if (targetElement) {
        // 优化：只在需要时输出详细日志
        if (clickCount % 100 === 0) {
            console.log(`[后台点击] 第${clickCount}次点击: 目标元素`, targetElement.tagName, targetElement.className);
        }

        // 创建高性能的鼠标事件序列
        const eventOptions = {
            view: window,
            bubbles: true,
            cancelable: true,
            clientX: randomX,
            clientY: randomY,
            button: 0
        };

        // 使用更高效的事件触发方式
        try {
            // 方法1: 直接点击事件（最快）
            const clickEvent = new MouseEvent('click', {
                ...eventOptions,
                buttons: 0
            });
            targetElement.dispatchEvent(clickEvent);

            // 方法2: 如果需要更真实的事件序列（可选）
            if (settings.interval >= 5) {
                const mousedownEvent = new MouseEvent('mousedown', {
                    ...eventOptions,
                    buttons: 1
                });
                const mouseupEvent = new MouseEvent('mouseup', {
                    ...eventOptions,
                    buttons: 0
                });

                targetElement.dispatchEvent(mousedownEvent);
                targetElement.dispatchEvent(mouseupEvent);
            }

            // 优化：只对特定元素触发焦点
            if (targetElement.tagName === 'INPUT' || targetElement.tagName === 'BUTTON' || targetElement.tagName === 'A') {
                if (targetElement.focus && typeof targetElement.focus === 'function') {
                    targetElement.focus();
                }
            }

        } catch (error) {
            console.warn(`[后台点击] 事件触发失败:`, error);
        }

        clickCount++;

        // 优化：减少消息发送频率
        if (clickCount % 10 === 0) {
            chrome.runtime.sendMessage({
                type: 'clickPerformed',
                count: clickCount,
                coordinates: { x: Math.round(randomX), y: Math.round(randomY) }
            });
        }

        // 性能监控
        const duration = performance.now() - startTime;
        if (duration > 5) {
            console.warn(`[后台点击] 点击耗时过长: ${duration.toFixed(2)}ms`);
        }

    } else {
        console.warn(`[后台点击] 未找到目标元素: (${randomX}, ${randomY})`);
    }
}

// 开始点击 - 高性能版（支持间歇模式）
function startClicking() {
    if (!clickArea) {
        showSuccessNotification('❌ 请先选择点击区域！');
        return;
    }

    if (isClicking) {
        console.warn('[后台点击] 点击已在进行中，忽略重复启动');
        return;
    }

    // 参数验证
    if (settings.intervalMode && settings.intervalMode.enabled) {
        if (settings.intervalMode.clickDuration < 1 || settings.intervalMode.clickDuration > 300) {
            showSuccessNotification('❌ 连点时长必须在1-300秒之间！');
            return;
        }
        if (settings.intervalMode.pauseDuration < 1 || settings.intervalMode.pauseDuration > 60) {
            showSuccessNotification('❌ 暂停时长必须在1-60秒之间！');
            return;
        }
    }

    isClicking = true;
    clickCount = 0;
    startTime = Date.now();

    console.log(`[后台点击] 🚀 开始点击，间隔: ${settings.interval}ms + 随机${settings.randomRange}ms`);
    console.log('[后台点击] 完整设置对象:', JSON.stringify(settings, null, 2));

    try {
        // 检查是否启用间歇模式
        if (settings.intervalMode && settings.intervalMode.enabled) {
            console.log(`[间歇模式] ✅ 启用间歇模式：连点${settings.intervalMode.clickDuration}秒，暂停${settings.intervalMode.pauseDuration}秒`);
            startIntervalMode();
        } else {
            console.log('[普通模式] ✅ 启用连续点击模式');
            console.log('[普通模式] intervalMode状态:', settings.intervalMode);
            startActualClicking();
        }

        // 通知扩展状态变化
        chrome.runtime.sendMessage({
            type: 'statusChanged',
            isClicking: true
        });
    } catch (error) {
        console.error('[后台点击] 启动失败:', error);
        isClicking = false;
        showSuccessNotification('❌ 启动失败，请重试！');
    }
}

// 开始实际的点击操作（从原startClicking函数中提取）
function startActualClicking() {
    // 如果间歇模式激活且当前不是连点阶段，则不执行点击
    if (intervalModeState.isActive && intervalModeState.currentPhase !== 'clicking') {
        return;
    }

    console.log(`[实际点击] 开始执行点击，间隔: ${settings.interval}ms + 随机${settings.randomRange}ms`);

    // 计算实际的点击间隔（包含随机延迟）
    function getRandomInterval() {
        const baseInterval = settings.interval;
        const randomDelay = Math.random() * (settings.randomRange || 0);
        return baseInterval + randomDelay;
    }

    // 对于极高速点击，使用requestAnimationFrame优化
    if (settings.interval <= 5 && settings.randomRange <= 2) {
        console.log(`[实际点击] ⚡ 启用极速模式 (${settings.interval}ms + 随机${settings.randomRange}ms)`);

        let lastClickTime = 0;
        let nextClickDelay = getRandomInterval();

        function highSpeedClick() {
            // 检查是否应该继续点击
            if (!isClicking) return;
            if (intervalModeState.isActive && intervalModeState.currentPhase !== 'clicking') return;

            const now = performance.now();
            if (now - lastClickTime >= nextClickDelay) {
                performBackgroundClick();
                lastClickTime = now;
                nextClickDelay = getRandomInterval(); // 计算下次点击的延迟
            }

            requestAnimationFrame(highSpeedClick);
        }

        requestAnimationFrame(highSpeedClick);

    } else {
        // 普通速度使用setTimeout实现真正的随机间隔
        function scheduleNextClick() {
            // 检查是否应该继续点击
            if (!isClicking) return;
            if (intervalModeState.isActive && intervalModeState.currentPhase !== 'clicking') return;

            const randomInterval = getRandomInterval();
            clickInterval = setTimeout(() => {
                performBackgroundClick();
                scheduleNextClick(); // 递归调度下一次点击
            }, randomInterval);
        }

        scheduleNextClick();
    }
}

// 停止实际的点击操作
function stopActualClicking() {
    console.log('[实际点击] 🛑 停止点击操作');

    // 清理点击定时器（支持setTimeout和setInterval）
    if (clickInterval) {
        clearTimeout(clickInterval);
        clearInterval(clickInterval);
        clickInterval = null;
    }
}

// 停止点击
function stopClicking() {
    if (!isClicking) return;

    isClicking = false;

    // 停止间歇模式（如果激活）
    if (intervalModeState.isActive) {
        stopIntervalMode();
    }

    // 停止实际点击
    stopActualClicking();

    console.log(`[后台点击] 🛑 停止点击，总共点击了 ${clickCount} 次`);

    // 显示停止通知
    const duration = (Date.now() - startTime) / 1000;
    const avgSpeed = duration > 0 ? Math.round(clickCount / duration) : 0;

    let notificationText = `
        🛑 点击已停止
        📊 总计点击: ${clickCount.toLocaleString()} 次
        ⏱️ 平均速度: ${avgSpeed} 次/秒
    `;

    // 如果是间歇模式，添加循环次数信息
    if (settings.intervalMode && settings.intervalMode.enabled && intervalModeState.cycleCount > 0) {
        notificationText += `\n🔄 完成循环: ${intervalModeState.cycleCount} 轮`;
    }

    showSuccessNotification(notificationText);

    // 通知扩展状态变化
    chrome.runtime.sendMessage({
        type: 'statusChanged',
        isClicking: false,
        totalClicks: clickCount
    });
}

// 监听来自扩展的消息
chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    console.log('[消息监听] 收到消息:', message.type, message);

    switch (message.type) {
        case 'selectArea':
            console.log('[选择区域] 开始创建区域选择器');
            try {
                createAreaSelector();
                console.log('[选择区域] ✅ 区域选择器创建成功');
                sendResponse({ success: true });
            } catch (error) {
                console.error('[选择区域] 创建区域选择器失败:', error);
                sendResponse({ success: false, error: error.message });
            }
            break;

        case 'startClick':
            // 合并设置，确保间歇模式配置正确传递
            if (message.settings) {
                settings = {
                    ...settings,
                    ...message.settings,
                    intervalMode: {
                        ...settings.intervalMode,
                        ...(message.settings.intervalMode || {})
                    }
                };
            }
            console.log('[消息处理] 收到开始点击消息，设置:', settings);
            startClicking();
            break;

        case 'stopClick':
            stopClicking();
            break;

        case 'getStatus':
            sendResponse({
                isClicking,
                clickCount,
                clickArea,
                settings,
                intervalModeState: {
                    isActive: intervalModeState.isActive,
                    currentPhase: intervalModeState.currentPhase,
                    remainingTime: intervalModeState.remainingTime,
                    cycleCount: intervalModeState.cycleCount
                }
            });
            break;
    }
});

// 页面卸载时清理
window.addEventListener('beforeunload', () => {
    console.log('[页面卸载] 清理所有定时器和状态');
    stopClicking();

    // 额外清理间歇模式相关定时器
    if (intervalModeState.phaseTimer) {
        clearTimeout(intervalModeState.phaseTimer);
    }
    if (intervalModeState.countdownTimer) {
        clearInterval(intervalModeState.countdownTimer);
    }
});
