#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, m, s;
int cnt, len, sum, ans;
int head[N], nxt[N << 1], to[N << 1], val[N << 1];
int dep[N], dis[N], father[N];
bool vis[N];
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Dfs(int u, int fa) {
    father[u] = fa;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) continue;
        dep[v] = dep[u] + w;
        Dfs(v, u);
        if (dep[s] < dep[v]) s = v;
    }
}
void Dfs1(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + w;
        Dfs1(v, u);
        sum = max(sum, dis[v]);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
    }
    Dfs(1, 0);
    dep[s] = 0;
    Dfs(s, 0);
    len = dep[s];
    for (int i = s; i; i = father[i]) vis[i] = 1;
    for (int u = s; u; u = father[u]) {
        sum = 0;
        Dfs1(u, 0);
        if (dep[u] > (len >> 1)) ans = max(ans, (len << 1) - dep[u] + sum);
        else ans = max(ans, len + dep[u] + sum);
    }
    printf("%lld\n", ans);

    return 0;
}