#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 3e3 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

char a[N], b[N];
int x[N], y[N];
int ch[256];
int val[5][5];
ll f[N][N][3];
int A, B;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> (a + 1) >> (b + 1);
    ch['A'] = 1;
    ch['T'] = 2;
    ch['G'] = 3;
    ch['C'] = 4;
    int n = strlen(a + 1);
    int m = strlen(b + 1);
    for (int i = 1; i <= n; i++) x[i] = ch[a[i]];
    for (int i = 1; i <= m; i++) y[i] = ch[b[i]];
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            cin >> val[i][j];
        }
    }
    cin >> A >> B;
    for (int i = 1, len = max(n, m); i <= len; i++) {
        f[i][0][0] = f[i][0][2] = f[0][i][0] = f[0][i][1] = -INF;
        f[i][0][1] = f[0][i][2] = - A - (i - 1) * B;
    }
    f[0][0][1] = f[0][0][2] = -INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j][0] = *max_element(f[i - 1][j - 1], f[i - 1][j - 1] + 3) + val[x[i]][y[j]];
            f[i][j][1] = max(f[i - 1][j][1] - B, max(f[i - 1][j][0] - A, f[i - 1][j][2] - A));
            f[i][j][2] = max(f[i][j - 1][2] - B, max(f[i][j - 1][0] - A, f[i][j - 1][1] - A));
        }
    }
    printf("%lld\n", *max_element(f[n][m], f[n][m] + 3));
    return 0;
}