#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int M = 1e2 + 10;
const int N = 21;

int n, m, k, o;
int dis[N], dist[M][M];
ll f[M];
bool vis[N][M], vis1[N];
bool flag[N];
vector<pair<int, int> > e[M];

void Dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(make_pair(0, 1));
    for (int i = 1; i <= m; i++) dis[i] = INF, vis1[i] = false; dis[1] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis1[u]) continue;
        vis1[u] = true;
        for (auto [v, w] : e[u]) {
            if (flag[v]) continue;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(make_pair(dis[v], v));
            }
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> k >> o;
    for (int i = 1; i <= o; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(make_pair(v, w));
        e[v].emplace_back(make_pair(u, w));
    }
    int d;
    cin >> d;
    for (int i = 1; i <= d; i++) {
        int p, a, b;
        cin >> p >> a >> b;
        for (int j = a; j <= b; j++) vis[p][j] = true;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int p = 1; p <= m; p++) flag[p] = false;
            for (int p = 1; p <= m; p++) {
                for (int t = i; t <= j; t++) {
                    flag[p] |= vis[p][t];
                } 
            }
            Dijkstra();
            dist[i][j] = dis[m];
        }
    }
    for (int i = 1; i <= n; i++) {
        f[i] = (ll)i * dist[1][i];
        for (int j = 1; j < i; j++) {
            f[i] = min(f[i], f[j] + (ll)(i - j) * dist[j + 1][i] + k);
        }
    }
    printf("%lld\n", f[n]);
    return 0;
}