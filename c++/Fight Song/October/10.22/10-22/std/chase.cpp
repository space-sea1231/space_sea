#include <bits/stdc++.h>
#define pii pair<int, int>
#define st first
#define nd second
using namespace std;
const int N = 2e5 + 7, logN = 23;
int n, x, y, ans, fa[N][logN], depa[N], depb[N], o[N];
vector<int> dra[N], drb[N];
pii d[N];
void dfsb(int u, int Fa) {
    fa[u][0] = Fa, depb[u] = depb[Fa] + 1;
    for (int v : drb[u]) {
        if (v == Fa)
            continue;
        dfsb(v, u);
    }
}
int dis(int x, int y) {
    int ans = 0;
    if (depb[x] < depb[y])
        swap(x, y);
    for (int i = logN - 1; i >= 0; i --)
        if (depb[fa[x][i]] >= depb[y])
            x = fa[x][i], ans += (1 << i);
    if (x == y)
        return ans;
    for (int i = logN - 1; i >= 0; i --)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i], ans += (1 << i + 1);
    return ans + 2;
}
void solve() {
    for (int i = 1; i < logN; i ++)
        for (int j = 1; j <= n; j ++)
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
    for (int i = 1; i < n; i ++) {
        // cout << d[i].st << ' ' << d[i].nd << ' ' << dis(d[i].st,     d[i].nd) << '\n';
        if (dis(d[i].st, d[i].nd) >= 3)
            o[d[i].st] = o[d[i].nd] = 1;
    }
    // for (int i = 1; i <= n; i ++)
    //     cout << depb[i] << ' ';
}
void dfs(int u, int fa) {
    depa[u] = depa[fa] + 1;
    if (depa[u] >= depb[u])
        return;
    if (o[u]) {cout << "forever"; exit(0);}
    ans = max(ans, depb[u]);
    for (int v : dra[u]) {
        if (v == fa)
            continue;
        dfs(v, u);
    }
}
int main() {
     freopen("chase.in", "r", stdin);
     freopen("chase.out", "w", stdout);
    cin >> n >> x >> y;
    if (x == y) {cout << 0; exit(0);}
    depa[0] = depb[0] = -1;
    for (int i = 1, u, v; i < n; i ++) {
        cin >> u >> v, d[i] = {u, v};
        dra[u].push_back(v);
        dra[v].push_back(u);
    }
    for (int i = 1, u, v; i < n; i ++) {
        cin >> u >> v;
        drb[u].push_back(v);
        drb[v].push_back(u);
    }
    dfsb(y, 0);
    solve();
    dfs(x, 0);
    cout << ans * 2;
    return 0;
}
