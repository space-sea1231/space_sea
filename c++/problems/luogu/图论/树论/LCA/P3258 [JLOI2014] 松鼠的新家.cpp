#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n;
int cnt;
int a[N], sum[N];
int head[N], nxt[N << 1], to[N << 1];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
class Least_Common_Ancestors {
    static const int K = 33;
    public:
        int dep[N], dp[N][K], father[N];
        void Dfs(int u, int fa) {
            father[u] = fa;
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa) continue;
                dep[v] = dep[u] + 1;
                dp[v][0] = u;
                for (int i = 1; i < K; i ++) {
                    dp[v][i] = dp[dp[v][i - 1]][i - 1];
                }
                Dfs(v, u);
            }
        }
        int Lca(int x, int y) {
            if (dep[x] < dep[y]) swap(x, y);
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
        void Update(int u, int fa) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa) continue;
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
    cin.tie();
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Tree.Dfs(1, 0);
    for (int i = 1; i < n; i ++) {
        int x = a[i], y = a[i + 1];
        int lca = Tree.Lca(x, y), fa = Tree.father[lca];
        sum[x]++, sum[y]++, sum[lca]--, sum[fa]--;
    }
    Tree.Update(1, 0);
    sum[a[1]]++;
    for (int i = 1; i <= n; i ++) {
        printf("%d\n", sum[i]-1);
    }

    return 0;
}