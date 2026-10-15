#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10, mod = 1e9 + 7;
int n, c[N], cnt, x, y, dp[N], add[N];
signed main() {
    // freopen("resona.in", "r", stdin);
    // freopen("resona.out", "w", stdout);
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (x == y) continue;
        c[++cnt] = x, y = x;
    }
    n = cnt, dp[0] = 1;
    for (int i = 1; i <= n; i++) add[c[i]] = (add[c[i]] + dp[i - 1]) % mod, dp[i] = add[c[i]];
    printf("%d\n", dp[n] % mod);
    return 0;
}
