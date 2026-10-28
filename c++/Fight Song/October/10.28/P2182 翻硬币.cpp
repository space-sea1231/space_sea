#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 210;
const int Mod = 1e9 + 7;

int n, k, m, tot;
char a[N], b[N];
ll sum[N][N], f[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k >> m;
    cin >> (a + 1) >> (b + 1);
    for (int i = 1; i <= n; i++) if (a[i] != b[i]) tot++;
    int lim = max(n, m);
    for (int i = 0; i <= lim; i++) sum[i][0] = sum[i][i] = 1;
    for (int i = 1; i <= lim; i++) {
        for (int j = 1; j < i; j++) {
            sum[i][j] = (sum[i - 1][j] + sum[i - 1][j - 1]) % Mod;
        }
    }
    f[0][tot] = 1;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            for (int r = 0; r <= min(j, m); r++) {
                int nxt = j - 2 * r + m;
                if (nxt >= 0 && nxt <= n) {
                    ll ways = f[i - 1][j] * sum[n - j][m - r] % Mod * sum[j][r] % Mod;
                    f[i][nxt] = (f[i][nxt] + ways) % Mod;
                }
            }
        }
    }
    
    printf("%lld\n", f[k][0]);
    return 0;
}