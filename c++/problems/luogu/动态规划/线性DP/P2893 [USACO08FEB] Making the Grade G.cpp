#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <unordered_map>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 2e3 + 10;
const int INF = 0x3f3f3f3f;

int n;
int ans = INF;
int a[N], tmp[N];
int f[N][N];
// unordered_map<int, int> idx;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp[i] = a[i];
    }
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    // for (int i = 1; i <= len; i++) idx[tmp[i]] = i;
    #ifdef __Debug
    // for (int i = 1; i <= n; i++) printf("idx[%d]=%d\n", a[i], idx[a[i]]);
    for (int i = 1; i <= len; i++) printf("tmp[%d]=%d\n", i, tmp[i]);
    #endif
    for (int i = 1; i <= n; i++) {
        int val = INF;
        for (int j = 1; j <= len; j++) {
            val = min(val, f[i - 1][j]);
            f[i][j] = val + abs(a[i] - tmp[j]);
        }
    }
    #ifdef __Debug
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= len; j++) {
            printf("f[%d][%d] = %d\n", i, j, f[i][j]);
        }
    }
    #endif
    for (int i = 1; i <= len; i++) ans = min(ans, f[n][i]);
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) {
        int val = INF;
        for (int j = len; j >= 1; j--) {
            val = min(val, f[i - 1][j]);
            f[i][j] = val + abs(a[i] - tmp[j]);
        }
    }
    for (int i = 1; i <= len; i++) ans = min(ans, f[n][i]);
    printf("%d\n", ans);
    return 0;
}