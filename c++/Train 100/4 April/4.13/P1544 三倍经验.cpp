#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;
const int K = 6e3 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
ll a[N][N];
ll f[N][N][K];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i <= m; i++) f[1][1][i] = (i && a[1][1] > 0) ? a[1][1] * 3:a[1][1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= m; k++) {//2 2
                ll cas1 = (j == 1) ? -INF:f[i - 1][j - 1][k] + a[i][j];
                ll cas2 = (j == i) ? -INF:f[i - 1][j][k] + a[i][j];
                ll cas3 = (k == 0|| j == 1) ? -INF:f[i - 1][j - 1][k - 1] + a[i][j] * 3;
                ll cas4 = (k == 0 || j == i) ? -INF:f[i - 1][j][k - 1] + a[i][j] * 3;
                // if (i == 2 && j == 2 && k == 0) printf("%lld %lld %lld %lld\n", cas1, cas2, cas3, cas4);
                f[i][j][k] = max(cas1, max(cas2, max(cas3, cas4)));
            }
        }
    }
    ll ans = -INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            ans = max(ans, f[n][i][j]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}