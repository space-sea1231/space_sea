#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 17;

int n, m;
int f[1 << N];
int stat[1 << N], staw[1 << N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> m >> n;
    int S = (1 << n) - 1;
    for (int i = 1; i <= n; i++) {
        int t, w;
        cin >> t >> w;
        for (int j = 1; j <= S; j++) {
            if (1 << (i - 1) & j) {
                stat[j] = max(stat[j], t);
                staw[j] += w;
            }
        }
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i <= S; i++) {
        if (staw[i] <= m) f[i] = stat[i];
        for (int j = i; j; j = (j - 1) & i) {
            if (staw[i ^ j] <= m) f[i] = min(f[i], f[j] + stat[i ^ j]);
        }
    }
    printf("%d\n", f[S]);
    return 0;
}