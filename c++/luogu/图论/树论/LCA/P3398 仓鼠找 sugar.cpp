#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int M = 30;
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
        int dep[N], dp[N][M];
        void Dfs(int u, int fa) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa) continue;
                dep[v] = dep[u] + 1;
                dp[v][0] = u;
                for (int j = 1; j < M; j ++) {
                    dp[v][j] = dp[dp[v][j - 1]][j - 1];
                }
                Dfs(v, u);
            }
        }
        int Lca(int x, int y) {
            if (dep[x] < dep[y]) {
                swap(x, y);
            }
            for (int i = M - 1; i >= 0; i --) {
                if (dep[dp[x][i]] >= dep[y]) {
                    x = dp[x][i];
                }
            }
            if (x == y) return x;
            for (int i = M - 1; i >= 0; i --) {
                if (dp[x][i] != dp[y][i]) {
                    x = dp[x][i], y = dp[y][i];
                }
            }
            return dp[x][0];
        }
        char Check(int a, int b, int c, int d) {
            int x = Lca(a, b);
            int y = Lca(c, d);
            if (dep[x] >= dep[y] && (Lca(x, c) == x || Lca(x, d) == x)) return 'Y';
            if (dep[y] >= dep[x] && (Lca(y, a) == y || Lca(y, b) == y)) return 'Y';
            return 'N';
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
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        printf("%c\n", Tree.Check(a, b, c, d));
    }
    return 0;
}