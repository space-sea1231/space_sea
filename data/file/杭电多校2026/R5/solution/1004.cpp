#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

const ll mod = 1000000007;

ll qpow(ll a, ll n) {
    ll r = 1;
    while (n) {
        if (n & 1) r = (i128)r * a % mod;
        a = (i128)a * a % mod;
        n >>= 1;
    }
    return r;
}

pair<ll, ll> psum(ll q, ll n) {
    if (!n) return {1, 0};
    auto [pw, s] = psum(q, n / 2);
    ll ns = (i128)s * (1 + pw) % mod;
    ll np = (i128)pw * pw % mod;
    if (n & 1) {
        ns = (ns + np) % mod;
        np = (i128)np * q % mod;
    }
    return {np, ns};
}

ll pdiff(ll a, ll b, ll n) {
    ll r = qpow(a, n) - qpow(b, n);
    if (r < 0) r += mod;
    return r;
}

void solve() {
    ll n, c;
    int m;
    cin >> n >> m >> c;

    vector<ll> sw(m + 1), sa(m + 1);
    for (int i = 1; i <= m; ++i) {
        ll w;
        cin >> w;
        sw[i] = sw[i - 1] + w;
        sa[i] = sa[i - 1] + (i128)i * w;
    }

    ll W = sw[m];
    auto ok = [&](int x) {
        i128 tw = (i128)sw[m] - sw[x];
        i128 ta = sa[m] - sa[x];
        return ta - (i128)x * tw <= (i128)c * W;
    };

    int s = 0;
    while (s <= m && !ok(s)) ++s;
    if (!s) {
        cout << 0 << '\n';
        return;
    }

    ll iw = qpow(W % mod, mod - 2);
    ll q = (i128)(sw[s - 1] % mod) * iw % mod;
    ll et = psum(q, n).second;
    ll ha = (sa[m] - sa[s - 1]) % mod;
    ll e = (i128)et * ha % mod * iw % mod;

    for (int v = 1; v < s; ++v) {
        if (sw[v] == sw[v - 1]) continue;
        ll a = (i128)(sw[v] % mod) * iw % mod;
        ll b = (i128)(sw[v - 1] % mod) * iw % mod;
        e = (e + (i128)v * pdiff(a, b, n)) % mod;
    }

    ll ans = (e - (i128)(c % mod) * et) % mod;
    if (ans < 0) ans += mod;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
