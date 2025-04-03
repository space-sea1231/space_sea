#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>

#define fi first
#define se second

#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

const int N = 8e2 + 10, inf = 0x3f3f3f3f;

using ll = long long;

int n, m, k, a[N], f[N][11], dep[N], s[N];
ll dp[N][N];
bool mn[N][N];

vector<int> e[N];

void dfs(int u, int fa)
{
    dep[u] = dep[(f[u][0] = fa)] + 1;
    for (auto v : e[u])
    {
        if (v == fa)
            continue;
        dfs(v, u);
        s[u] += s[v];
    }
}

int LCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 10; i >= 0; i--)
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = 10; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

int lim;

void dfs2(int u, int fa, int top)
{
    mn[u][top] = true;
    for (auto v : e[u])
    {
        if (v == fa || a[v] < a[top] || a[v] - a[top] > lim)
            continue;
        dfs2(v, u, top);
    }
}

void dfs3(int u, int fa)
{
    for (int i = 1; i <= n; i++)
        dp[u][i] = (mn[u][i] ? 0 : inf);
    for (auto v : e[u])
    {
        if (v == fa)
            continue;
        dfs3(v, u);
        ll ans = inf;
        for (int i = 1; i <= n; i++)
            ans = min(ans, dp[v][i]);
        ans += s[v];
        for (int i = 1; i <= n; i++)
            dp[u][i] += min(ans, dp[v][i]);
    }
}

bool check(int x)
{
    lim = x;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            mn[j][i] = false;
        dfs2(i, 0, i);
    }
    dfs3(1, 0);
    ll ans = inf;
    for (int i = 1; i <= n; i++)
        ans = min(ans, dp[1][i]);
    return ans <= k;
}

int main()
{
    fst
            cin >>
        n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
    dfs(1, 0);
    for (int j = 1; j <= 10; j++)
        for (int i = 1; i <= n; i++)
            f[i][j] = f[f[i][j - 1]][j - 1];
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, s[u]++, s[v]++, s[LCA(u, v)] -= 2;
    dfs(1, 0);
    int l = 0, r = 1e9, res = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
            r = (res = mid) - 1;
        else
            l = mid + 1;
    }
    cout << res;
    return 0;
}
