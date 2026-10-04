#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;
typedef __int128 lll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n;
ll p;
ll s[1000005];
lll f[1000005];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> p;
    ll sum = 0, best = -INF;
    for (int i = 1; i <= n; i++) {
        ll a;
        cin >> a;
        sum += a;
        if (sum > best) best = sum;
        if (sum < 0) sum = 0;
        s[i] = best;
    }
    f[1] = s[1];
    lll mx = f[1] + s[1];
    for (int i = 2; i <= n; i++) {
        f[i] = mx;
        lll tmp = f[i] + s[i];
        if (tmp > mx) mx = tmp;
    }
    lll ans = f[1];
    for (int i = 2; i <= n; i++) {
        if (f[i] > ans) ans = f[i];
    }
    ll res = (ll)(ans % p);
    printf("%lld\n", res);
    return 0;
}