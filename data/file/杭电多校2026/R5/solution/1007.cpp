#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
    int n;
    vector<int> t;

    BIT(int n = 0) {
        init(n);
    }

    void init(int x) {
        n = x;
        t.assign(n + 1, 0);
    }

    void add(int x, int v) {
        for (++x; x <= n; x += x & -x) t[x] += v;
    }

    int sum(int x) const {
        if (x < 0) return 0;
        int r = 0;
        for (++x; x > 0; x -= x & -x) r += t[x];
        return r;
    }

    int rng(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

struct PBIT {
    int mn, mx, len;
    BIT b[2];

    void init(int x, int y) {
        mn = x;
        mx = y;
        len = mx - mn + 1;
        int z = (len + 1) / 2 + 2;
        b[0].init(z);
        b[1].init(z);
    }

    void addv(int v, int d) {
        int x = v - mn;
        b[x & 1].add(x >> 1, d);
    }

    int cnt(int l, int r, int p) const {
        if (l > r) return 0;
        if ((l & 1) != p) ++l;
        if ((r & 1) != p) --r;
        if (l > r) return 0;
        int x = l - mn, y = r - mn;
        return b[x & 1].rng(x >> 1, y >> 1);
    }
};

int fix(ll x, int mod) {
    int r = x % mod;
    if (r < 0) r += mod;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        int N = n - 1, M = m - 1, g = std::gcd(N, M), d = 2 * g;

        auto pid = [&](int r) {
            if (r < 0) r += d;
            if (r >= d) r -= d;
            return min(r, d - r);
        };
        auto blen = [&](int t) {
            int l = max(1, 1 + t), r = min(n, m + t);
            return l > r ? 0 : r - l + 1;
        };
        auto slen = [&](int q) {
            int l = max(1, q - m + 2), r = min(n, q + 1);
            return l > r ? 0 : r - l + 1;
        };

        int tl = 1 - m, tr = n - 1, ql = 0, qr = n + m - 2;
        vector<vector<int>> bl(g + 1), sl(g + 1);
        vector<ll> bs(g + 1), ss(g + 1);
        vector<unsigned char> on(g + 1);
        for (int t = tl; t <= tr; t++) {
            int p = pid(fix(t, d));
            bl[p].push_back(t);
            bs[p] += blen(t);
        }
        for (int q = ql; q <= qr; q++) {
            int p = pid(fix(q, d));
            sl[p].push_back(q);
            ss[p] += slen(q);
        }

        PBIT bt, bq;
        bt.init(tl, tr);
        bq.init(ql, qr);
        auto c1 = [&](int t) {
            int l = max(1, 1 + t), r = min(n, m + t);
            if (l > r) return 0;
            int x = 2 * l - t - 2, y = 2 * r - t - 2;
            return bq.cnt(x, y, x & 1);
        };
        auto c2 = [&](int q) {
            int l = max(1, q - m + 2), r = min(n, q + 1);
            if (l > r) return 0;
            int x = 2 * l - q - 2, y = 2 * r - q - 2;
            return bt.cnt(x, y, x & 1);
        };
        auto cp = [&](int x, int y, int vx, int vy) {
            int a = vx == 1 ? x - 1 : 2 * N - x + 1;
            int b = vy == 1 ? y - 1 : 2 * M - y + 1;
            return pid(fix(1LL * a - b, d));
        };

        ll ans = 0;
        for (int i = 0; i < k; i++) {
            int x, y, vx, vy;
            cin >> x >> y >> vx >> vy;
            int p = cp(x, y, vx, vy);
            if (!on[p]) {
                on[p] = 1;
                ll add = bs[p] + ss[p];
                for (int t : bl[p]) add -= c1(t);
                for (int t : bl[p]) bt.addv(t, 1);
                for (int q : sl[p]) add -= c2(q);
                for (int q : sl[p]) bq.addv(q, 1);
                ans += add;
            }
            if (i) cout << ' ';
            cout << ans;
        }
        cout << '\n';
    }
    return 0;
}
