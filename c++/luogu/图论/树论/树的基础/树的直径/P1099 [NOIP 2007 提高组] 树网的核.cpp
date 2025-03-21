#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10;
const int INF = 1e15;
int n, m, s;
int cnt, num, ans=INF;
int head[N], nxt[N << 1], to[N << 1], val[N << 1];
int dis[N], father[N], sit[N], sat[N], sats[N];
bool vis[N];
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Dfs(int u, int fa) {
    father[u]=fa;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa || vis[v]) {
            continue;
        }
        dis[v] = dis[u] + w;
        if (dis[s] < dis[v]) {
            s = v;
        }
        Dfs(v, u);
    }
}
void Bfs() {
    for (int i = s; i; i = father[i]) {
        sit[++num] = i;
        sat[num] = dis[i];
    }
    reverse(sit + 1, sit + num + 1);
    reverse(sat + 1, sat + num + 1);
    for (int i = 1; i <= num; i++) {
        sats[i] = sat[num] - sat[i];
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
    }
    Dfs(1, 0);
    dis[s] = 0;
    Dfs(s, 0);
    Bfs();
    for (int i = 1; i <= num; i++) {
        vis[sit[i]] = 1;
    }
    int maxn=0;
    for (int i = 1; i <= num; i++) {
        dis[sit[i]] = 0, s = 0;
        Dfs(sit[i], 0);
        maxn = max(maxn, dis[s]);
    }
    int l = 1, r = 1;
    while (l <= num) {
        while (r <= num && sat[r + 1] - sat[l] <= m) {
            r++;
        }
        ans = min(ans, max(maxn, max(sat[l], sats[r])));
        l++;
    }
    printf("%lld\n", ans);

    return 0;
}