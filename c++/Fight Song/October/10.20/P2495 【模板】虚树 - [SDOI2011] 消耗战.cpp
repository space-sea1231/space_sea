#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2.5e5 + 10;
const int K = 20;

int n, m;
int num;
int dep[N], dfn[N];
int f[N][K], g[N][K];
ll dp[N];
vector<pair<int, int> > e[N];

int cnt;
int head[N], to[N << 1], val[N << 1], nxt[N << 1];

void Dfs(int u, int fa) {
    dfn[u] = ++num;
    dep[u] = dep[fa] + 1;
    for (auto [v, w] : e[u]) {
        if (v == fa) continue;
        f[v][0] = u; g[v][0] = w; 
        for (int i = 1; i < K; i++) {
            f[v][i] = f[f[v][i - 1]][i - 1];
            g[v][i] = min(g[v][i - 1], g[f[v][i - 1]][i - 1]);
        }
        Dfs(v, u);
    }
}
int Lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; ~i; i--) {
        if (dep[f[x][i]] >= dep[y]) {
            x = f[x][i];
        }
    }
    if (x == y) return x;
    for (int i = K - 1; ~i; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}
int Dist(int u, int fa) {
    int minn = INF;
    for (int i = K - 1; ~i; i--) {
        if (dep[f[u][i]] >= dep[fa]) {
            // printf("Dist:%d->%d g[%d][%d]=%d\n", u, f[u][i], u, i, g[u][i]);
            minn = min(minn, g[u][i]);
            u = f[u][i];
        }
    }
    return minn;
}
bool Cmp(int a, int b) { return dfn[a] < dfn[b]; }
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int k;
int top;
int h[N], vis[N];
int stk[N << 1];

void Build() {
    top = cnt = 0; stk[++top] = 1;
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> h[i];
        vis[h[i]] = m;
    }
    sort(h + 1, h + k + 1, Cmp);
    
    for (int i = 1; i < k; i++) {
        stk[++top] = h[i];
        stk[++top] = Lca(h[i], h[i + 1]);
    } stk[++top] = h[k];
    sort(stk + 1, stk + top + 1, Cmp);
    top = unique(stk + 1, stk + top + 1) - stk - 1;
    
    for (int i = 1; i < top; i++) {
        // cerr<<stk[i] << " " << stk[i + 1] << "\n";
        int lca = Lca(stk[i], stk[i + 1]);
        head[stk[i]] = head[stk[i + 1]] = 0;
        dp[stk[i]] = dp[stk[i + 1]] = 0;
        Add(lca, stk[i + 1], Dist(stk[i + 1], lca));
        // printf("%d->%d\n", lca, stk[i + 1]);
        // printf("Dist(%d,%d)=%d\n", stk[i + 1], lca, Dist(stk[i + 1], lca));
    }
    // printf("\n");
}
void Dfs1(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) continue;
        // printf("%d->%d %d\n", u, v, w);
        Dfs1(v, u);
        if (vis[v] == m) dp[u] += w;
        else dp[u] += min(dp[v], (ll)w);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(make_pair(v, w));
        e[v].emplace_back(make_pair(u, w));
    }
    Dfs(1, 0);
    cin >> m;
    while (m--) {
        Build();
        // cerr<<stk[1] << "\n";
        Dfs1(1, 0); //printf("\n");
        printf("%lld\n", dp[1]);
 
    }
    return 0;
}