#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 1e5 + 10;
const int K = 5e5 + 10;

int n, m, s;
int cnt;
ll seg[N * 10], dis[N * 10];
ll head[N * 40], to[N * 40], nxt[N * 40], cost[N * 40];
bool vis[N * 10];

void Add(int u, int v, int w) {
    to[++cnt] = v;
    cost[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

namespace SegmentTree {
    void Build(int p, int l, int r) {
        if (l == r) {
            seg[l] = p;
            return ;
        }
        Add(p << 1, p, 0);
        Add(p << 1 | 1, p, 0);
        Add(p + K, (p << 1) + K, 0);
        Add(p + K, (p << 1 | 1) + K, 0);

        int mid = l + r >> 1;
        Build(p << 1, l, mid);
        Build(p << 1 | 1, mid + 1, r);
    }
    void Update1(int p, int l, int r, int L, int R, int u, int w) {
        if (L <= l && r <= R) {
            Add(seg[u], p + K, w);
            return ;
        }
        int mid = l + r >> 1;
        if (L <= mid) Update1(p << 1, l, mid, L, R, u, w);
        if (mid < R) Update1(p << 1 | 1, mid + 1, r, L, R, u, w);
    }
    void Update2(int p, int l, int r, int L, int R, int u, int w) {
        if (L <= l && r <= R) {
            Add(p, seg[u] + K, w);
            return ;
        }
        int mid = l + r >> 1;
        if (L <= mid) Update2(p << 1, l, mid, L, R, u, w);
        if (mid < R) Update2(p << 1 | 1, mid + 1, r, L, R, u, w);
    }
} using namespace SegmentTree;

void Dijkstra() {
    for (int i = 1; i < N * 10; i++) dis[i] = INF;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q; 
    q.push(make_pair(0, seg[s]));
    dis[seg[s]] = 0;
    while (!q.empty()) {
        pair<int, int> cur = q.top(); q.pop();
        int u = cur.second;
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i], w = cost[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(make_pair(dis[v], v));
            }
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> s; Build(1, 1, n);
    for (int i = 1; i <= n; i++) Add(seg[i], seg[i] + K, 0), Add(seg[i] + K, seg[i], 0);
    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int u, v, w;
            cin >> u >> v >> w;
            Add(seg[u], seg[v] + K, w);
        }
        if (opt == 2) {
            int u, l, r, w;
            cin >> u >> l >> r >> w;
            Update1(1, 1, n, l, r, u, w);
        }
        if (opt == 3) {
            int u, l, r, w;
            cin >> u >> l >> r >> w;
            Update2(1, 1, n, l, r, u, w);
        }
    }
    Dijkstra();
    for (int i = 1; i <= n; i++) printf("%lld ", dis[seg[i] + K] == INF ? -1 : dis[seg[i] + K]);
    return 0;
}