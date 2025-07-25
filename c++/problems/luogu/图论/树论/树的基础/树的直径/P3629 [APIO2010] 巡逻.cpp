#include <bits/stdc++.h>
using namespace std;
const int N=1e5 + 10;
int n, m, s;
int cnt, len1, len2;
int head[N], nxt[N << 1], to[N << 1], val[N << 1];
int dep[N], dis[N], father[N];
bool vis[N];
void Add(int u, int v) {
    to[++cnt] = v;
    val[cnt] = 1;
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
        if (dep[s] < dep[v]) {
            s = v;
        }
    }
}
void Dp(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) continue;
        if (vis[u] && vis[v]) w = -1;
        Dp(v, u);
        len2 = max(len2, dis[u] + dis[v] + w);
        dis[u] = max(dis[u], dis[v] + w);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Dfs(1, 0);
    dep[s] = 0;
    Dfs(s, 0);
    len1 = dep[s];
    if (m == 1){
        printf("%d\n", ((n - 1) << 1) - len1 + 1);
        return 0;
    }
    for (int i = s; i; i = father[i]) vis[i] = 1;
    Dp(1, 0);
    printf("%d\n", (n << 1) - len1 - len2);

    return 0;
}