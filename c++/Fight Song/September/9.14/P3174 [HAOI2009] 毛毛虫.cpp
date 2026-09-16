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
const int N = 3e5 + 10;

int n, m;
// int f[N][2];
int f[N][2];
vector<int> e[N];

void Dfs(int u, int fa) {
    // f[u][0] = f[u][1] = 1;
    int max1 = 0, max2 = 0;
    for (int v:e[u]) {
        if (v == fa) continue;
        Dfs(v, u);
        f[u][0]++;
        if (max1 < f[v][0]) max2 = max1, max1 = f[v][0];
        else if (max2 < f[v][0]) max2 = f[v][0];
    }
    f[u][0] += max1; f[u][1] = max2;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    Dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[i][0] + f[i][1] + 1 + (i != 1));
    printf("%d\n", ans);
    return 0;
}