#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
const int K = 33;
int n, m;
int cnt;
int head[N], to[N << 1], nxt[N << 1];
void Add(int u, int v) {
    to[++ cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
class Least_Common_Ancestors {
    public:
        int dep[N], dp[N][K], sum[N];
        void Dfs(int u, int fa) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa) continue;
                dep[v] = dep[u] + 1;
                dp[v][0] = u;
                for (int j = 1; j < K; j ++) {
                    dp[v][j] = dp[dp[v][j - 1]][j - 1];
                }
                Dfs(v, u);
                sum[u] += sum[v] + 1;
            }
        }
        int Lca(int x, int y) {
            if (dep[x] < dep[y]) {
                swap(x, y);
            }
            for (int i = K - 1; i >= 0; i --) {
                if (dep[dp[x][i]] >= dep[y]) {
                    x = dp[x][i];
                }
            }
            if (x == y) return x;
            for (int i = K - 1; i >= 0; i --) {
                if (dp[x][i] != dp[y][i]) {
                    x = dp[x][i], y = dp[y][i];
                }
            }
            return dp[x][0];
        }
        void Query(int x, int y, int z) {
            int ans;
            int a = Lca(x, y);
            int b = Lca(x, z);
            int c = Lca(y, z);
            if (a == b) ans = c;
            if (a == c) ans = b;
            if (b == c) ans = a;
            printf("%d %d\n", ans, dep[x] + dep[y] + dep[z] - dep[a] - dep[b] - dep[c]);
        }
    Least_Common_Ancestors() {
        dep[0] = -1;
    }
}Tree;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Tree.Dfs(1, 0);
    for (int i = 1; i <= m; i ++) {
        int x, y, z;
        cin >> x >> y >> z;
        Tree.Query(x, y, z);
    }
    return 0;
}