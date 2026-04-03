#!/bin/bash

# ========== 你只需要改这里 ==========
YOUR_QQ="你的QQ号"          # 改成你的QQ
TARGET_QQ="对方QQ号"        # 发给谁
MSG="修炼"                 # 发送内容
SEND_COUNT=20              # 发送次数
WAIT_SECOND=70            # 每次间隔秒数
# ===================================

echo "等待5秒，准备开始发送..."
sleep 5

for ((i=1; i<=SEND_COUNT; i++)); do
    echo "正在发送第 $i 条消息：$MSG"
    
    # 纯Linux自带工具发送，不需要任何安装
    curl -s "https://api.qinfafa.com/api/send/?qq=$YOUR_QQ&user=$TARGET_QQ&msg=$MSG" > /dev/null
    
    echo "发送成功，等待 $WAIT_SECOND 秒后继续"
    sleep $WAIT_SECOND
done

echo "✅ 全部发送完成！"