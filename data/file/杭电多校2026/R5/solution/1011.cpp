#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 998244353;

struct E {
    int c, d, b;
};

struct C {
    int i = 0, b = -1;
};

struct Top {
    C x, y;

    void add(int i, int b) {
        if (x.i && x.b == b)
            x.i = i;
        else if (y.i && y.b == b)
            y.i = i, swap(x, y);
        else
            y = x, x = {i, b};
    }
};

struct I {
    int b = 1;
    size_t o = 0;
};

struct U {
    int c = 0, d = 0;
    array<int, 11> a{};
};

class Sol {
   public:
    explicit Sol(int x) : n(x), g(n), del(n, 0), par(n, -1), sz(n), md(n), path(n), ix(n) {
        int h = 2;
        while ((1 << min(h, 30)) < max(1, n)) ++h;
        for (auto& v : path) v.reserve(h + 1);
    }

    void add(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build() {
        build_lca();
        dc(0);
        size_t z = 0;
        for (int c = 0; c < n; c++) {
            int b = 1;
            while (b <= md[c]) b <<= 1;
            ix[c] = {b, z};
            z += (size_t)2 * b;
        }
        slot.resize(z);
    }

    void upd(int id, int c, int l, int r) {
        if (l > r) return;
        for (const E& e : path[c]) {
            ll x = (ll)l - e.d, y = (ll)r - e.d;
            if (y < 0 || x > md[e.c]) continue;
            int L = max(0LL, x), R = min((ll)md[e.c], y);
            if (L <= R) ins(e.c, L, R, id, e.b);
        }
    }

    int get(int v) const {
        int ans = 0;
        for (const E& e : path[v]) {
            const I& t = ix[e.c];
            int p = t.b + e.d;
            while (p > 0) {
                const Top& x = slot[t.o + p];
                chk(x.x, e.b, ans);
                chk(x.y, e.b, ans);
                p >>= 1;
            }
        }
        return ans;
    }

    int dist(int u, int v) const {
        int x = lca(u, v);
        return dep[u] + dep[v] - 2 * dep[x];
    }

   private:
    int n;
    vector<vector<int>> g;
    vector<char> del;
    vector<int> par, sz, md;
    vector<vector<E>> path;
    vector<I> ix;
    vector<Top> slot;
    int lg = 0;
    vector<int> dep;
    vector<vector<int>> up;

    static void chk(const C& x, int b, int& ans) {
        if (!x.i) return;
        if (b >= 0 && x.b == b) return;
        ans = max(ans, x.i);
    }

    void build_lca() {
        lg = 1;
        while ((1 << lg) <= n) ++lg;
        dep.assign(n, 0);
        up.assign(lg, vector<int>(n));
        vector<int> o(1, 0);
        for (int i = 0; i < (int)o.size(); i++) {
            int u = o[i];
            for (int v : g[u]) {
                if (v == up[0][u]) continue;
                up[0][v] = u;
                dep[v] = dep[u] + 1;
                o.push_back(v);
            }
        }
        for (int k = 1; k < lg; k++)
            for (int u = 0; u < n; u++) up[k][u] = up[k - 1][up[k - 1][u]];
    }

    int lca(int u, int v) const {
        if (dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for (int k = 0; k < lg; k++)
            if ((d >> k) & 1) u = up[k][u];
        if (u == v) return u;
        for (int k = lg - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
        }
        return up[0][u];
    }

    int cent(int s) {
        vector<int> a(1, s);
        par[s] = -1;
        for (int i = 0; i < (int)a.size(); i++) {
            int u = a[i];
            for (int v : g[u]) {
                if (del[v] || v == par[u]) continue;
                par[v] = u;
                a.push_back(v);
            }
        }
        for (int u : a) sz[u] = 1;
        for (int i = (int)a.size() - 1; i > 0; i--) {
            int u = a[i];
            sz[par[u]] += sz[u];
        }

        int tot = a.size(), c = s, best = tot;
        for (int u : a) {
            int mx = tot - sz[u];
            for (int v : g[u])
                if (!del[v] && par[v] == u) mx = max(mx, sz[v]);
            if (mx < best) best = mx, c = u;
        }
        return c;
    }

    void dc(int s) {
        int c = cent(s);
        path[c].push_back({c, 0, -1});
        md[c] = 0;
        struct W {
            int u, p, d;
        };
        vector<W> stk;
        for (int v : g[c]) {
            if (del[v]) continue;
            stk.clear();
            stk.push_back({v, c, 1});
            while (!stk.empty()) {
                W x = stk.back();
                stk.pop_back();
                path[x.u].push_back({c, x.d, v});
                md[c] = max(md[c], x.d);
                for (int y : g[x.u]) {
                    if (del[y] || y == x.p || y == c) continue;
                    stk.push_back({y, x.u, x.d + 1});
                }
            }
        }
        del[c] = 1;
        for (int v : g[c])
            if (!del[v]) dc(v);
    }

    void ins(int c, int l, int r, int id, int b) {
        const I& t = ix[c];
        int x = l + t.b, y = r + t.b + 1;
        while (x < y) {
            if (x & 1) slot[t.o + x].add(id, b), ++x;
            if (y & 1) --y, slot[t.o + y].add(id, b);
            x >>= 1;
            y >>= 1;
        }
    }
};

int val(const U& u, int d) {
    ll r = 0;
    for (int i = u.d; i >= 0; i--) r = (r * d + u.a[i]) % mod;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        Sol sol(n);
        for (int i = 0; i + 1 < n; i++) {
            int u, v;
            cin >> u >> v;
            sol.add(--u, --v);
        }
        sol.build();
        vector<U> up(q + 1);
        for (int op = 1; op <= q; op++) {
            int tp;
            cin >> tp;
            if (tp == 1) {
                int v, l, r, d;
                cin >> v >> l >> r >> d;
                --v;
                U u;
                u.c = v;
                u.d = d;
                for (int i = 0; i <= d; i++) {
                    ll x;
                    cin >> x;
                    x %= mod;
                    if (x < 0) x += mod;
                    u.a[i] = x;
                }
                up[op] = u;
                sol.upd(op, v, l, r);
            } else {
                int v;
                cin >> v;
                --v;
                int id = sol.get(v);
                if (!id)
                    cout << 0 << '\n';
                else
                    cout << val(up[id], sol.dist(up[id].c, v)) << '\n';
            }
        }
    }
    return 0;
}
