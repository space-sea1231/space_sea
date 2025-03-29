#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define len(x) int((x).size())

using ll = long long;
using db = long double;

template <typename T>
inline bool ckmin(T &x, const T &y) {
    return y < x && (x = y, true);
}

template <typename T>
inline bool ckmax(T &x, const T &y) {
    return x < y && (x = y, true);
}

inline int p2(int n) {
    return 1 << n;
}

inline int msk2(int n) {
    return p2(n) - 1;
}

constexpr int N = 20, S = (1 << 16) + 5, V = 3.2e6 + 5, mo = 998442353, inf = 1e9;

inline int reduce(int x) {
    return x - (x >= mo) * mo;
}

inline void add(int &x, int y) {
    x = reduce(x + y);
}

int n, m, p[N][N];
int fac[V], ifac[V];
int dis[N][N], num[N][N];
int f[S][N], g[S][N];

ll qpow(ll b, ll e = mo - 2) {
    ll ans = 1;
    for (; e; e >>= 1) {
        if (e & 1)
            ans = ans * b % mo;
        b = b * b % mo;
    }
    return ans;
}

void math(int n) {
    *fac = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = ll(fac[i - 1]) * i % mo;
    ifac[n] = qpow(fac[n]);
    for (int i = n; i; --i)
        ifac[i - 1] = ll(ifac[i]) * i % mo;
    assert(ifac[0] == 1);
}

template <typename F>
void enumerate(int s, F f) {
    while (s) {
        int i = __builtin_ctz(s);
        s -= p2(i), f(i);
    }
}

void proc() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j <= n; ++j)
            cin >> p[i][j];
    }
    memset(dis, 0, sizeof dis);
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            ll x = 1;
            for (int k = 1; k <= n; ++k) {
                int d = abs(p[i][k] - p[j][k]);
                dis[i][j] += d, x = x * ifac[d] % mo;
            }
            dis[j][i] = dis[i][j];
            num[j][i] = num[i][j] = x * fac[dis[i][j]] % mo;
        }
    }
    memset(f, 63, sizeof f), memset(g, 0, sizeof g);
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        if (x)
            f[p2(i)][i] = 0, g[p2(i)][i] = 1;
    }
    for (int s = 1; s < p2(m); ++s)
        enumerate(s, [&](int i) {
            enumerate(s - p2(i), [&](int j) {
                int d = f[s - p2(i)][j] + dis[i][j], w = ll(g[s - p2(i)][j]) * num[i][j] % mo;
                if (ckmin(f[s][i], d))
                    g[s][i] = w;
                else if (f[s][i] == d)
                    add(g[s][i], w);
            });
        });
    int ans1 = inf, ans2 = 0, s = msk2(m);
    for (int i = 0; i < m; ++i) {
        if (ckmin(ans1, f[s][i]))
            ans2 = g[s][i];
        else if (ans1 == f[s][i])
            add(ans2, g[s][i]);
    }
    if (ans1 < inf)
        cout << ans1 << " " << ans2 << "\n";
    else
        cout << "NIE\n";
}

int main() {
    freopen("ge.in", "r", stdin);
    freopen("ge.out", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    math(V - 1);
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        proc();
}
