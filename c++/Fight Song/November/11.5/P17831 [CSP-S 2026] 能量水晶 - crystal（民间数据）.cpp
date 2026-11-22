#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

int n;
ll m;
ll a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    // for (int i = 1; i <= n; i++) printf("%lld ", a[i]); printf("\n");
    // for (int i = 0; i <= 200; i++) printf("%d:%d\n", i - 100, cnt[i]);
    // for (int i = 0; i <= 200; i++) {
    //     printf("%d:%d\n", i - 100, cnt[i]);
    // }
    int pos = 1, ans = 0;
    ll sum = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
        sum += (a[i] - a[i - 1]) * (i - 1);
        // if (i == 136125) printf("%lld\n", sum);
        // if (i == 428133) printf("%lld %d\n", sum, pos);
        // lst = sum;
        // printf("%d->%lld\n", i, sum);
        while (pos <= i && sum - (((pos - 1) * a[i]) - tot) > m) {
            tot += a[pos++];
            // printf("%d %d %lld\n", i, pos, lst - sum);
            // lst = sum;
        }
        ans = max(ans, i - pos + 1);
    }
    // ll tot = 0;
    // for (int i = 1; i <= n; i++) {
    //     sum += (a[i] - a[i - 1]) * (i - 1);
    //     tot += a[428133] - a[i];
    //     if (i == 112858) printf("%lld\n", tot);
    //     if (i == 428133) {
    //         printf("%lld %lld\n", sum, tot);
    //         return 0;
    //     }
    //     // lst = sum;
    //     // printf("%d->%lld\n", i, sum);
    //     ans = max(ans, i - pos + 1);
    // }
    printf("%lld\n", ans);
    return 0;
}