#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

ll n, m;
ll a[N];
ll ans;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    if (a[1] > m) {
        ans = a[1] - m;
        a[1] = m;
    }
    for (int i = 2; i <= n; i++) {
        if (a[i] + a[i - 1] > m) {
            ans += a[i] + a[i - 1] - m;
            a[i] = m - a[i - 1];
        }
    }
    printf("%lld\n", ans);
    return 0;
}