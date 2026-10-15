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
const int N = 40;
const int M = 1e3 + 10;

int n, m;
int a[M], b[M];
bool q[N], tmp[N];
bool ans;

void Check() {
    for (int i = 1; i <= n; i++) tmp[i] = q[i];
    // for (int i = 1; i <= n; i++) printf("%d ", tmp[i]);
    // printf("\n");
    for (int i = 1; i <= m; i++) {
        if (tmp[a[i]] && !tmp[b[i]]) swap(tmp[a[i]], tmp[b[i]]);
    }
    bool flag1 = false, flag2 = false;
    for (int i = 1; i <= n; i++) {
        if (tmp[i]) {
            flag1 = true;
            if (flag2) return;
        } 
        if (!tmp[i] && flag1) flag2 = true;
    }
    ans ^= 1;
}
void Dfs(int cur, int lst) {
    if (cur == n + 1) {
        Check();
        return;
    }
    if ((n - cur + 1) ^ lst) {
        q[cur] = false;
        Dfs(cur + 1, lst);
    }
    if (lst) {
        q[cur] = true;
        Dfs(cur + 1, lst - 1);
    }
}
// void Dfs(int cur, int lst) {
//     if (cur == n + 1 && lst == 0) {
//         Check();
//         return;
//     }
//     // if ((n - cur + 1) ^ lst) {
//         q[cur] = false;
//         Dfs(cur + 1, lst);
//     // }
//     q[cur] = true;
//     Dfs(cur + 1, lst - 1);
// }
signed main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) {
        ans = false;
        // printf("-----%d-----\n", i);
        Dfs(1, i);
        printf("%d ", ans);
    }

    return 0;
}
/*
第一本：K5杀死巫师，玩的K系列第一本（情怀），而且玩到了关键角色黑猫体验感拉满；
第二本：K15屠龙之证，颠覆式的机制设计简直绝了，而且玩到凶手体验感拉满；
第三本：K12娘娘千岁，已极其优秀的游戏机制和丝毫不差的剧情、推理成为了K的游戏系列爆款top1；
第四本：K14动物监友会，纯因为我们那车玩的就是嗨，是玩的最欢乐的一个本，同时各方面也不差；
第五本：K18谁与争疯，K的游戏系列情感演绎的天花板，同样是爆款；
第六本：K11再见苏西，K的游戏系列立意天花板；
*/