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

    constexpr friend poly operator + (poly a, poly b) {
        poly c(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i ++) {
            add(c[i], a[i]);
        }
        for (int i = 0; i < b.size(); i ++) {
            add(c[i], b[i]);
        }
        return c;
    }
};

const int N = 100100;

int n;

std::string str;
int a[N];

struct trans {
    poly a00, a01, a10, a11;

    trans() {}
    trans operator * (trans rhs) const {
        trans net;
        net.a00 = a00 * rhs.a00 + a01 * rhs.a10;
        net.a01 = a00 * rhs.a01 + a01 * rhs.a11;
        net.a10 = a10 * rhs.a00 + a11 * rhs.a10;
        net.a11 = a10 * rhs.a01 + a11 * rhs.a11;
        return net;
    }
};

trans get(int i) {
    trans cur;
    cur.a00 = poly{10, a[i]};
    cur.a01 = poly{0, 1};
    cur.a10 = poly{a[i]};
    cur.a11 = poly{1};
    return cur;
};
trans solve(int l, int r) {
    if (l == r) {
        return get(l);
    }
    int mid = (l + r) >> 1;
    return solve(l, mid) * solve(mid + 1, r);
}

void work() {
    std::cin >> n;

    std::cin >> str;
    for (int i = 1; i <= n; i ++) {
        a[i] = str[i - 1] - '0';
    }

    if (n == 1) {
        std::cout << a[1] << '\n';
        return;
    }

    trans res = solve(2, n);
    for (int k = 0; k < n; k ++) {
        int t00 = k < res.a00.size() ? res.a00[k] : 0;
        int t10 = k < res.a10.size() ? res.a10[k] : 0;
        int v = (1ll * a[1] * t00 + t10) % mod;
        std::cout << v << ' ';
    }
    std::cout << '\n';
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