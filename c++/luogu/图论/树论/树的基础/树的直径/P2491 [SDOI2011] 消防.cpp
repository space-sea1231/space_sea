#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10;
const int INF = 1e15;
int n, m, s, t, tot, top;
int cnt, num, ans=INF;
int head[N], nxt[N << 1], to[N << 1], val[N << 1];
int dis[N], dis1[N], pre[N], prv[N], sum[N], que[N];
queue<pair<int, int> > q;
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Dfs(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) {
            continue;
        }
        dis[v] = dis[u] + w;
        pre[v] = u, prv[v] = w;
        if (dis[s] < dis[v]) {
            s = v;
        }
        Dfs(v, u);
    }
}
void Bfs() {
    memset(dis, 0x3f, sizeof(dis));
    t=s;
    while (pre[s]) {
        q.push(make_pair(s, s));
        dis[s] = 0;
        sum[pre[s]] = sum[s] + prv[s];
        s = pre[s];
    }
    while (!q.empty()) {
        int root = q.front().first, u = q.front().second;
        q.pop();
        for (int i = head[u]; i; i=nxt[i]) {
            int v = to[i], w = val[i];
            if (dis[v] >= INF) {
                dis[v] = dis[u] + w;
                dis1[root] = max(dis1[root], dis[v]);
                q.push(make_pair(root, v));
            }
        }
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
    dis[s] = 0, pre[s] = 0;
    Dfs(s, 0);
    Bfs();
    for (int l = t, r = t; l && r != s; l = pre[l]) {
        int last=r;
        tot++;
        while (sum[r] - sum[l] <= m && r) {
            last = r, r = pre[r];
            if (r && sum[r] - sum[l] <= m) {
                while (dis1[r] >= que[top] && top >= tot) {
                    top--;
                }
                que[++top]=dis1[r];
            }
        }
        if (r == 0 || sum[r] - sum[l] > m) {
            r = last;
        }
        int tmp = max(sum[l], max(sum[s] - sum[r], que[tot]));
        ans = min(ans, tmp);
    }
    printf("%lld\n", ans);

    return 0;
}