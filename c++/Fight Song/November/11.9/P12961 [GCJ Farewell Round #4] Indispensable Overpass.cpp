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

int T;
int n, m, k;
ll f[N];
int dep[N], siz[N];
vector<int> e[N];

void Dfs(int u, int fa, int root) {
    siz[u] = 1;
    f[root] += dep[u];
    for (int v : e[u]) {
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        Dfs(v, u, root);
        siz[u] += siz[v];
    }
}
void Dfs1(int u, int fa, int sz) {
    for (int v : e[u]) {
        if (v == fa) continue;
        f[v] = f[u] - siz[v] + (sz - siz[v]);
        // if (v == 2) cerr << siz[v] << "\n";
        Dfs1(v, u, sz);
    }
}
void Solve(int cur) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n + m; i++) {
        e[i].clear();
        f[i] = dep[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int v;
        cin >> v;
        e[i].emplace_back(v);
        e[v].emplace_back(i);
        // cerr << i << " " << v << "\n";
    }
    for (int i = 1; i < m; i++) {
        int v;
        cin >> v;
        e[i + n].emplace_back(v + n);
        e[v + n].emplace_back(i + n);
        // cerr << i + n << " " << v + n << "\n";
    }
    Dfs(1, 0, 1), Dfs(n + 1, 0, n + 1);
    Dfs1(1, 0, n), Dfs1(n + 1, 0, m);
    ll sum1 = 0, sum2 = 0;
    for (int i = 1; i <= n; i++) sum1 += f[i]; sum1 /= 2;
    for (int i = n + 1; i <= n + m; i++) sum2 += f[i]; sum2 /= 2;
    printf("Case #%d: ", cur);
    // cerr << sum1 << " " << sum2 << "\n";
    // for (int i = 1; i <= n + m; i++) printf("f[%d]=%d\n", i, f[i]);
    // for (int i = 1; i <= n + m; i++) printf("dep[%d]=%d\n", i, dep[i]);
    // for (int i = 1; i <= n + m; i++) printf("siz[%d]=%d\n", i, siz[i]);
    while (k--) {
        int x, y;
        cin >> x >> y;
        ll num = sum1 + sum2 + 1LL * m * f[x] + 1LL * n * f[y + n] + 1LL * n * m;
        ll den = 1LL * (n + m) * (n + m - 1) / 2;
        double ans = (double)num / (double)den;
        printf("%.07lf ", ans);
    }
    printf("\n");
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) Solve(_);
    return 0;
}
/*
Dare to love yourself, like loving the morning sun.
敢于去热爱自己，如同爱清晨的太阳
*/