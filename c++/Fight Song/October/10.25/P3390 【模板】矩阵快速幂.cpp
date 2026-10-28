#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const int Mod = 1e9 + 7;

ll n, k;
int a[N][N], b[N][N];
int sum[N][N];

void Calc(int p[][N], int q[][N]) {
    for (int i = 1; i <= n; i++)  {
        for (int j = 1; j <= n; j++) {
            b[i][j] = 0;
            for (int k = 1; k <= n; k++) {
                b[i][j] = ((ll)b[i][j] + (ll)p[i][k] * q[k][j] % Mod) % Mod;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            p[i][j] = b[i][j];
        }
    }
}
void Pow() {
    for (int i = 1; i <= n; i++) sum[i][i] = 1;
    while (k) {
        if (k & 1) Calc(sum, a);
        Calc(a, a);
        k >>= 1;
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    Pow();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
    return 0;
}