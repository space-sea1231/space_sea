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
const int N = 1e3 + 10;

int n, k, Q;
int a[N];
int dis[N];
bool vis[N];
vector<pair<int, int> > e[N];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;

int Search(int x, int y) {
    q.push(make_pair(0, x));
    for (int i = 1; i <= n; i++) dis[i] = INF, vis[i] = false; dis[x] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [v, w]: e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(make_pair(dis[v], v));
            }
        }
    }
    return dis[y];
}
signed main() {
    freopen("railway.in", "r", stdin);
    freopen("railway.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k >> Q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int cnt = 0;
            for (int k = i + 1; k <= j; k++) {
                cnt += (a[k] >= a[j] || a[k] >= a[i]);
            }
            e[i].emplace_back(make_pair(j, cnt));
        }
        for (int j = i - 1; j; j--) {
            int cnt = 0;
            for (int k = i - 1; k >= j; k--) {
                cnt += (a[k] >= a[j] || a[k] >= a[i]);
            }
            e[i].emplace_back(make_pair(j, cnt));
        }
    }
    for (int i = 1; i <= Q; i++) {
        int x, y;
        cin >> x >> y;
        // printf("%d %d\n", x, y);
        printf("%d\n", Search(x, y));
    }
    // for (int i = 1; i <= n; i++) printf("dis[%d]=%d\n", i, dis[i]);
    return 0;
}