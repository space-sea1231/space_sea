#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int INF = 1e15 + 10;

ll n, m;
ll x[N], y[N];
    
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    ll minn = INF;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        minn = min(minn, x[i] + y[i]);
    }
    sort(x + 1, x + n + 1);
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        m -= x[i];
        if (m < 0) break;
        ans = max(ans, i + m / minn * 2);
    }
    printf("%lld\n", ans);
    return 0;
}