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
const int N = 1e6 + 10;
const int Mod = 998244353;

int C, T;
int n, m;

namespace Pts1 {
    int ans;
    int a[20];
    bool vis[20][20];
    void Check() {
        for (int i = 1; i <= n; i++) {
            bool flag = true;
            for (int j = 1; j <= n; j++) {
                if (vis[i][j]) {
                    if (a[i] > a[j]) flag = false;
                    if (abs(a[i] - a[j]) != 1) return ;
                }
            }
            if (flag && a[i]) return ;
        }
        for (int i = 1; i <= n; i++) printf("%d ", a[i]); printf("\n");
        ans++;
    }
    void Dfs(int dep) {
        if (dep == n + 1) {
            Check();
            return ;
        }
        for (int i = 0; i < n; i++) {
            a[dep] = i;
            Dfs(dep + 1);
        }
    }
} 
namespace Pts2 {
    int Pow(int a, int b) {
        if (b < 0) return 0;
        int sum = 1;
        while (b) {
            if (b & 1) sum = (ll)sum * a % Mod;
            a = (ll)a * a % Mod;
            b >>= 1;
        }
        return sum;
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> C >> T;
    if (C == 1) {
        using namespace Pts1;
        while (T--) {
            cin >> n >> m;
            ans = 0;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    vis[i][j] = false;
                }
            }
            for (int i = 1; i <= m; i++) {
                int u, v;
                cin >> u >> v;
                vis[u][v] = vis[v][u] = true;
            }
            Dfs(1);
            printf("%d\n", ans);
        }
    }
    if (C == 2) {
        using namespace Pts2;
        while (T--) {
            cin >> n >> m;
            for (int i = 1; i <= m; i++) {
                int u, v;
                cin >> u >> v;
            }
            if (n & 1) printf("%d\n", Pow(2, n / 2 + 1) - 1 + Pow(2, n / 2) - 1);
            else printf("%d\n", (ll)2 * (Pow(2, n / 2) - 1 + Mod) % Mod);
        }
    }
    return 0;
}