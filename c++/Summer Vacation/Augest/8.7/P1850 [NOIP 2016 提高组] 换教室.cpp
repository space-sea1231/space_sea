#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const double INF_DOUBLE = 1e9;
const int N = 2e3 + 10;
const int M = 3e2 + 10;

int n, m, v, e;
int c[N], d[N];
int dis[M][M];
double f[N][N][2];
double p[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < 2; k++) {
                f[i][j][k] = INF_DOUBLE;
            }
        }
    }
    f[1][0][0] = f[1][1][1] = 0;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= v; i++) dis[i][i] = 0;
    for (int i = 1; i <= e; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        dis[x][y] = dis[y][x] = min(dis[x][y], z);
    }
    for (int k = 1; k <= v; k++) {
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j < i; j++) {
                dis[i][j] = dis[j][i] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
            // printf("dis[%d][%d]=%d\n", i, j, dis[i][j]);
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0, lim = min(i, m); j <= lim; j++) {
            f[i][j][0] = min(f[i - 1][j][0] + dis[c[i - 1]][c[i]],
                             f[i - 1][j][1] + dis[c[i - 1]][c[i]] * (1 - p[i - 1]) +
                                 dis[d[i - 1]][c[i]] * p[i - 1]);
            if (j) f[i][j][1] = min(f[i - 1][j - 1][0] + dis[c[i - 1]][d[i]] * p[i] + 
                                        dis[c[i - 1]][c[i]] *  (1 - p[i]),
                                    f[i - 1][j - 1][1] + dis[d[i - 1]][d[i]] * p[i - 1] * p[i] +
                                        dis[d[i - 1]][c[i]] * p[i - 1] * (1 - p[i]) + 
                                        dis[c[i - 1]][d[i]] * (1 - p[i - 1]) * p[i] + 
                                        dis[c[i - 1]][c[i]] * (1 - p[i - 1]) * (1 - p[i]));
            // printf("f[%d][%d] = %.2lf %.2lf\n", i, j, f[i][j][0], f[i][j][1]);        
        }
    }
    double ans = INF_DOUBLE;
    for (int i = 0; i <= m; i++) ans = min(ans, min(f[n][i][0], f[n][i][1]));
    printf("%.2lf\n", round(ans * 100) / 100);
    return 0;
}