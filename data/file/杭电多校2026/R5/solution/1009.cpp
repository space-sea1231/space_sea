#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll iv(ll a, ll m) {
    ll x = 1, y = 0, b = m;
    while (b) {
        ll q = a / b, t = a - q * b;
        a = b, b = t;
        t = x - q * y, x = y, y = t;
    }
    return (x % m + m) % m;
}

bool crt(ll& x, ll& m, int a, int p) {
    ll g = std::gcd(m % p, (ll)p);
    if ((a - x % g) % g) return false;
    ll q = p / g;
    if (q == 1) return true;
    ll d = (a - x % p) / g % q;
    if (d < 0) d += q;
    ll t = d * iv(m / g % q, q) % q;
    x += m * t;
    m *= q;
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int& x : a) cin >> x, --x;
    for (int& x : b) cin >> x, --x;

    const int K = 10;
    vector<int> cur = a, nxt(n);
    for (int k = 0; k < K; k++) {
        if (cur == b) {
            cout << k << '\n';
            return;
        }
        for (int i = 0; i < n; i++) nxt[i] = cur[cur[i]];
        cur.swap(nxt);
    }

    ll x = 0, m = 1;
    vector<int> vis(n), pre(n, -1);
    for (int y : cur) vis[y] = 1;
    for (int s = 0; s < n; s++) {
        if (!vis[s]) continue;
        int L = 0, y = s;
        do {
            vis[y] = 0;
            pre[cur[y]] = y;
            y = cur[y];
            ++L;
        } while (y != s);

        int r = 0;
        for (y = s; y != b[s] && r < L; ++r) y = cur[y];
        if (y != b[s]) {
            cout << -1 << '\n';
            return;
        }
        if (L > 1) {
            int e = -1, ord = 0, w = 1;
            do {
                if (w == r) e = ord;
                w = w * 2 % L;
                ++ord;
            } while (w != 1);
            if (e < 0 || !crt(x, m, e, ord)) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (pre[b[cur[i]]] != b[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << x + K << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
