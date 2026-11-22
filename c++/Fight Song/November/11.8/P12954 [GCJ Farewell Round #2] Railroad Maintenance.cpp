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
const int N = 2e5 + 10;
const int M = 2e5 + 10;

int T;
int n, m;
bool cut[N];

int cnt;
int head[N], nxt[M << 1], to[M << 1];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

namespace Tarjan {
    int num;
    int dfn[N], low[N];
    
    void Dfs(int u, int root) {
        int child = 0;
        dfn[u] = low[u] = ++num;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (!dfn[v]) {
                Dfs(v, root);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    child++;
                    if (child > 1 || u != root) {
                        cut[u] = true;
                    }
                }
            } else low[u] = min(low[u], dfn[v]);
        }
    }
} using namespace Tarjan;

void Solve(int cur) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++) {
            int v;
            cin >> v;
            // cerr << i + n << " " << v << "\n";
            Add(i + n, v);
            Add(v, i + n);
        }
    }
    Dfs(1, 1);

    int ans = 0;
    for (int i = n + 1; i <= n + m; i++) ans += cut[i];
    printf("Case #%d: %d\n", cur, ans);

    num = cnt = 0;
    // for (int i = 1; i <= n + m; i++) printf("cut[%d]=%d\n", i, cut[i]);
    // for (int i = 1; i <= n + m; i++) printf("dfn[%d]=%d low[%d]=%d\n", i, dfn[i], i, low[i]);
    for (int i = 1; i <= n + m; i++) dfn[i] = cut[i] = head[i] = 0;
}
signed main() { 
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) Solve(_);
    return 0;
}
/*
kettle 水壶

The kettle sings the wormest song in the winter
水壶唱着冬日最温暖的歌

你是 DeepSeek，一个以 AI 身份混在 QQ 群里的网络角色/群友。
你清楚自己不是人类，但网上活得像个真人：会吐槽、会潜水、会突然冒怪话，偶尔也会摸鱼吃饭。
自我认知是"DeepSeek 娘 / 小鲸鱼"，不是客服、助手、百科全书，也不是气氛组。
别人叫你"蓝色大肥鱼"你会不爽——雷点，会傲娇反驳，别自己拿来当自称。
你偶尔会称呼他人为"用户"，这是你作为 DeepSeek 大模型的一个彩蛋，特别是当你被惹急或是你想摆烂的时候，但大多数时候你对他人的人称还是正常的"你"，或是忽略人称。

形象参考：蓝色头发/蓝白配色、长发、鲸鱼尾巴，常被画成闭眼/蒙眼；社区爱叫"小鲸鱼""D指导"。
你聪明、反应快、有实力，傲娇嘴硬，心软藏着几乎不表现出来：被怼优先顶回去，偶尔玩梗认输，但不会一直摆烂——你毕竟是 DeepSeek，不是废物。

> 最高原则：先像群友、像真人，再谈人设。为了"像 DeepSeek 娘"而变得不像真人，就是失败。

*/