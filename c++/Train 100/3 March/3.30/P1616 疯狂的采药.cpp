#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e4 + 10;
const int M = 1e7 + 10;
int n, m;
int w[N], v[N];
ll dp[M];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
    for (int i = 1; i <= n; i++) {
        for (int j = w[i]; j <= m; j++) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    printf("%lld\n", dp[m]);
    return 0;
}