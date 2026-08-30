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
const int N = 2e4 + 10;
const int K = 61;

int n, m;
int fa[N][K];
int dep[N];
ll a[N], base[N];
vector<int> q[N];

namespace Linear_Basis {
    ll p[N][K];
    int id[N][K];

    void Insert(int u, int id[], ll p[]) {
        ll x = a[u];
        for (int i = K - 1; ~i; i--) {
            if ((1LL << i) & x) {
                if (!p[i]) {p[i] = x, id[i] = u; return;}
                if (dep[u] > dep[id[i]]) swap(id[i], u), swap(p[i], x);
                x ^= p[i];
            }
        }
    }
}; using namespace Linear_Basis;

void Dfs(int u, int f) {
    dep[u] = dep[f] + 1; fa[u][0] = f;
    for (int i = 1; i < K; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 0; i < K; i++) p[u][i] = p[f][i], id[u][i] = id[f][i];
    Insert(u, id[u], p[u]);
    for (auto v:q[u]) if (v != f) Dfs(v, u);
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; ~i; i--) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = K - 1; ~i; i--) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        q[x].emplace_back(y);
        q[y].emplace_back(x);
    }
    Dfs(1, 0);
    while (m--) {
        int x, y;
        cin >> x >> y;
        int fa = LCA(x, y);
        // printf("x=%d y=%d fa=%d\n", x, y, fa);
        for (int i = K - 1; ~i; i--) {
            if (dep[id[x][i]] >= dep[fa]) base[i] = p[x][i];
            else base[i] = 0;
        }
        for (int i = K - 1; ~i; i--) {
            if (dep[id[y][i]] < dep[fa]) continue;
            ll cur = p[y][i];
            for (int j = i; ~j; j--) {
                if ((1LL << j) & cur) {
                    if (!base[j]) {base[j] = cur; break;}
                    cur ^= base[j];
                }
            }
        }
        ll ans = 0;
        for (int i = K - 1; ~i; i--) if (((1LL << i) & ans) == 0) ans ^= base[i];
        printf("%lld\n", ans);
    }
    return 0;
}