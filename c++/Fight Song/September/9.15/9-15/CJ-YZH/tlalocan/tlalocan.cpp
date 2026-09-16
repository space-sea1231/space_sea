#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <map>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 10;
const int M = 100;
const int Mod = 998244353;

int n, m;
int a[M], b[M];

namespace Pts1 {
    // bool vis[N];
    int x[N];
    int ans = 0;
    map<ll, bool> s;
    void Check() {
        ll sum = 0;
        for (int i = 1; i <= m; i++) {
            if (x[a[i]] > x[b[i]]) sum = sum * 10 + 1;
            if (x[a[i]] == x[b[i]]) sum = sum * 10 + 2;
            if (x[a[i]] < x[b[i]]) sum = sum * 10 + 3;
        }
        if (s.find(sum) == s.end()) {
            s[sum] = true;
            ans++;
            if (ans == Mod) ans = 0;
        }
        // for (int i = 1; i <= n; i++) printf("%d ", x[i]);
        // printf("\n");
    }
    void Dfs(int dep) {
        if (dep == n + 1) {
            Check();
            return;
        }
        for (int i = 1; i <= n; i++) {
            // if (!vis[i]) {
                x[dep] = i;
                // vis[i] = true;
                Dfs(dep + 1);
                // vis[i] = false;
            // }
        }
    }
}
signed main() {
    freopen("tlalocan.in", "r", stdin);
    freopen("tlalocan.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
    if (n <= 6) {
        using namespace Pts1;
        Dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}