#include <bits/stdc++.h>
using namespace std;
const int N=6e5 + 10;
int n, m;
int cnt=1, tot, num, ans;
int head[N], nxt[N << 1], to[N << 1];
int dfn[N], low[N], vis[N], dp[N];
bool bridge[N << 1];
void Add(int u, int v){
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Tarjan(int u, int fa){
    dfn[u] = low[u] = ++num;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]){
                bridge[i] = bridge[i ^ 1] = 1;
            }
        }
        if (v == fa){
            continue;
        }
        low[u] = min(low[u], dfn[v]);
    }
}
void dfs(int u) {
    vis[u] = tot;
    for (int i = head[u]; i; i = nxt[i]){
        int v = to[i];
        if (vis[v] || bridge[i]){
            continue;
        }
        dfs(v);
    }
}
void Dp(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        Dp(v, u);
        ans = max(ans, dp[u] + dp[v] + 1);
        dp[u] = max(dp[u], dp[v] + 1);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i]) continue;
        Tarjan(i, 0);
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        tot++;
        dfs(i);
    }
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (vis[u] !=  vis[v]) {
                Add(vis[u] + n, vis[v] + n);
            }
        }
    }
    Dp(vis[1] + n, 0);
    printf("%d\n", ans);

    return 0;
}