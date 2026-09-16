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
const int N = 5e5 + 10;

int n;
int a[N];
int f[N], g[N];
vector<int> e[N];

void Dfs(int u, int fa) {
    vector<int> sec;
    f[u] = a[u];
    for (int v:e[u]) {
        if (v == fa) continue;
        Dfs(v, u);
        sec.emplace_back(v);
    }
    sort(sec.begin(), sec.end(), [&](int a, int b) {
        return f[a] - g[a] > f[b] - g[b];
    });
    for (int cur:sec) {
        f[u] = max(f[u], g[u] + 1 + f[cur]);
        g[u] += g[cur] + 2;
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    Dfs(1, 0);
    // for (int i = 1; i <= n; i++) printf("f[%d]=%d\n", i, f[i]);
    printf("%d\n", max(f[1], g[1] + a[1]));
    return 0;
}
/*
1.when it enter on of the son tree, it can leave until it passage all of the computer.
Sequence 顺序
*/