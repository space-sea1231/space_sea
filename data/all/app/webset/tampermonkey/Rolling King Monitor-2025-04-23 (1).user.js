// ==UserScript==
// @name         Rolling King Monitor
// @namespace    http://tampermonkey.net/
// @version      2025-04-23
// @description  Monitor Rolling Kings
// @author       Shaojia
// @match        https://www.luogu.com.cn/problem/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=luogu.com.cn
// @grant        GM_xmlhttpRequest
// ==/UserScript==

(function() {
    'use strict';

    // --- 配置区域 ---
    // 寻找初始状态为“展开”的按钮
    const buttonSelector = 'a:has(svg.fa-expand-wide)';
    // 侧边栏的选择器
    const sidePanelSelector = 'div[data-v-754e1ea4].side';
    // --- 配置区域结束 ---


    const observer = new MutationObserver((mutationsList, observer) => {
        const toggleButton = document.querySelector(buttonSelector);
        const sidePanel = document.querySelector(sidePanelSelector);

        // 确保两个元素都已找到，并且我们还没有附加过事件监听器
        if (toggleButton && sidePanel && !toggleButton.dataset.handlerAttached) {
            console.log('成功找到目标按钮和侧边栏，正在附加新功能...');

            // 1. 给按钮做一个标记，防止重复附加事件
            toggleButton.dataset.handlerAttached = 'true';

            // 2. 附加新的点击事件
            toggleButton.addEventListener('click', (event) => {
                // 阻止元素的默认行为和事件冒泡
                event.preventDefault();
                event.stopPropagation();

                // 获取按钮内部需要修改的元素
                const svgIcon = toggleButton.querySelector('svg');
                // <a> 标签的最后一个子节点通常是文本节点
                let textNode = toggleButton.lastChild;

                // 检查按钮的当前状态 (通过SVG图标的类名来判断)
                if (svgIcon.classList.contains('fa-expand-wide')) {
                    // --- 当前是“展开”状态，执行隐藏操作 ---
                    // 1. 隐藏侧边栏
                    sidePanel.style.display = 'none';

                    // 2. 更新按钮为“折叠”状态
                    toggleButton.innerHTML = toggleButton.innerHTML.replace(/展开/g, "折叠");
                    svgIcon.classList.remove('fa-expand-wide');
                    svgIcon.classList.add('fa-compress-wide');

                    console.log('侧边栏已隐藏，按钮更新为“折叠”。');

                } else {
                    // --- 当前是“折叠”状态，执行显示操作 ---
                    // 1. 显示侧边栏 (恢复默认 display)
                    sidePanel.style.display = '';

                    // 2. 更新按钮为“展开”状态
                    toggleButton.innerHTML = toggleButton.innerHTML.replace(/折叠/g, "展开");
                    svgIcon.classList.remove('fa-compress-wide');
                    svgIcon.classList.add('fa-expand-wide');

                    console.log('侧边栏已显示，按钮更新为“展开”。');
                }
            }, true); // 使用事件捕获确保我们的脚本最先执行

            console.log('新功能已成功附加。');

            // 脚本成功运行一次后，我们可以选择断开观察者以节省资源。
            // 如果您担心按钮会被网站动态移除再重新创建，可以注释掉下面这行。
            observer.disconnect();
        }
    });

    // 开始观察整个文档
    observer.observe(document.body, {
        childList: true,
        subtree: true
    });

    if (location.pathname.startsWith('/problem/solution/')) return;

    const users = [
        // cj
        756684,732175,746790,681610,360083,704234,508927,673867,694969,700547,717599,748239
    ];

    let contentDivRef = null;
    let hasInserted = false;
    let remainingRequests = 0
    let used = new Map();
    let checked = new Map();

    // 向卷王区域插入一行 HTML
    const ins = (str) => {
        hasInserted = true;
        contentDivRef.innerHTML += str;
    };

    // 所有请求完成后的收尾处理
    const handleRequestDone = () => {
        remainingRequests--;
        if (remainingRequests === 0) {
            setTimeout(() => {
                ins(`<a style="font-weight:bold;color:#666666">已完成检查</a><br>`);
            }, 1000);
        }
    };

    // 根据用户名关键字去 OJ 接口拿真实用户名
    async function fetchUserName(keyword) {
        const url = `https://www.luogu.com.cn/api/user/search?keyword=${keyword}`;
        let response;
        while (true) {
            try {
                response = await fetch(url);
                if (response.ok) break;
            } catch (err) {}
            await new Promise(r => setTimeout(r, 1000));
        }
        const data = await response.json();
        return (data.users && data.users.length) ? data.users[0].name : null;
    }

    // 拉取某个用户的 AC/提交记录
    const get_record = (pid, user) => {
        const tryRequest = (status) => {
            GM_xmlhttpRequest({
                method: 'GET',
                url: `https://www.luogu.com.cn/record/list?_contentOnly=1&status=${status}&pid=${pid}&user=${user}`,
                onload: res => {
                    if (res.status !== 200) {
                        tryRequest(status);
                        return;
                    }
                    handleRequestDone();
                    const data = JSON.parse(res.responseText);
                    if (data.currentData.records.result.length > 0) {
                        let info = data.currentData.records.result[0].user;
                        let color = status === 12 ? 'rgb(82, 196, 26)' : 'rgb(231, 76, 60)';
                        if (status === 14 && used.has(user)) return;
                        let str = `<a style="font-weight:bold;color:${color}" ` +
                                  `href="https://www.luogu.com.cn/record/list?pid=${pid}&user=${info.uid}">` +
                                  `${info.name}</a><br>`;
                        ins(str);
                        if (status === 12) used.set(user, 1);
                        checked.set(user, 1);
                    } else if (status === 14) {
                        if (used.has(user)) return;
                        fetchUserName(user.toString()).then(name => {
                            let str = `<a style="font-weight:bold;color:#cccccc" ` +
                                      `href="https://www.luogu.com.cn/record/list?pid=${pid}&user=${user}">` +
                                      `${name}</a><br>`;
                            ins(str);
                        });
                    }
                },
                onerror: () => tryRequest(status)
            });
        };
        tryRequest(12);
        tryRequest(14);
    };

    const main = () => {
        const url = location.href;
        const l = url.lastIndexOf('/'), q = url.indexOf('?');
        const r = q === -1 ? url.length : q;
        const hashIdx = url.indexOf('#');
        const end = (hashIdx !== -1 && hashIdx < r) ? hashIdx : r;
        const pid = url.substring(l + 1, end);

        remainingRequests = users.length * 2;

        // 等待侧栏加载完成
        const sideInit = setInterval(() => {
            const side = document.querySelector('div[data-v-754e1ea4].side');
            if (!side) return;
            clearInterval(sideInit);

            // 构造 l-card 容器
            const card = document.createElement('div');
            card.setAttribute('data-v-b62e56e7', '');
            card.setAttribute('data-v-f0a51f8c', '');
            card.setAttribute('data-v-754e1ea4-s', '');
            card.classList.add('l-card');

            // 标题
            const h3 = document.createElement('h3');
            h3.setAttribute('data-v-f0a51f8c', '');
            h3.classList.add('lfe-h3');
            h3.innerText = '卷王';

            // 内容区
            const innerDiv = document.createElement('div');
            innerDiv.setAttribute('data-v-f0a51f8c', '');
            innerDiv.innerHTML = '';  // 最初为空
            contentDivRef = innerDiv;

            card.appendChild(h3);
            card.appendChild(innerDiv);

            // 添加隐藏/展开按钮
            const captionDiv = document.createElement('div');
            captionDiv.setAttribute('data-v-f0a51f8c', '');
            captionDiv.classList.add('lfe-caption');
            captionDiv.style.textAlign = 'center';

            const captionSpan = document.createElement('span');
            captionSpan.setAttribute('data-v-47eac1f0', '');
            captionSpan.setAttribute('data-v-f0a51f8c', '');
            captionSpan.classList.add('expand-indicator');
            captionDiv.appendChild(captionSpan);

            const chevronUpSvg = `<svg data-v-47eac1f0="" class="svg-inline--fa fa-chevron-up icon" aria-hidden="true" focusable="false" data-prefix="fal" data-icon="chevron-up" role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512"><path class="" fill="currentColor" d="M244.7 116.7c6.2-6.2 16.4-6.2 22.6 0l192 192c6.2 6.2 6.2 16.4 0 22.6s-16.4 6.2-22.6 0L256 150.6 75.3 331.3c-6.2 6.2-16.4 6.2-22.6 0s-6.2-16.4 0-22.6l192-192z"></path></svg>`;
            const chevronDownSvg = `<svg data-v-47eac1f0="" class="svg-inline--fa fa-chevron-down icon" aria-hidden="true" focusable="false" data-prefix="fal" data-icon="chevron-down" role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512"><path class="" fill="currentColor" d="M267.3 395.3c-6.2 6.2-16.4 6.2-22.6 0l-192-192c-6.2-6.2-6.2-16.4 0-22.6s16.4-6.2 22.6 0L256 361.4 436.7 180.7c6.2-6.2 16.4-6.2 22.6 0s6.2 16.4 0 22.6l-192 192z"></path></svg>`;

            let collapsed = false;
            const renderCaption = () => {
                if (collapsed) {
                    captionSpan.innerHTML = chevronDownSvg + '展开';
                } else {
                    captionSpan.innerHTML = chevronUpSvg + '隐藏';
                }
            };
            renderCaption();

            captionDiv.addEventListener('click', () => {
                collapsed = !collapsed;
                innerDiv.style.display = collapsed ? 'none' : '';
                renderCaption();
            });

            card.appendChild(captionDiv);

            // 追加到侧栏最下面
            side.appendChild(card);

            // 开始轮询各用户记录
            let idx = 0;
            const timer = setInterval(() => {
                if (idx >= users.length) {
                    clearInterval(timer);
                    return;
                }
                get_record(pid, users[idx]);
                idx++;
            }, 100);
        }, 100);

        console.log("Rolling King Monitor initialized.");
    };

    main();

    function hideParentDivs() {
        const buttons = document.querySelectorAll('button.close.button-transparent');
        buttons.forEach(button => {
            const parentDiv = button.closest('div');
            if (parentDiv && parentDiv.style.display !== 'none') {
                parentDiv.style.display = 'none';
            }
        });
    }

    // 初始执行一次
    hideParentDivs();

    // 监听 DOM 变化
    const observers = new MutationObserver(() => {
        hideParentDivs();
    });

    observers.observe(document.body, {
        childList: true,
        subtree: true
    });
})();