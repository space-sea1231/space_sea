#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
ll a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, [&](int a, int b) {
        return a > b;
    });
    for (int i = 1; i <= n; i++) {
        if (a[i] == a[i + 1]) continue;
        if (m >= i * (a[i] - a[i + 1])) {
            m -= i * (a[i] - a[i + 1]);
        } else {
            a[i] -= m / i; m %= i;
            ll ans = 0;
            for (int j = 1; j <= i; j++) {
                if (m) {
                    m--;
                    ans += (a[i] - 1) * (a[i] - 1);
                } else ans += a[i] * a[i];
            }
            for (int j = i + 1; j <= n; j++) {
                ans += a[j] * a[j];
            }
            printf("%lld\n", ans);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}