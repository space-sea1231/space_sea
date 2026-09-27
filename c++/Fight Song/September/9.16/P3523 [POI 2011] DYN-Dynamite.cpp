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
int mid, cnt;
int f[N], g[N];
/*
f[i]:the farest bomb to node i(max)
g[i]:the nearest spark to node i(min)
*/
bool a[N];
vector<int> e[N];

void Dfs(int u, int fa) {
    if (a[u]) f[u] = 0;
    for (int v:e[u]) {
        if (v == fa) continue;
        Dfs(v, u);
        // if (u == 5 && v == 6) printf("Debug:%d %d\n", v, f[v] + 1); 
        f[u] = max(f[u], f[v] + 1);
        g[u] = min(g[u], g[v] + 1);
    }
    // printf("f[%d]=%d g[%d]=%d\n", u, f[u], u, g[u]);
    if (f[u] + g[u] <= mid) f[u] = -INF;
    if (f[u] >= mid) {
        // cerr<<u << " ";
        g[u] = 0;
        f[u] = -INF;
        cnt++;
    }
}
bool Check() {
    cnt = 0;
    for (int i = 1; i <= n; i++) f[i] = -INF, g[i] = INF;
    Dfs(1, 0);
    if (f[1] >= 0) cnt++;
    // cerr<<endl << cnt;
    if (cnt <= m) return true;
    else return false;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    int l = 0, r = n;
    while (l < r) {
        mid = l + r >> 1;
        if (Check()) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", r);
    return 0;
}
/*
Tread 踏着
*/