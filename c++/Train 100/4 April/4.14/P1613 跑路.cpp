#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 65;

int n, m;
int dis[N][N];
bool f[N][N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        dis[u][v] = 1;
        f[u][v][0] = true;
    }
    for (int t = 1; t < N; t++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    if (f[i][k][t - 1] && f[k][j][t - 1]) {
                        f[i][j][t] = true;
                        dis[i][j] = 1;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    printf("%d\n", dis[1][n]);
    return 0;
}