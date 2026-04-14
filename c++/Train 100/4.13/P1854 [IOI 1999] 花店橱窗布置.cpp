#include <iostream>
#include <stdio.h>
#include <cstring>
// #include <pair>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;

int n, m;
int a[N][N];
int f[N][N];
int ans[N];
pair<int, int> pre[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    memset(f, -0x3f, sizeof(f));
    for (int i = 0; i <= m; i++) f[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= m; j++) {
            if (f[i - 1][j - 1] + a[i][j] >= f[i][j - 1]) {
                f[i][j] = f[i - 1][j - 1] + a[i][j];
                pre[i][j] = {i - 1, j - 1};
            }
            else {
                f[i][j] = f[i][j - 1];
                pre[i][j] = {i, j - 1};
            }
        }
    }
    printf("%d\n", f[n][m]);
    for (int i = n, j = m; i > 0;) {
        if (pre[i][j].first == i - 1) ans[i] = j;
        i = pre[i][j].first, j = pre[i][j].second;
    }
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}