#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 51;
const int K = 2.5e3 + 10;

int n, m, t;
int f[N][K];
int g[N][N][K];
int sum[N][N];
bool a[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
            // printf("%d", a[i][j]);
            sum[i][j] = sum[i][j - 1] + a[i][j];
        }
        // printf("\n");
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int j1 = 0; j1 < j; j1++) {
                for (int k = 1; k <= t; k++) {
                    g[i][j][k] = max(g[i][j][k], g[i][j1][k - 1] + max(sum[i][j] - sum[i][j1], j - j1 - (sum[i][j] - sum[i][j1])));
                    // if (i == 1 & j == 2 && k == 1) {
                    //     if (j1 == 0) cerr<<g[i][j1][k - 1] << " " << sum[i][j] << "\n";
                    // }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <= t; k++) {
            for (int k1 = 0; k1 <= k; k1++) {
                f[i][k] = max(f[i][k], f[i - 1][k1] + g[i][m][k - k1]);
            }
        }
    }
    // cerr<<f[1][1] << endl;
    // cerr<<g[1][2][1];
    printf("%d\n", f[n][t]);
    //g[i][j][k] = max(g[i][j`][k-1] + max(sum[j`+1][j], j - j` - sum[j`+1][j]))
    //f[i][k] = max(f[i-1][k`]+g[i][m][k-k`])
    return 0;
}