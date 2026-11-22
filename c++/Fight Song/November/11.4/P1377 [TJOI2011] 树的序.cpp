#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n;
int top;
int a[N];
int pos[N], stk[N];

namespace Tree {
    int root, num;
    struct Node {
        int val;
        int lson, rson;
    }; Node node[N];
    
    void Dfs(int u) {
        printf("%d ", u);
        if (node[u].lson) Dfs(node[u].lson);
        if (node[u].rson) Dfs(node[u].rson);
    }
} using namespace Tree;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k && pos[stk[k]] > pos[i]) k--;
        if (k) node[stk[k]].rson = i; // printf("Debug:%d.rson->%d\n", k, i);}
        if (k < top) node[i].lson = stk[k + 1]; // printf("Debug:%d.lson->%d\n", i, k + 1);}
        stk[++k] = i;
        top = k;
    }
    Dfs(stk[1]);
    return 0;
}

/*
王俊凯：跟着我 左手
右手 一个慢动作
右手 左手 慢动作重播
易烊千玺：这首歌 给你快乐
你有没有爱上我
王源：跟着我 鼻子
眼睛 动一动耳朵
装乖 耍帅 换不停风格
合：青春有太多
未知的猜测
成长的烦恼算什么
王源：皮鞋擦亮 换上西装
佩戴上一克拉的梦想
易烊千玺：我的勇敢充满电量
昂首到达每一个地方
王俊凯：这世界 的太阳
因为自信才能把我照亮
这舞台 的中央
合：有我才闪亮
有我才能发着光
合：跟着我 左手 右手
一个慢动作
右手 左手慢动作重播
这首歌 给你快乐
你有没有爱上我
跟着我 鼻子眼睛
动一动耳朵
装乖 耍帅 换不停风格
青春有太多 未知的猜测
成长的烦恼算什么
王源：经常会想 长大多好
有些事情却只能想象
易烊千玺：想说就说 想做就做
为了明天的自己鼓掌
王俊凯：这世界 的太阳
因为自信才能把我照亮
这舞台 的中央
合：有我才闪亮
有我才能发着光
合：跟着我左手 右手
一个慢动作
右手 左手 慢动作重播
这首歌 给你快乐
你有没有爱上我
跟着我 鼻子 眼睛
动一动耳朵
装乖 耍帅 换不停风格
青春有太多 未知的猜测
成长的烦恼算什么
王俊凯：向明天 对不起
向前冲 不客气
一路有你 充满斗志无限动力
合：男子汉 没有什么输不起
正太修炼成功的秘籍
王源：跟着我左手 右手
一个慢动作
易烊千玺：右手 左手 慢动作重播
王俊凯：这首歌 给你快乐
你有没有爱上我
合：跟着我鼻子眼睛
动一动耳朵
装乖 耍帅 换不停风格
青春有太多 未知的猜测
成长的烦恼算什么
HEY
TFBOYS
*/