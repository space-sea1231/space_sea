#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int M = 30;
int n, m;
int cnt;
int head[N], nxt[N << 1], to[N << 1];
int dep[N], sit[N][M], sat[N][M], ru[N];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    ru[u]++;
}
class Least_Common_Ancestors {
    public:
        void Dfs(int u, int fa) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa) continue;
                dep[v] = dep[u] + 1;
                sit[v][0] = u;
                sat[v][0] = ru[v];
                for (int i = 1; i < M; i++) {
                    sit[v][i] = sit[sit[v][i - 1]][i - 1];
                    sat[v][i] = sat[v][i - 1] + sat[sit[v][i - 1]][i - 1];
                }
                Dfs(v, u);
            }
        }
        int Lca(int x, int y) {
            if (x == y) return ru[x];
            if (dep[x] < dep[y]) {
                swap(x, y);
            }
            int sum = 0;
            for (int i = M - 1; i >= 0; i--) {
                if (dep[sit[x][i]] >= dep[y]) {
                    sum += sat[x][i];
                    x = sit[x][i];
                }
            }
            if (x == y) return sum + ru[x];
            for (int i = M - 1; i >= 0; i--) {
                if (sit[x][i] != sit[y][i]) {
                    sum += sat[x][i] + sat[y][i];
                    x = sit[x][i], y = sit[y][i];
                }
            }
            return sum + sat[x][0] + sat[y][0] + sat[sit[x][0]][0];
        }
    Least_Common_Ancestors() {
        dep[0] = -1;
    }
} Tree;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    sat[1][0] = ru[1];
    Tree.Dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        printf("%lld\n", Tree.Lca(x, y));
    }

    return 0;
}