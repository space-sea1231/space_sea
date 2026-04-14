#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e3 + 10;
const int M = 1e4 + 10;
const int MOD = 1e9 + 7;

int n, m;
int a[N];
int f[M];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    f[0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (i - a[j] >= 0) f[i] = ((ll)f[i] + f[i - a[j]]) % MOD;
        }
    }
    printf("%d\n", f[m]);
    return 0;
}