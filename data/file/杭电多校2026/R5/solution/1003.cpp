#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

const int mod = 998244353;

struct P {
    ll x, y;
    int t;
};

P operator-(const P& a, const P& b) {
    return {a.x - b.x, a.y - b.y, 0};
}

i128 cr(const P& a, const P& b) {
    return (i128)a.x * b.y - (i128)a.y * b.x;
}

i128 cr(const P& a, const P& b, const P& c) {
    return cr(b - a, c - a);
}

int half(const P& a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 0 : 1;
}

int add(int a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<P> p(n);
        for (P& x : p) cin >> x.x >> x.y >> x.t;

        sort(p.begin(), p.end(), [](const P& a, const P& b) {
            return tie(a.y, a.x) < tie(b.y, b.x);
        });

        if (n < 4) {
            cout << 0 << '\n';
            continue;
        }

        vector<vector<int>> o(n), rk(n, vector<int>(n, -1)), fp(n);
        for (int s = 0; s < n; ++s) {
            o[s].reserve(n - 1);
            for (int i = 0; i < n; ++i) {
                if (i != s) o[s].push_back(i);
            }

            sort(o[s].begin(), o[s].end(), [&](int a, int b) {
                P x = p[a] - p[s], y = p[b] - p[s];
                int ha = half(x), hb = half(y);
                if (ha != hb) return ha < hb;
                i128 z = cr(x, y);
                if (z != 0) return z > 0;
                i128 dx = (i128)x.x * x.x + (i128)x.y * x.y;
                i128 dy = (i128)y.x * y.x + (i128)y.y * y.y;
                if (dx != dy) return dx < dy;
                return a < b;
            });

            int z = n - 1;
            for (int i = 0; i < z; ++i) rk[s][o[s][i]] = i;
            fp[s].resize(z);
            int r = 1;
            for (int l = 0; l < z; ++l) {
                r = max(r, l + 1);
                P x = p[o[s][l]] - p[s];
                while (r < l + z) {
                    P y = p[o[s][r % z]] - p[s];
                    if (cr(x, y) <= 0) break;
                    ++r;
                }
                fp[s][l] = r;
            }
        }

        vector<vector<int>> dp(n, vector<int>(n));
        vector<int> w(n - 1), pre(2 * (n - 1) + 1);
        int ans = 0;

        for (int s = 0; s < n; ++s) {
            vector<int> v;
            for (int x : o[s]) {
                if (x > s) v.push_back(x);
            }
            int k = v.size(), z = n - 1;
            for (int bi = 0; bi < k; ++bi) {
                int b = v[bi];
                fill(w.begin(), w.end(), 0);
                w[rk[b][s]] = p[s].t != p[b].t;
                for (int ai = 0; ai < bi; ++ai) {
                    int a = v[ai];
                    w[rk[b][a]] = dp[a][b];
                }

                pre[0] = 0;
                for (int i = 0; i < 2 * z; ++i) pre[i + 1] = add(pre[i], w[i % z]);
                for (int ci = bi + 1; ci < k; ++ci) {
                    int c = v[ci];
                    if (p[b].t == p[c].t) {
                        dp[b][c] = 0;
                        continue;
                    }
                    int r = rk[b][c];
                    int val = pre[fp[b][r]] - pre[r + 1];
                    if (val < 0) val += mod;
                    dp[b][c] = val;
                    if (p[c].t != p[s].t && cr(p[b], p[c], p[s]) > 0) {
                        ans = add(ans, val);
                    }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
