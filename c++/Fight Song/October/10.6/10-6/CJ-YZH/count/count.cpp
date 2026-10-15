#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 998244353;

int T;
ll n, m, x;

signed main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> x;
        if (n <= 500 && m <= 500) {
            ll ans = 0;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++)
                    for (int k = 0; k <= j - 1; k++)
                        ans = (ans + (i * k + x) / j) % Mod;
            printf("%lld\n", ans);
        } else if (n == 1) {
            printf("%lld\n", m % Mod * (x % Mod) % Mod);
        }
    }
    return 0;
}