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
const int K = 16;

int n, m;
int f[N][K], dep[N], sum[N];
bool vis[N];
bool a[N];
vector<int> e[N];

void Dfs(int u, int fa) {
    sum[u] = sum[fa] + a[u];
    dep[u] = dep[fa] + 1;
    for (int v:e[u]) {
        if (v == fa) continue;
        f[v][0] = u;
        for (int k = 1; k < K; k++) f[v][k] = f[f[v][k - 1]][k - 1];
        Dfs(v, u);
    }
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
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        a[i] = (c == 'G');
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    Dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y;
        char c;
        cin >> x >> y >> c;
        int fa = Lca(x, y);
        if (c == 'H' && (sum[x] - sum[f[fa][0]] != dep[x] - dep[f[fa][0]] || sum[y] - sum[f[fa][0]] != dep[y] - dep[f[fa][0]])) printf("1");
        else if (c == 'G' && (sum[x] - sum[f[fa][0]] != 0 || sum[y] - sum[f[fa][0]] != 0)) printf("1");
        else printf("0");
    }
    return 0;
}