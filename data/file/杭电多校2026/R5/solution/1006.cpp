#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> zf(const string& s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

struct BIT {
    int n;
    vector<ll> t;

    BIT(int n) : n(n), t(n + 1, 0) {
    }

    void add(int x, ll v) {
        if (x <= 0) return;
        for (; x <= n; x += x & -x) t[x] += v;
    }

    ll sum(int x) {
        ll r = 0;
        for (; x > 0; x -= x & -x) r += t[x];
        return r;
    }
};

void solve() {
    int la, lb, lc;
    cin >> la >> lb >> lc;
    string a, b, c;
    cin >> a >> b >> c;

    vector<int> zc = zf(a + "#" + c), zb = zf(a + "#" + b);
    vector<ll> cc(la + 2);
    for (int i = 0; i < lc; i++) ++cc[min(zc[la + 1 + i], la)];
    for (int i = la; i >= 1; i--) cc[i] += cc[i + 1];

    vector<vector<int>> add(la + 2);
    for (int i = 0; i < lb; i++) {
        int x = min(zb[la + 1 + i], la);
        if (x) add[x].push_back(i);
    }

    BIT bc(lb + 5), bs(lb + 5);
    set<int> st;
    ll ans = 0;
    for (int L = la; L >= 1; L--) {
        for (int k : add[L]) {
            auto it = st.insert(k).first, pl = it, nx = it;
            bool hp = it != st.begin();
            ++nx;
            bool hn = nx != st.end();
            if (hp) {
                --pl;
                if (hn) {
                    int d = *nx - *pl;
                    bc.add(d, -1);
                    bs.add(d, -d);
                }
                int d = k - *pl;
                bc.add(d, 1);
                bs.add(d, d);
            }
            if (hn) {
                int d = *nx - k;
                bc.add(d, 1);
                bs.add(d, d);
            }
        }

        ll cb = 0;
        if (!st.empty()) {
            ll m = st.size();
            int lim = L - 1;
            ll ov = bc.sum(lim) * L - bs.sum(lim);
            cb = m * L - ov;
        }
        ans += cb * cc[L];
    }
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
