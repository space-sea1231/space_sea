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
const int N = 1e6 + 10;
const int K = 21;

int n;
int a[N], f[N][K];
int cnt[N], top[N], siz[N], dep[N];
bool vis[N];
vector<int> e[N], q[N];

void Dfs(int u, int fa) {
    if (!vis[a[u]]) top[a[u]] = u;
    cnt[a[u]]++; vis[a[u]] = true;
    siz[u] = 1; dep[u] = dep[fa] + 1;

    int tmp = cnt[a[u]];
    for (int v : e[u]) {
        if (v == fa) continue;
        f[v][0] = u;
        for (int k = 1; k < K; k++) f[v][k] = f[f[v][k - 1]][k - 1];
        Dfs(v, u);
        siz[u] += siz[v];
    }
    if (cnt[a[u]] == tmp) q[a[u]].emplace_back(u);
}
int Lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; ~i; i--) {
        if (dep[f[x][i]] >= dep[y]) {
            x = f[x][i];
        }
    }
    if (x == y) return x;
    for (int i = K - 1; ~i; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}
int Lca2(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; ~i; i--) {
        if (dep[f[x][i]] > dep[y]) {
            x = f[x][i];
        }
    }
    return x;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    Dfs(1, 0);
    for (int i = 1; i <= n; i++) if (top[i] && q[i].size() == 1 && q[i][0] != top[i]) q[i].emplace_back(top[i]);
    // for (int i = 1; i <= n; i++) {
    //     printf("%d: ", i);
    //     for (int p:q[i]) printf("%d ", p);
    //     printf("\n");
    // }
    for (int i = 1; i <= n; i++) {
        int sz = q[i].size();
        if (sz == 0) printf("%lld\n", (ll)n * (n - 1) / 2);
        if (sz == 1) {
            int u = q[i][0];
            ll ans = ((ll)n - siz[u] + 1) * siz[u] - 1;
            int tot = 0;
            for (int v : e[u]) {
                if (v == f[u][0]) continue;
                ans += (ll)siz[v] * tot;
                tot += siz[v];
            }
            printf("%lld\n", ans);
        }
        if (sz == 2) {
            int u = q[i][0], v = q[i][1];
            int fa = Lca(u, v);
            if (fa == v) swap(u, v);
            ll ans = 0;
            if (fa == u) {
                ans = (ll)(n - siz[Lca2(u, v)]) * siz[v];
                if (i == 3) cerr << n - siz[u] + 1 << " " << siz[v] << "\n";
            }
            else ans = (ll)siz[u] * siz[v];
            // int tot = 0; 
            // for (int vv : e[v]) {
            //     if (vv == f[v][0]) continue;
            //     ans += (ll)siz[vv] * tot;
            //     tot += siz[vv];
            // }
            printf("%lld\n", ans);
        }
        if (sz > 2) printf("0\n");
    }
    return 0;
}
/*
诶哟喵，又摔跤了，疼疼疼疼疼疼疼，四肢一摔就只剩一个能动了T﹏T
左手扭了，右手擦了，右腿淤了，老天爷良心，没让我四肢瘫痪QAQ
不能打篮球了，钢琴也碰不了，键盘也敲不动了
喵喵喵喵喵，我伤才好一天啊喵#_#

Don't you think about me enough?
你不觉得对我来说已经够了吗？
I've been burning my heart out
我已痛彻心扉
Got to face, need to tell you
我已经选择面对
I won't run because I'm reticent
我不会再逃避只因我本应缄默
You will know you're reborn tonight
你会明白你将在今晚获得新生。
Must be ragged but I stay by your side
即使再艰辛我也会留在你身边
Even if my body bleached to the bones
即使粉身碎骨
I don't wanna go through that ever again
我也不想再次失去你
So cry no more, oh my beloved
别再哭泣，我亲爱的
Go ahead be proud and fight it out
抬起头前行，并奋斗到底
You are the ONE, our rising star
你是唯一，我们的希望之星
You guide us far to home，yea girt
你引导着我们回到遥不可及的家乡
*/