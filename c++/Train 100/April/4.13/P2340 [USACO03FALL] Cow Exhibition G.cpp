#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 4e2 + 10;
const int M = 1e3 + 10;
const int K = 4e5;

int n;
int v[N], w[N];
int f[(K + 10) << 1];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];
    memset(f, -0x3f, sizeof(f));
    f[K] = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] >= 0) {
            for (int j = K * 2; j >= v[i]; j--) {
                f[j] = max(f[j], f[j - v[i]] + w[i]);
            }
        }
        else {
            for (int j = 0; j <= K * 2 + v[i]; j++) {
                f[j] = max(f[j], f[j - v[i]] + w[i]);
            }
        }
    }
    int ans = 0;
    for (int i = K; i <= K * 2; i++) {
        if (f[i] >= 0) ans = max(ans, f[i] + i - K);
    }
    printf("%d\n", ans);
    return 0;
}