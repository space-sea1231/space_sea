#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
int cnt;
int head[N], nxt[N << 1], to[N << 1];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
class Least_common_ancestors{
    static const int K = 33;
    int dep[N], dp[N][K];
    void Dfs(int u, int fa) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa) continue;
            dep[v] = dep[u] + 1;
            dp[v][0] = u;
            for (int i = 1; i < K; i++) {
                dp[u][i] = dp[dp[u][i-1]][i-1];
            }
            Dfs(v, u);
        }
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
    for (int i = 1; i <= m; i++)
    return 0;
}