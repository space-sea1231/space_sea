#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e3 + 10;
int n, m, x, y;
bool a[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> x >> y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    int sum = 0;
    for (int i = n; i > x; i--) {
        for (int j = 1; j <= m; j++) {
            sum += a[i][j];
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; j++) ans += a[x][j];
    printf("%d %d\n", sum + 1, sum + ans);
    return 0;
}