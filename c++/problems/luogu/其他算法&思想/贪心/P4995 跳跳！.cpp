#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 3e2 + 10;

int n;
ll a[N], b[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int l = 1, r = n;
    int num = 0;
    while (l < r) {
        b[++num] = a[r];
        b[++num] = a[l];
        l++, r--;
        if (l >= r) break;
    }
    if (l == r) b[++num] = a[l];
    ll last = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (ll)(b[i] - last) * (b[i] - last);
        last = b[i];
    }
    printf("%lld\n", ans);
    return 0;
}