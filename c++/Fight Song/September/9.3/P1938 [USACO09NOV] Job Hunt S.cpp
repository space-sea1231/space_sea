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
const int N = 3e2 + 10;

int n, m1, k, m2, s;
int ans;
int dis[N];
bool vis[N][N];
vector<pair<int, int> > e[N];

void Dfs(int u, int dist) {
    if (dis[u] >= dist) return;
    if (dis[u] && dis[u] < dist) {
        printf("-1\n");
        exit(0);
    }
    dis[u] = dist;
    for (auto [v, w]:e[u]) Dfs(v, dist + w);
    dis[u] = 0;
    ans = max(ans, dist);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> k >> m1 >> n >> m2 >> s;
    for (int i = 1; i <= m1; i++) {
        int u, v;
        cin >> u >> v;
        // if (vis[u][v]) continue;
        vis[u][v] = true;
        // cerr<<u<<" "<<v<<endl;
        e[u].emplace_back(make_pair(v, k));
    }
    for (int i = 1; i <= m2; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(make_pair(v, k - w));
    }
    Dfs(s, k);
    printf("%d\n", ans);
    return 0;
}