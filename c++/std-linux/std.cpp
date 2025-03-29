#include <bits/stdc++.h>
using namespace std;
const int N = 8e3 + 10;
int n, m, k;
int cnt;
int a[N];
int head[N], to[N << 1], nxt[N << 1];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
struct Least_Common_Ancestors {
    static const int K = 33;
    int dep[N], dp[N][K], sum[N];
    void Dfs(int u, int fa) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa) continue;
            dep[v] = dep[u] + 1;
            dp[v][0] = u;
            for (int j = 1; j < K; j++) {
                dp[v][j] = dp[dp[v][j - 1]][j - 1];
            }
            Dfs(v, u);
        }
    }
    int Lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = K - 1; i >= 0; i--) {
            if (dep[dp[x][i]] >= dep[y]) {
                x = dp[x][i];
            }
        }
        if (x == y) return x;
        for (int i = K - 1; i >= 0; i--) {
            if (dp[x][i] != dp[y][i]) {
                x = dp[x][i], y = dp[y][i];
            }
        }
        return dp[x][0];
    }
    void Update(int u, int fa) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa)
                continue;
            Update(v, u);
            sum[u] += sum[v];
        }
    }
    Least_Common_Ancestors() {
        dep[0] = -1;
    }
} Tree;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        Tree.sum[x] ++;
        Tree.sum[y] ++;
        Tree.sum[Tree.Lca(x, y)] -= 2;
    }
    Tree.Update(1, 0);
    
    return 0;
}