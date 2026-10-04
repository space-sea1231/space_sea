#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <deque>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = 1e9 + 1;
const int N = 5e5 + 10;
const int K = 2e6 + 10;

int n, m, s;
int cnt;
int seg[N * 10], dis[N * 10];
int head[N * 20], to[N * 20], nxt[N * 20], cost[N * 20];
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
    void Update1(int p, int l, int r, int L, int R, int u) {
        if (L <= l && r <= R) {
            Add(p, u, 1);
            return ;
        }
        int mid = l + r >> 1;
        if (L <= mid) Update1(p << 1, l, mid, L, R, u);
        if (mid < R) Update1(p << 1 | 1, mid + 1, r, L, R, u);
    }
    void Update2(int p, int l, int r, int L, int R, int u) {
        if (L <= l && r <= R) {
            Add(u, p + K, 0);
            return ;
        }
        int mid = l + r >> 1;
        if (L <= mid) Update2(p << 1, l, mid, L, R, u);
        if (mid < R) Update2(p << 1 | 1, mid + 1, r, L, R, u);
    }
} using namespace SegmentTree;

void Bfs() {
    for (int i = 1; i < N * 10; i++) dis[i] = INF;
    deque<int> q;
    q.push_front(seg[s]);
    dis[seg[s]] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i], w = cost[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (w == 0) q.push_front(v);
                else q.push_back(v);
            }
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> s; Build(1, 1, n);
    for (int i = 1; i <= n; i++) Add(seg[i], seg[i] + K, 0), Add(seg[i] + K, seg[i], 0);
    for (int i = 1; i <= m; i++) {
        int sl, sr, fl, fr; 
        cin >> sl >> sr >> fl >> fr;
        Update1(1, 1, n, sl, sr, (K << 1) + i);
        Update2(1, 1, n, fl, fr, (K << 1) + i);
        Update1(1, 1, n, fl, fr, (K << 1) + i + m);
        Update2(1, 1, n, sl, sr, (K << 1) + i + m);
    }
    Bfs();
    for (int i = 1; i <= n; i++) printf("%d\n", dis[seg[i] + K] == INF ? -1 : dis[seg[i] + K]);
    return 0;
}