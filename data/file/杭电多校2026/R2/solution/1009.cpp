#include <bits/stdc++.h>

using i64 = long long;

#define debug(a) std::cout << #a << '=' << (a) << ' '

template <class T>
inline void chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
    }
}
template <class T>
inline void chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
    }
}

const int mod = 998244353; // 模数需要根据实际问题调整

template <class T>
inline int norm(T x) {
    x %= mod;
    return x < 0 ? x + mod : x;
}

inline void add(int &x, const int &y) {
    x += y; if (x >= mod) x -= mod;
}
inline void dec(int &x, const int &y) {
    x -= y; if (x < 0) x += mod;
}
inline void mul(int &x, const int &y) {
    x = 1ll * x * y % mod;
}
inline void neg(int &x) {
    if (x) x = mod - x;
}

template <class T>
constexpr int qpow(int a, T b, int p) {
    int ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
    }
    return ans;
}

// 预处理单位根
constexpr auto findRootPower(int mod, int g) {
    std::array<int, 32> w{};
    for (int k = 1, idx = 0; (mod - 1) % (k << 1) == 0; k <<= 1) {
        w[idx ++] = qpow(g, (mod - 1) / (k << 1), mod); // 2k 阶单位根
    }
    return w;
}

constexpr auto RootPower = findRootPower(mod, 3);

std::vector<int> rev;
void dft(std::vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n; i ++) {
        if (i < rev[i]) {
            std::swap(a[i], a[rev[i]]);
        }
    }
    for (int k = 1, idx = 0; k < n; k <<= 1) {
        int omega = RootPower[idx ++];
        for (int i = 0; i < n; i += (k << 1)) {
            int x = 1;
            for (int j = 0; j < k; j ++, mul(x, omega)) {
                int u = a[i + j], v = 1ll * x * a[i + j + k] % mod;
                add(a[i + j] = u, v), dec(a[i + j + k] = u, v);
            }
        }
    }
}
void idft(std::vector<int> &a) {
    int n = a.size(), inv = qpow(n, mod - 2, mod);
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    for (int i = 0; i < n; i ++) {
        mul(a[i], inv);
    }
}

// 多项式
struct poly : public std::vector<int> {
    poly() : std::vector<int>() {}
    explicit constexpr poly(int n) : std::vector<int>(n) {}
    explicit constexpr poly(const std::vector<int> &a) : std::vector<int>(a) {}
    constexpr poly(const std::initializer_list<int> &a) : std::vector<int>(a) {}

    template <class InputIt, class = std::_RequireInputIter<InputIt>>
    explicit constexpr poly(InputIt st, InputIt ed) : std::vector<int>(st, ed) {}

    // 多项式乘法
    constexpr friend poly operator * (poly a, poly b) {
        int tot = a.size() + b.size() - 1;
        if (tot < 128) {
            poly c(tot);
            for (int i = 0; i < a.size(); i ++) {
                for (int j = 0; j < b.size(); j ++) {
                    c[i + j] = (c[i + j] + 1ll * a[i] * b[j]) % mod;
                }
            }
            return c;
        }

        int L = 1, P = 0;
        while (L < tot) L <<= 1, P ++;
        rev.resize(L);
        for (int i = 0; i < L; i ++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (P - 1));
        }

        a.resize(L), b.resize(L);
        dft(a), dft(b);
        for (int i = 0; i < L; i ++) {
            mul(a[i], b[i]);
        }
        idft(a);
        a.resize(tot);
        return a;
    }

    bool operator < (const poly &rhs) const {
        return size() > rhs.size();
    }
};

const int N = 100100;

int n, s, t;
std::vector<std::vector<int>> G;

int ans;
std::vector<int> fact, facv;

poly make(int r, int flag) {
    poly a(r + 1);
    for (int i = 0; i <= r; i ++) {
        a[i] = 1ll * fact[r] * facv[r - i] % mod;
        if (flag) {
            mul(a[i], i + 1);
        }
    }
    return a;
}

void solve(std::vector<poly> polys, int m) {
    std::priority_queue<poly> q;
    for (poly p : polys) {
        q.push(p);
    }

    while (q.size() > 1) {
        poly p1 = q.top(); q.pop();
        poly p2 = q.top(); q.pop();
        q.push(p1 * p2);
    }

    poly p = q.top();
    for (int i = 0; i < p.size(); i ++) {
        int cur = 1ll * p[i] * facv[i + m] % mod * fact[n] % mod;
        if (i & 1) neg(cur);
        add(ans, cur);
    }
}

int lst[N];
void dfs(int u, int fu) {
    lst[u] = fu;
    for (int v : G[u]) {
        if (v == fu) {
            continue;
        }
        dfs(v, u);
    }
}

int m, seq[N];

void work() {
    std::cin >> n >> s >> t;

    G.assign(n + 1, {});
    for (int i = 1; i < n; i ++) {
        int x, y;
        std::cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    ans = 0;
    fact.resize(n + 1), facv.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i ++) {
        fact[i] = 1ll * fact[i - 1] * i % mod;
    }
    facv[n] = qpow(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; i --) {
        facv[i] = 1ll * facv[i + 1] * (i + 1) % mod;
    }

    std::vector<int> deg(n + 1);
    for (int i = 1; i <= n; i ++) {
        deg[i] = G[i].size();
    }

    if (s == t) {
        if (n == 1) {
            std::cout << 1 << '\n';
            return;
        }

        int p = 0;
        for (int v : G[s]) {
            add(p, 1ll * fact[deg[s] - 1] * fact[deg[v]] % mod * facv[deg[s] + deg[v]] % mod);
        }
        ans = 1ll * fact[n] * p % mod;
        std::cout << ans << '\n';
        return;
    }

    dfs(s, 0);

    m = 0;
    for (int x = t;; x = lst[x]) {
        seq[++ m] = x;
        if (x == s) {
            break;
        }
    }
    std::reverse(seq + 1, seq + 1 + m);

    std::vector<poly> polys;
    polys.push_back(make(deg[s] - 1, 0));
    if (m == 2) {
        polys.push_back(make(deg[t], 0));
    } else {
        polys.push_back(make(deg[seq[2]] - 1, 0));
        for (int i = 3; i < m; i ++) {
            polys.push_back(make(deg[seq[i]] - 2, 0));
        }
        polys.push_back(make(deg[t] - 1, 0));
    }

    solve(polys, m - 1);

    if (G[s].size() > 1) {
        std::vector<poly> polys;
        int md = 0;
        for (int v : G[s]) {
            if (v == seq[2]) {
                continue;
            }
            chmax(md, deg[v] - 1);
        }
        poly adj(md + 1);
        for (int v : G[s]) {
            if (v == seq[2]) {
                continue;
            }
            poly cur = make(deg[v] - 1, 0);
            for (int i = 0; i < cur.size(); i ++) {
                add(adj[i], cur[i]);
            }
        }

        polys.push_back(adj);
        polys.push_back(make(deg[s] - 2, 1));
        for (int i = 2; i < m; i ++) {
            polys.push_back(make(deg[seq[i]] - 2, 0));
        }
        polys.push_back(make(deg[t] - 1, 0));

        solve(polys, m + 1);
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    while (T --) {
        work();
    }

    return 0;
}