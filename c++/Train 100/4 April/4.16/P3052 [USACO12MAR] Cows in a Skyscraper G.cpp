#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 20;

int n, m;
int num;
int a[N];
int f[1 << N], w[1 << N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int j = 1; j <= (1 << n) - 1; j++) {
        for (int i = 1; i <= n; i++) {
            if ((1 << (i - 1)) & j) w[j] += a[i];
        }
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= (1 << n) - 1; i++) {
        for (int j = i; j; j = (j - 1) & i) {
            if (w[j] <= m) f[i] = min(f[i], f[i - j] + 1);
        }
    }
    printf("%d\n", f[(1 << n) - 1]);
    return 0;
}