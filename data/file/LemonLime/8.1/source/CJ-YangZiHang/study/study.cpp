#include <iostream>
#include <stdio.h>
#include <cmath>
// #define __Debug

using namespace std;
typedef long long ll;
typedef __int128 i128;

const int N = 3e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll n, m;
ll a[N], b[N];

bool Check(ll src) {
    ll sum = n * m;
    for (int i = 1; i <= n; i++) {
        if (a[i] > b[i]) {
            ll res = src / a[i];
            if (src / a[i] * a[i] < src) res++;
            if (res > m) {
                res = m + (src - m * a[i]) / b[i];
                if ((src - m * a[i]) / b[i] * b[i] < (src - m * a[i])) res++;
            } 
            if (res > sum) return false;
            sum -= res;
        }
        else if (a[i] <= b[i]) {
            ll res = src / b[i];
            if (src / b[i] * b[i] < src) res++;
            if (res > sum) return false;
            sum -= res;
        }
        #ifdef __Debug
            printf("src=%lld sum=%lld\n", src, sum);
        #endif
    }
    return sum >= 0;
}
signed main() {
    freopen("study.in", "r", stdin);
    freopen("study.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    ll l = 1, r = INF, ans = 1;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (Check(mid)) {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}