#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 998244353;
const int g = 3;
const int N = 400005;

int fac[N], ifac[N];

int qpow(int a, int b) {
    int r = 1;
    a %= mod;
    while (b) {
        if (b & 1) r = 1LL * r * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return r;
}

int inv(int x) {
    return qpow(x, mod - 2);
}

void init() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = 1LL * fac[i - 1] * i % mod;
    ifac[N - 1] = inv(fac[N - 1]);
    for (int i = N - 2; i >= 1; --i) {
        ifac[i] = 1LL * ifac[i + 1] * (i + 1) % mod;
    }
}

vector<int> rv;

void init_rv(int n) {
    rv.resize(n);
    for (int i = 0; i < n; ++i) {
        rv[i] = (rv[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
}

void ntt(vector<int>& a, int n, int tp) {
    for (int i = 0; i < n; ++i) {
        if (i < rv[i]) swap(a[i], a[rv[i]]);
    }
    for (int m = 1; m < n; m <<= 1) {
        int wn = qpow(g, (mod - 1) / (m << 1));
        if (tp == -1) wn = inv(wn);
        for (int j = 0; j < n; j += m << 1) {
            int w = 1;
            for (int k = 0; k < m; ++k) {
                int x = a[j + k];
                int y = 1LL * w * a[j + k + m] % mod;
                a[j + k] = (x + y) % mod;
                a[j + k + m] = (x - y + mod) % mod;
                w = 1LL * w * wn % mod;
            }
        }
    }
    if (tp == -1) {
        int iv = inv(n);
        for (int& x : a) x = 1LL * x * iv % mod;
    }
}

vector<int> mul(vector<int> a, vector<int> b, int d = -1) {
    if (a.empty() || b.empty()) return {};
    int n = a.size(), m = b.size(), z = 1;
    while (z < n + m - 1) z <<= 1;
    a.resize(z);
    b.resize(z);
    init_rv(z);
    ntt(a, z, 1);
    ntt(b, z, 1);
    for (int i = 0; i < z; ++i) a[i] = 1LL * a[i] * b[i] % mod;
    ntt(a, z, -1);
    a.resize(d == -1 ? n + m - 1 : d);
    return a;
}

vector<int> pinv(const vector<int>& a, int d) {
    if (d == 1) return {inv(a[0])};
    vector<int> b = pinv(a, (d + 1) >> 1);
    int z = 1;
    while (z < d * 2) z <<= 1;
    vector<int> t(a.begin(), a.begin() + min((int)a.size(), d));
    t.resize(z);
    b.resize(z);
    init_rv(z);
    ntt(t, z, 1);
    ntt(b, z, 1);
    for (int i = 0; i < z; ++i) {
        b[i] = 1LL * b[i] * (2 - 1LL * t[i] * b[i] % mod + mod) % mod;
    }
    ntt(b, z, -1);
    b.resize(d);
    return b;
}

vector<int> der(const vector<int>& a) {
    int n = a.size();
    if (n <= 1) return {0};
    vector<int> b(n - 1);
    for (int i = 1; i < n; ++i) b[i - 1] = 1LL * a[i] * i % mod;
    return b;
}

vector<int> inte(const vector<int>& a) {
    int n = a.size();
    vector<int> b(n + 1);
    for (int i = 0; i < n; ++i) b[i + 1] = 1LL * a[i] * inv(i + 1) % mod;
    return b;
}

vector<int> ln(const vector<int>& a, int d) {
    vector<int> b = inte(mul(der(a), pinv(a, d), d - 1));
    b.resize(d);
    return b;
}

vector<int> ex(const vector<int>& a, int d) {
    if (d == 1) return {1};
    vector<int> b = ex(a, (d + 1) >> 1);
    b.resize(d);
    vector<int> c = ln(b, d), t(d);
    t[0] = 1;
    for (int i = 0; i < d; ++i) {
        t[i] = (t[i] - c[i] + (i < (int)a.size() ? a[i] : 0) + mod) % mod;
    }
    return mul(b, t, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    int T;
    cin >> T;
    while (T--) {
        int n, a, b, c;
        ll m;
        cin >> n >> m >> a >> b >> c;

        int ia = inv(a);
        int i2a = inv(2LL * a % mod);
        int B = 1LL * b * i2a % mod;
        int C = (1LL * c * ia % mod - 1LL * B * B % mod + mod) % mod;

        int z = 2 * n + 1;
        vector<int> num(z), den(z);
        int x = (m % mod + B + 1) % mod;
        for (int r = 0; r <= 2 * n; ++r) {
            int u = (qpow(x, r + 1) - qpow(B, r + 1) + mod) % mod;
            num[r] = 1LL * u * ifac[r + 1] % mod;
            den[r] = ifac[r + 1];
        }

        vector<int> e = mul(num, pinv(den, z), z);
        vector<int> u(z);
        for (int r = 0; r <= 2 * n; ++r) u[r] = 1LL * e[r] * fac[r] % mod;

        vector<int> a1(n + 1), a2(n + 1);
        for (int k = 0; k <= n; ++k) {
            a1[k] = 1LL * u[2 * k] * ifac[k] % mod;
            a2[k] = 1LL * qpow(C, k) * ifac[k] % mod;
        }

        vector<int> sp = mul(a1, a2, n + 1), s(n + 1), l(n + 1);
        for (int i = 1; i <= n; ++i) {
            s[i] = 1LL * qpow(a, i) * sp[i] % mod * fac[i] % mod;
            l[i] = 1LL * s[i] * inv(i) % mod;
        }

        vector<int> f = ex(l, n + 1);
        for (int i = 0; i <= n; ++i) cout << f[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}
