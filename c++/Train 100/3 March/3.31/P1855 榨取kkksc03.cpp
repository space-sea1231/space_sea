#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e2 + 10;
int n, m, t;
int f[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        for (int j = m; j >= a; j--) {
            for (int k = t; k >= b; k--) {
                f[j][k] = max(f[j][k], f[j - a][k - b] + 1);
            }
        }        
    }
    printf("%d\n", f[m][t]);
    return 0;
}