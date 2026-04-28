#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 40;

int n;
int a[N];
int f[N][N];
int pre[N][N];

void Dfs(int l, int r) {
    if (l > r) return;
    printf("%d ", pre[l][r]);
    Dfs(l, pre[l][r] - 1);
    Dfs(pre[l][r] + 1, r);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 1; j <= n; j++) f[i][j] = 1;
        f[i][i] = a[i];
        pre[i][i] = i;
    }
    for (int k = 2; k <= n; k++) {
        for (int l = 1; l + k - 1 <= n; l++) {
            int r = l + k - 1;
            for (int i = l; i <= r; i++) {
                if (f[l][r] < f[l][i - 1] * f[i + 1][r] + a[i]) {
                    f[l][r] = f[l][i - 1] * f[i + 1][r] + a[i];
                    pre[l][r] = i;
                }
                
            }
        }
    }
    printf("%d\n", f[1][n]);
    Dfs(1, n);
    return 0;
}