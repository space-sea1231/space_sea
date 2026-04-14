#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 55;
const int M = 2e5 + 10;

char c[N];
int n;
int sum[N][N];
int f[N][M];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> (c + 1) >> n;
    int len = strlen(c + 1);
    for (int i = 1; i <= len; i++) {
        for (int j = i; sum[i][j - 1] <= 1000000 && j <= len; j++) {
            sum[i][j] = sum[i][j - 1] * 10 + (c[j] - '0');
        }
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = -1;
    for (int i = 1; i <= len; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = i - 1; k >= 0 && sum[k + 1][i] <= min(n, j); k--) {
                f[i][j] = min(f[i][j], f[k][j - sum[k + 1][i]] + 1);
            }
        }
    }
    if (f[len][n] < 41) printf("%d\n", f[len][n]);
    else printf("-1\n");
    return 0;
}