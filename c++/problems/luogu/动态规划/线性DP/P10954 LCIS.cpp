#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 3e3 + 10;

int n;
int a[N], b[N];
int f[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) {
        int val = 0;
        for (int j = 1; j <= n; j++) {
            if (a[i] == b[j]) f[i][j] = val + 1;
            else f[i][j] = f[i - 1][j];
            if (b[j] < a[i]) val = max(val, f[i - 1][j]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[n][i]);
    printf("%d\n", ans);

    return 0;
}