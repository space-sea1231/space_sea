#pragma GCC optimize(2, 3, "Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
const int N = 100005, M = 22222 + 5, INF = 0x3f3f3f3f;
int T, n, rk[N], to[10][N], mn[M];
short a[N], f[N], g[N], val[N], msk[N];
string s;
void solve() {
    cin >> s;
    n = (int)s.size();
    for (int i = 0; i < n; ++i) a[i] = s[i] - '0';
    for (int i = 0; i <= n; ++i) rk[i] = 1, f[i] = g[i] = 0;
    for (int w = 1, cnt = 1; w * (w + 1) <= n << 1; ++w) {
        memset(msk + 1, 0, cnt * sizeof(short));
        for (int l = 0; l + w <= n; ++l)
            msk[rk[l]] |= 1 << a[l + w - 1];
        int tot = 0;
        for (int i = 1; i <= cnt; ++i)
            for (short x = msk[i]; x; x &= x - 1)
                to[__builtin_ctz(x)][i] = ++tot;
        cnt = tot, mn[0] = 0;
        for (int l = 0, num = 0, pos = 0; l + w <= n; ++l) {
            rk[l] = to[a[l + w - 1]][rk[l]];
            if (l >= w && val[l - w]) {
                while (num < val[l - w]) mn[++num] = INF;
                mn[val[l - w]] = min(mn[val[l - w]], rk[l - w]);
            }
            while (pos < f[l]) {
                if (++pos > num) num = pos;
                mn[pos] = 0;
            }
            if (w == 1 || a[l]) 
                val[l] = lower_bound(mn, mn + num + 1, rk[l]) - mn,
                g[l + w] = max(g[l + w], val[l]);
            else val[l] = 0;
        }
        for (int i = 1; i <= n; ++i)
            g[i] = max(g[i], g[i - 1]), f[i] = g[i];
    }
    cout << f[n] << '\n';
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> T;
    while (T--) solve();
    return 0;
}
