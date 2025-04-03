#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int K = 33;
int n, m;
int ans, cnt;
int head[N], to[N << 1], nxt[N << 1], val[N << 1];
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
struct Least_Common_Ancestors {
    int num;
    int dep[N], dis[N], dfn[N], dp[N][K];
    void Dfs(int u, int fa) {
        dfn[u] = ++num;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i], w = val[i];
            if (v == fa) continue;
            dep[v] = dep[u] + 1;
            dis[v] = dis[u] + w;
            dp[v][0] = u;
            for (int j = 1; j < K; j++) {
                dp[v][j] = dp[dp[v][j - 1]][j - 1];
            }
            Dfs(v, u);
        }
    }
    int Lca(int x, int y) {
        if (dep[x] < dep[y]) {
            swap(x, y);
        }
        int srcx = x, srcy = y;
        for (int i = K - 1; i >= 0; i--) {
            if (dep[dp[x][i]] >= dep[y]) {
                x = dp[x][i];
            }
        }
        if (x == y) return dis[srcx] - dis[srcy];
        for (int i = K - 1; i >= 0; i--) {
            if (dp[x][i] != dp[y][i]) {
                x = dp[x][i], y = dp[y][i];
            }
        }
        return dis[srcx] + dis[srcy] - (dis[dp[x][0]] << 1);
    }
    Least_Common_Ancestors() {
        dep[0] = -1;
    }
} Tree;
struct Cmp {
    bool operator()(int a, int b) {
        return Tree.dfn[a] < Tree.dfn[b];
    }
};
set <int, Cmp> s;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
    }
    Tree.Dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        if (s.empty() || s.find(x) == s.end()) {
            auto now = s.insert(x).first;
            auto pre = prev(now), nxt = next(now);
            if (now == s.begin()) pre = prev(s.end());
            if (now == prev(s.end())) nxt = s.begin();
            ans -= Tree.Lca(*pre, *nxt);
            ans += Tree.Lca(*pre, x);
            ans += Tree.Lca(x, *nxt);
        } else {
            auto now = s.lower_bound(x);
            auto pre = prev(now), nxt = next(now);
            if (now == s.begin()) pre = prev(s.end());
            if (now == prev(s.end())) nxt = s.begin();
            ans += Tree.Lca(*pre, *nxt);
            ans -= Tree.Lca(*pre, x);
            ans -= Tree.Lca(x, *nxt);
            s.erase(x);
        }
        printf("%lld\n", ans);
    }

    return 0;
}