#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m, s;
int cnt, tot, ans = INF;
int head[N], nxt[N << 1], from[N << 1], to[N << 1];
bool vis[N];
void Add(int u, int v) {
    from[++cnt] = u;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Dfs(int u, int dep, int fa) {
    tot++;
    if (!dep) return;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        Dfs(v, dep-1, u);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    if (m&1) {
        for (int i = 1; i <= (n << 1); i += 2) {
            int u = from[i], v = to[i];
            tot = 0;
            Dfs(u, m >> 1, v);
            Dfs(v, m >> 1, u);
            ans = min(ans, n - tot);
        }
    } else {
        for (int i = 1; i <= n; i++) {
            tot = 0;
            Dfs(i, m >> 1, 0);
            ans = min(ans, n - tot);
        }
    }
    printf("%d\n", ans);

    return 0;
}