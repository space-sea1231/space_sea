#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n, m;
int cnt = 1, ans, maxn;
int sum[N];
int head[N], to[N << 1], nxt[N << 1], val[N << 1];
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
class Least_Common_Ancestors {
    static const int K = 33;
    public:
        int dep[N], dp[N][K];
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
        void Update(int u, int edge) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                // printf("Debug2: %d %d %d\n", u, v, i);
                if (i == (edge ^ 1)) continue;
                Update(v, i);
                sum[u] += sum[v];
            }
            ans += sum[u] * val[edge];
            // printf("Debug1: %d %d\n", u, sum[u]);
            maxn = max(maxn, sum[u] * val[edge]);
        }
    Least_Common_Ancestors() {
        dep[0] = -1;
    }
} Tree;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
    }
    Tree.Dfs(1, 0);
    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        // printf("Debug4: %d %d %d\n", x, y, Tree.Lca(x, y));
        sum[x]++, sum[y]++, sum[Tree.Lca(x, y)] -= 2;
    }
    // for (int i = 1; i <= n; i ++) {
    //     printf("Debug3: %d %d\n", i, sum[i]);
    // }
    Tree.Update(1, 0);
    printf("%d\n", ans - maxn);

    return 0;
}