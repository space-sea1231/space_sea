#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int T, n;
ll a[N];

signed main() {
    // freopen("change.in", "r", stdin);
    // freopen("change.out", "w", stdout);

    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    // cin >> T;
    // while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        ll sum = 0, g = 0;
        for (int i = 1; i < n; i++) {
            sum += abs(a[i + 1] - a[i]);
            g = __gcd(g, abs(a[i + 1] - a[i]));
        }
        g *= 2;
        if (g == 0) printf("%lld\n", a[1] + sum);
        else printf("%lld\n", ((a[1] - 1) % g + g) % g + 1 + sum);
    // }
    return 0;
}