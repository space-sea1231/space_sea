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
const int K = 20;

int n, X, Y;
int ans;
int f[N][K];
int depb[N], depa[N];
bool vis[N];
vector<int> e1[N], e2[N];
pair<int, int> edge[N];

void Dfs1(int u, int fa) { // A剑旗 B凯撒
    depb[u] = depb[fa] + 1;
    for (int v : e2[u]) {
        if (v == fa) continue;
        f[v][0] = u;
        for (int i = 1; i < K; i++) f[v][i] = f[f[v][i - 1]][i - 1];
        Dfs1(v, u);
    }
}
void Dfs2(int u, int fa) {
    depa[u] = depa[fa] + 1;
    if (depa[u] >= depb[u]) return ;
    if (vis[u]) { printf("forever\n"), exit(0); }
    ans = max(ans, depb[u]);
    for (int v : e1[u]) {
        if (v == fa) continue;
        Dfs2(v, u);
    }
}
int Dist(int x, int y) {
    if (depb[x] < depb[y]) swap(x, y);
    int dis = 0;
    for (int i = K - 1; ~i; i--) {
        if (depb[f[x][i]] >= depb[y]) {
            x = f[x][i];
            dis += (1 << i);
        }
    }
    if (x == y) return dis;
    for (int i = K - 1; ~i; i--) {
        if (f[x][i] ^ f[y][i]) {
            x = f[x][i];
            y = f[y][i];
            dis += (1 << i + 1);
        }
    }
    return dis + 2;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> X >> Y;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e1[u].emplace_back(v);
        e1[v].emplace_back(u);
        edge[i] = make_pair(u, v);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e2[u].emplace_back(v);
        e2[v].emplace_back(u);
    }
    depa[0] = depb[0] = -1;
    Dfs1(Y, 0);
    for (int i = 1; i < n; i++) {
        int u = edge[i].first, v = edge[i].second;
        if (Dist(u, v) >= 3) vis[u] = vis[v] = true;
    }
    Dfs2(X, 0);
    printf("%d\n", ans << 1);
    return 0;
}
/*

*/