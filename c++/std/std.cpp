#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
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
int edge[M][M];
double f[N][N][2];
double k[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    memset(edge, 0x3f, sizeof(edge));
    cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 2; k++) {
                f[i][j][k] = INF_DOUBLE;
            }
        }
    }
    f[1][0][0] = f[1][1][1] = 0;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i <= n; i++) cin >> k[i];
    for (int i = 1; i <= e; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        edge[x][y] = edge[y][x] = min(edge[x][y], z);
    }
    for (int i = 1; i <= e; i++) {
        for (int j = 1; j <= e; j++) {
            if (i == j) continue;
            for (int k = 1; k <= e; k++) {
                if (k == j) continue;
                edge[i][j] = min(edge[i][j], edge[i][k] + edge[k][j]);
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {

        }
    }
    return 0;
}