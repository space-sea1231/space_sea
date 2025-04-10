#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
const int K = 33;
const int INF = 0x3f3f3f3f;
int n, m;
int cnt = 1, tot;
int maxn, maxx, maxw;
int a[N], b[N], dis1[N];
int head[N], nxt[N << 1], to[N << 1], val[N << 1];
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
int dep[N], dis[N], dp[N][K], sum[N];
void Dfs(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        dis[v] = dis[u] + w;
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
int Dist(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int srcx = x, srcy = y;
    for (int i = K - 1; i >= 0; i --) {
        if (dep[dp[x][i]] >= dep[y]) {
            x = dp[x][i];
        }
    }
    if (x == y) return dis[srcx] - dis[srcy];
    for (int i = K - 1; i >= 0; i --) {
        if (dp[x][i] != dp[y][i]) {
            x = dp[x][i], y = dp[y][i];
        }
    }
    return dis[srcx] + dis[srcy] - (dis[dp[x][0]] << 1);
}
void Update(int u, int edge) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (i == (edge ^ 1)) continue;
        Update(v, i);
        sum[u] += sum[v];
    }
    if (sum[u] == tot) maxn = max(maxn, val[edge]);
}
void Init() {
    tot = 0, maxn = 0;
    memset(sum, 0, sizeof(sum));
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    dep[0] = -1;
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
        maxw = max(maxw, w);
    }
    Dfs(1, 0);
    for (int i = 1; i <= m; i ++) {
        cin >> a[i] >> b[i];
        dis1[i] = Dist(a[i], b[i]);
        maxx = max(maxx, dis1[i]);
    }
    int l = maxx - maxw, r = 3e8, ans = INF;
    while (l <= r) {
        Init();
        int mid = (l + r) >> 1;
        for (int i = 1; i <= m; i ++) {
            if (dis1[i] > mid) {
                sum[a[i]]++;
                sum[b[i]]++;
                sum[Lca(a[i], b[i])] -= 2;
                tot++;
            }
        }
        Update(1, 0);
        if (maxx - maxn <= mid) {
            ans = min(ans, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", ans);
    
    return 0;
}