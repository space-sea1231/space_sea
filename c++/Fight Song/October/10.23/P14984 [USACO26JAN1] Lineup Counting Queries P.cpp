#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int Q;
ll l1, r1, l2, r2, t;

ll Calc(ll l, ll r) {
    return max(min(r, r1) - max(l, l1) + 1, 0ll);
}
ll Dfs(ll t, ll x) {
    if (x < 0) return 0;
    if (t == 0) return Calc(0, 0);
    ll len = (x + t % 3 + 1) / 3, s = t / 3 + 1;
    return Calc(s, s + len - 1) + Dfs(t / 3 * 2 + t % 3 - 1, x - len);
}
ll Solve() {
    cin >> l1 >> r1 >> l2 >> r2 >> t;
    if (l2 > (t >> 1)) return Calc(l2, r2);
    ll tot = Calc((t >> 1) + 1, r2);
    r2 = min(r2, t >> 1);
    return tot + Dfs(t, r2) - Dfs(t, l2 - 1);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> Q;
    while (Q--) printf("%lld\n", Solve());
    return 0;
}