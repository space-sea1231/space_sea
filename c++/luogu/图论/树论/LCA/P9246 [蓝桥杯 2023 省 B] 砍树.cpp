#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
int cnt = 1, ans;
int head[N], nxt[N << 1], to[N << 1];
int sum[N];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
class Least_common_ancestors{
    public:
        static const int K = 33;
        int dep[N], dp[N][K];
        void Dfs(int u, int fa) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa) continue;
                dep[v] = dep[u] + 1;
                dp[v][0] = u;
                for (int i = 1; i < K; i++) {
                    dp[v][i] = dp[dp[v][i-1]][i-1];
                }
                Dfs(v, u);
            }
        }
        int Lca(int x, int y) {
            if (dep[x] < dep[y]) swap(x, y);
            for (int i = K - 1; i >= 0; i--) {
                if (dep[dp[x][i]] <= dep[y]) {
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
        void Total(int u, int edge) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (i == (edge ^ 1)) continue;
                Total(v, i);
                sum[u] += sum[v];
            }
            if (sum[u] == m) ans = max(ans, edge);
        }
    Least_common_ancestors() {
        dep[0] = -1;
    }
} Tree;
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Tree.Dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        sum[x]++, sum[y]++;
        sum[Tree.Lca(x, y)] -= 2;
    }
    Tree.Total(1, 0);
    if (ans) printf("%d\n", ans/2);
    else printf("-1\n");

    return 0;
}