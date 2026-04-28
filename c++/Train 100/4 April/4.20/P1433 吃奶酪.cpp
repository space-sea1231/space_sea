#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cmath>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 16;
const int INF = 1e18;

int n;
double x[N], y[N];
double dis[N][N];
double f[N][1 << N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dis[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        }
    }
    memset(f, 0x43, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][1 << (i - 1)] = dis[0][i];
    for (int k = 1; k < (1 << n); k++) {
        for (int i = 1; i <= n; i++) {
            if ((k & (1 << (i - 1))) == false) continue;
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                if ((k & (1 << (j - 1))) == false) continue;
                f[i][k] = min(f[i][k], f[j][k ^ (1 << (i - 1))] + dis[i][j]);
            }
        }       
    }
    double ans = INF;
    for (int i = 1; i <= n; i++) ans = min(ans, f[i][(1 << n) - 1]);
    printf("%.2lf\n", ans);
    return 0;
}