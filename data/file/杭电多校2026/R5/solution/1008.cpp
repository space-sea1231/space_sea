#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Seg {
    int l, r, len;
};

struct Qry {
    int l, r, id;
};

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
        for (; x <= n; x += x & -x) t[x] = max(t[x], v);
    }

    int qry(int x) {
        int r = 0;
        for (; x > 0; x -= x & -x) r = max(r, t[x]);
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        vector<Seg> a(n);
        vector<int> xs;
        xs.reserve(n);
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            a[i] = {l, r, r - l + 1};
            xs.push_back(l);
        }
        vector<Qry> b(q);
        for (int i = 0; i < q; i++) {
            cin >> b[i].l >> b[i].r;
            b[i].id = i;
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int m = xs.size();
        auto pos = [&](int x) {
            return lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1;
        };
        auto rev = [&](int x) {
            return m - x + 1;
        };

        sort(a.begin(), a.end(), [](const Seg& x, const Seg& y) {
            return x.r < y.r;
        });
        vector<Qry> o = b;
        sort(o.begin(), o.end(), [](const Qry& x, const Qry& y) {
            return x.r < y.r;
        });

        BIT bit(m);
        vector<int> ans(q);
        int j = 0;
        for (auto& x : o) {
            while (j < n && a[j].r <= x.r) {
                bit.add(rev(pos(a[j].l)), a[j].len);
                ++j;
            }
            auto it = lower_bound(xs.begin(), xs.end(), x.l);
            if (it == xs.end())
                ans[x.id] = 0;
            else
                ans[x.id] = bit.qry(rev(it - xs.begin() + 1));
        }
        for (int x : ans) cout << x << '\n';
    }
    return 0;
}
