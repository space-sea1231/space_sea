#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

typedef long long ll;
using namespace std;

const int N = 40;

int k;
int a[N];

signed main() {
    // freopen("std.in", "r", stdin);
    // freopen("std.out", "w", stdout);
    cin.tie() -> ios::sync_with_stdio(0);
    while (cin >> k, k) {
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= k; i++) cin >> a[i];
        ll f[a[1] + 1][a[2] + 1][a[3] + 1][a[4] + 1][a[5] + 1];
        memset(f, 0, sizeof(f));
        f[0][0][0][0][0] = 1;
        for (int i1 = 0; i1 <= a[1]; i1++) {
            for (int i2 = 0; i2 <= a[2]; i2++) {
                for (int i3 = 0; i3 <= a[3]; i3++) {
                    for (int i4 = 0; i4 <= a[4]; i4++) {
                        for (int i5 = 0; i5 <= a[5]; i5++) {
                            if (i1 < a[1]) f[i1 + 1][i2][i3][i4][i5] += f[i1][i2][i3][i4][i5];
                            if (i2 < a[2] && i2 < i1) f[i1][i2 + 1][i3][i4][i5] += f[i1][i2][i3][i4][i5];
                            if (i3 < a[3] && i3 < i2) f[i1][i2][i3 + 1][i4][i5] += f[i1][i2][i3][i4][i5];
                            if (i4 < a[4] && i4 < i3) f[i1][i2][i3][i4 + 1][i5] += f[i1][i2][i3][i4][i5];
                            if (i5 < a[5] && i5 < i4) f[i1][i2][i3][i4][i5 + 1] += f[i1][i2][i3][i4][i5];
                        }
                    }
                }
            }
        }
        printf("%lld\n", f[a[1]][a[2]][a[3]][a[4]][a[5]]);
    }
    return 0;
}