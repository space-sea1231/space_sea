#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 1e9 + 7;

ll n, m, x;
namespace Pts1 {
    const int N = 5e2 + 10;
    int g[N][N];

    int Gcd(int a, int b) {
        while (b ^= a ^= b ^= a %= b);
        return a;
    }
    int C(int x, int y) {
        int sum = 0;
        for (int a = 1; a <= x; a++) {
            for (int b = 1; b <= x; b++) {
                for (int c = 1; c <= x; c++) {
                    for (int d = 1; d <= x; d++) {
                        sum = sum + ((a * d - b * c) / y * y == (a * d - b * c));
                        if (sum >= Mod) sum -= Mod;
                    }
                }
            }
        }
        return sum;
    }
}
signed main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> x;
    using namespace Pts1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            g[i][j] = Gcd(i, j);
        }
    }
    ll S = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            S = S + C(g[i][j], g[g[n][m]][x]);
            if (S > Mod) S %= Mod;
        }
    }
    printf("%lld\n", S);
    return 0;
}