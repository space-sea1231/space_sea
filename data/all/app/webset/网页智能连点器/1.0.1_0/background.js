// 后台脚本 - 处理扩展的后台逻辑
console.log('🎯 智能后台点击器后台脚本已启动');

// 扩展安装时的初始化
chrome.runtime.onInstalled.addListener(() => {
    console.log('智能后台点击器已安装');
    
    // 设置默认存储数据
    chrome.storage.local.set({
        clickArea: null,
        settings: {
            interval: 50,
            randomRange: 20,
            // 间歇模式默认配置
            intervalMode: {
                enabled: false,         // 间歇模式开关
                clickDuration: 15,      // 连点时长（秒）
                pauseDuration: 3        // 暂停时长（秒）
            }
        },
        isClicking: false,
        clickCount: 0,
        // 间歇模式状态
        intervalModeState: {
            currentPhase: 'idle',
            remainingTime: 0,
            cycleCount: 0
        }
    });
});

// 处理来自内容脚本和弹窗的消息
chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    console.log('收到消息:', message);
    
    switch (message.type) {
        case 'areaSelected':
            // 保存选择的区域
            chrome.storage.local.set({
                clickArea: message.area
            });
            console.log('区域已保存:', message.area);
            break;
            
        case 'clickPerformed':
            // 更新点击计数
            chrome.storage.local.set({
                clickCount: message.count
            });
            
            // 可以在这里添加统计逻辑
            console.log(`点击执行: 第${message.count}次，坐标(${message.coordinates.x}, ${message.coordinates.y})`);
            break;
            
        case 'statusChanged':
            // 更新点击状态
            chrome.storage.local.set({
                isClicking: message.isClicking
            });
            
            if (message.totalClicks !== undefined) {
                chrome.storage.local.set({
                    clickCount: message.totalClicks
                });
            }
            
            console.log('状态更新:', message.isClicking ? '开始点击' : '停止点击');
            break;
            
        case 'getStoredData':
            // 获取存储的数据
            chrome.storage.local.get(['clickArea', 'settings', 'isClicking', 'clickCount', 'intervalModeState'], (data) => {
                sendResponse(data);
            });
            return true; // 保持消息通道开放

        case 'updateSettings':
            // 更新设置（支持间歇模式配置）
            chrome.storage.local.set({
                settings: message.settings
            });
            console.log('设置已更新:', message.settings);
            break;

        case 'intervalModeUpdate':
            // 间歇模式状态更新
            if (message.intervalModeState) {
                chrome.storage.local.set({
                    intervalModeState: message.intervalModeState
                });
                console.log('间歇模式状态已更新:', message.intervalModeState);
            }
            break;

        case 'phaseChanged':
            // 阶段切换通知 - 更新存储状态
            const phaseData = {
                currentPhase: message.phase || 'idle',
                remainingTime: message.remainingTime || 0,
                cycleCount: message.cycleCount || 0
            };

            chrome.storage.local.set({
                intervalModeState: phaseData
            });

            console.log(`间歇模式阶段变化: ${message.phase}, 剩余时间: ${message.remainingTime}秒, 循环次数: ${message.cycleCount}`);
            break;
    }
});

// 标签页更新时重置状态
chrome.tabs.onUpdated.addListener((tabId, changeInfo, tab) => {
    if (changeInfo.status === 'complete') {
        // 页面加载完成时重置点击状态和间歇模式状态
        chrome.storage.local.set({
            isClicking: false,
            clickCount: 0,
            intervalModeState: {
                currentPhase: 'idle',
                remainingTime: 0,
                cycleCount: 0
            }
        });
        console.log('页面加载完成，已重置点击状态和间歇模式状态');
    }
});

// 扩展图标点击事件（可选）
chrome.action.onClicked.addListener((tab) => {
    console.log('扩展图标被点击，当前标签页:', tab.url);
});

// 处理快捷键命令
chrome.commands.onCommand.addListener(async (command) => {
    console.log('快捷键触发:', command);

    // 获取当前活动标签页
    const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
    if (!tab) {
        console.error('无法获取当前标签页');
        return;
    }

    try {
        switch (command) {
            case 'toggle-clicking':
                // 切换点击状态
                const data = await chrome.storage.local.get(['isClicking', 'clickArea']);

                if (!data.clickArea) {
                    // 如果没有选择区域，先选择区域
                    await chrome.tabs.sendMessage(tab.id, { type: 'selectArea' });
                    console.log('快捷键触发：选择区域');
                } else if (data.isClicking) {
                    // 如果正在点击，则停止
                    await chrome.tabs.sendMessage(tab.id, { type: 'stopClick' });
                    console.log('快捷键触发：停止点击');
                } else {
                    // 如果没有点击，则开始
                    const storedData = await chrome.storage.local.get(['settings']);
                    const defaultSettings = {
                        interval: 10,
                        randomRange: 5,
                        intervalMode: {
                            enabled: false,
                            clickDuration: 15,
                            pauseDuration: 3
                        }
                    };

                    const finalSettings = {
                        ...defaultSettings,
                        ...(storedData.settings || {}),
                        intervalMode: {
                            ...defaultSettings.intervalMode,
                            ...(storedData.settings?.intervalMode || {})
                        }
                    };

                    await chrome.tabs.sendMessage(tab.id, {
                        type: 'startClick',
                        settings: finalSettings
                    });
                    console.log('快捷键触发：开始点击，设置:', finalSettings);
                }
                break;

            case 'emergency-stop':
                // 紧急停止
                await chrome.tabs.sendMessage(tab.id, { type: 'stopClick' });
                console.log('快捷键触发：紧急停止');
                break;

            case 'select-area':
                // 选择区域
                await chrome.tabs.sendMessage(tab.id, { type: 'selectArea' });
                console.log('快捷键触发：选择区域');
                break;
        }
    } catch (error) {
        console.error('快捷键处理失败:', error);

        // 如果内容脚本未加载，尝试注入
        try {
            await chrome.scripting.executeScript({
                target: { tabId: tab.id },
                files: ['content.js']
            });
            console.log('内容脚本已重新注入');
        } catch (injectError) {
            console.error('注入内容脚本失败:', injectError);
        }
    }
});
