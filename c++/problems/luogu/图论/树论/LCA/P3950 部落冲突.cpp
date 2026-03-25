#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n, m;
int cnt, num;
int tot[N];
int head[N], to[N << 1], nxt[N << 1];
vector<pair<int, int> > q;
void add(int u, int v) {
    to[++ cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
class Least_Common_Ancestors {
    static const int K = 33;
    public:
        int dep[N], dis[N], dp[N][K];
        void dfs(int u, int fa) {
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa)
                    continue;
                dep[v] = dep[u] + 1;
                dp[v][0] = u;
                for (int j = 1; j < K; j++) {
                    dp[v][j] = dp[dp[v][j - 1]][j - 1];
                }
                dfs(v, u);
            }
        }
        int lca(int x, int y) {
            if (dep[x] < dep[y])
                swap(x, y);
            for (int i = K - 1; i >= 0; i--) {
                if (dep[dp[x][i]] >= dep[y]) {
                    x = dp[x][i];
                }
            }
            if (x == y)
                return x;
            for (int i = K - 1; i >= 0; i--) {
                if (dp[x][i] != dp[y][i]) {
                    x = dp[x][i], y = dp[y][i];
                }
            }
            return dp[x][0];
        }
        void add(int u, int fa, int w) {
            dis[u] += w;
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (v == fa)
                    continue;
                add(v, u, w);
            }
        }
    Least_Common_Ancestors() {
        dep[0] = -1;
    }
} lca;
struct Binary_Indexed_lca {
    int sum[N];
    int lowbit(int x) {
        return x & -x;
    }
    void add(int x ,int y) {
        for (int i = x; i <= n; i += lowbit(i))
            sum[i] += y;
    }
    int query(int x) {
        int ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i))
            ans += sum[i];
        return ans;
    }
} bin;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    bool flag = 1;
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
        if (v != u + 1)
            flag = 0;
    }
    if (flag) {
        for (int i = 1; i <= m; i ++) {
            char opt;
            int x, y;
            cin >> opt;
            if (opt == 'U')
                cin >> x;
            else
                cin >> x >> y;

            if (opt == 'Q') {
                if (x < y)
                    swap(x, y);
                if (bin.query(x) - bin.query(y) == 0) 
                    printf("Yes\n");
                else
                    printf("No\n");
            }
            if (opt == 'C') {
                if (x < y)
                    swap(x, y);
                bin.add(x, 1);
                tot[++ num] = x;
            }
            if (opt == 'U') {
                bin.add(tot[x], -1);
            }
        }
        return 0;
    }
    lca.dfs(1, 0);
    for (int i = 1; i <= m; i ++) {
        char opt;
        cin >> opt;
        if (opt == 'Q') {
            int x, y;
            cin >> x >> y;
            if (lca.dis[x] + lca.dis[y] - (lca.dis[lca.lca(x, y)] << 1) == 0)
                printf("Yes\n");
            else
                printf("No\n");
        }
        if (opt == 'C') {
            int x, y;
            cin >> x >> y;
            if (lca.dep[x] < lca.dep[y])
                swap(x, y);
            lca.add(x, y, 1);
            q.push_back(make_pair(x, y));
        }
        if (opt == 'U') {
            int x;
            cin >> x;
            lca.add(q[x - 1].first, q[x - 1].second, -1);
        }
    }

    return 0;
}