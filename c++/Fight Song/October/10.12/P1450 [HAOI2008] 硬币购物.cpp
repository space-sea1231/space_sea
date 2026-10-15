#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, s;
ll ans;
int c[5], b[5];
ll f[N];
bool vis[5];

void Dfs(int dep, int cnt) {
    if (dep == 5) {
        if (cnt == 0) return;
        int tot = s;
        for (int i = 1; i <= 4; i++) {
            if (vis[i]) {
                tot -= (b[i] + 1) * c[i];
            }
        }
        if (tot >= 0) ans += (cnt & 1 ? -1 : 1) * f[tot];
        return;
    }
    vis[dep] = true;
    Dfs(dep + 1, cnt + 1);
    vis[dep] = false;
    Dfs(dep + 1, cnt);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    f[0] = 1;
    for (int i = 1; i <= 4; i++) cin >> c[i]; cin >> n;
    for (int i = 1; i <= 4; i++) {
        for (int j = c[i]; j < N; j++) {
            f[j] += f[j - c[i]];
        }
    }
    for (int _ = 1; _ <= n; _++) {
        for (int i = 1; i <= 4; i++) cin >> b[i]; cin >> s;
        // int tmp = 4;
        // printf("Debug:f[%d]=%d\n", tmp, f[tmp]);
        ans = f[s]; Dfs(1, 0);
        printf("%lld\n", ans);
    }
    return 0;
}
/*

1 1 1
2 2
5 5 5
10
在这个风起云涌的战场上
暴风少年登场
在战胜烈火重重的咆哮声
喧闹整个世界
硝烟狂飞的讯号
机甲时代正来到
热血逆流而上
战车在发烫
勇士也势不可挡
Come on逆战 逆战来也
王牌要狂野
闯荡宇宙摆平世界
Oh 逆战 逆战狂野
王牌要发泄
战斗是我们倔强起点
我要操控我的权势
张扬我的声势
看这场龙战在野
这战场千百热血战士
一路向前飞驰
捍卫世界的勇士
Fighting 再一决
在这个风起云涌的战场上
暴风少年登场
在战胜烈火重重的咆哮声
喧闹整个世界
硝烟狂飞的讯号
机甲时代正来到
热血逆流而上
战车在发烫
勇士也势不可挡
Come on逆战 逆战来也
王牌要狂野
闯荡宇宙摆平世界
Oh 逆战 逆战狂野
王牌要发泄
战斗是我们倔强起点
我要操控我的权势
张扬我的声势
看这场龙战在野
这战场千百热血战士
一路向前飞驰
捍卫世界的勇士
Fighting 再一决
兄弟一场
未来继续顽强
看着战火飘摇
瓦解对手力量
熊熊气势再出发
逆战 逆战来也
王牌要狂野
闯荡宇宙摆平世界
Oh 逆战 逆战狂野
王牌要发泄
战斗是我们倔强起点
我要操控我的权势
张扬我的声势
看这场龙战在野
这战场千百热血战士
一路向前飞驰
捍卫世界的勇士
Fighting 再一决
*/