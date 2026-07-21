#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G = 3;

inline int modpow(long long a, long long e) {
    int r = 1;
    a %= MOD;
    while (e) {
        if (e & 1) r = (long long)r * a % MOD;
        a = (long long)a * a % MOD;
        e >>= 1;
    }
    return r;
}

void ntt(vector<int>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = modpow(G, (MOD - 1) / len);
        if (invert) wlen = modpow(wlen, MOD - 2);
        int half = len >> 1;
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < half; ++j) {
                int u = a[i + j];
                int v = (int)(w * a[i + j + half] % MOD);
                int x = u + v; if (x >= MOD) x -= MOD;
                int y = u - v; if (y < 0) y += MOD;
                a[i + j] = x;
                a[i + j + half] = y;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        int inv_n = modpow(n, MOD - 2);
        for (int &x : a) x = (long long)x * inv_n % MOD;
    }
}

vector<int> convolution(const vector<int>& a, const vector<int>& b) {
    int need = (int)a.size() + (int)b.size() - 1;
    int n = 1;
    while (n < need) n <<= 1;
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; ++i) fa[i] = (long long)fa[i] * fb[i] % MOD;
    ntt(fa, true);
    fa.resize(need);
    return fa;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, w;
        long long m, k;
        cin >> n >> w >> m >> k;
        int M = 1 << w;
        int mask = M - 1;
        vector<int> A(n);
        vector<int> S(M, 0);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
            S[A[i] & mask]++;
        }
        vector<int> H(M);
        for (int i = 0; i < M; ++i) cin >> H[i];
        vector<int> H_hat(M);
        for (int i = 0; i < M; ++i) {
            H_hat[(M - i) & mask] = H[i];
        }
        ntt(S, false);
        ntt(H_hat, false);
        int K = (int)min(k, m);
        vector<int> fact(K + 1), invfact(K + 1);
        fact[0] = 1;
        for (int i = 1; i <= K; ++i) fact[i] = (long long)fact[i - 1] * i % MOD;
        invfact[K] = modpow(fact[K], MOD - 2);
        for (int i = K; i >= 1; --i) invfact[i - 1] = (long long)invfact[i] * i % MOD;
        vector<int> A_conv(K + 1), B_conv(K + 1);
        for (int i = 0; i <= K; ++i) {
            A_conv[i] = (long long)modpow(i, k) * invfact[i] % MOD;
            B_conv[i] = invfact[i];
            if (i & 1) B_conv[i] = (MOD - B_conv[i]) % MOD;
        }
        vector<int> stir = convolution(A_conv, B_conv);
        stir.resize(K + 1);
        vector<int> coeff(K + 1);
        long long fall = 1;
        for (int q = 0; q <= K; ++q) {
            if (q > 0) fall = fall * ((m - q + 1) % MOD) % MOD;
            coeff[q] = (long long)stir[q] * fall % MOD;
        }
        vector<int> W(M, 0);
        for (int r = 0; r < M; ++r) {
            int Sr = S[r];
            int Hr = H_hat[r];
            if (Hr == 0) continue;
            long long val = modpow(Sr, m - K);
            int cur_idx = (-(long long)r * K) & mask;
            for (int q = K; q >= 0; --q) {
                if (coeff[q]) {
                    long long add = (long long)Hr * coeff[q] % MOD * val % MOD;
                    int nv = W[cur_idx] + (int)add;
                    if (nv >= MOD) nv -= MOD;
                    W[cur_idx] = nv;
                }
                val = val * Sr % MOD;
                cur_idx = (cur_idx + r) & mask;
            }
        }
        ntt(W, true);
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << W[A[i] & mask];
        }
        cout << '\n';
    }
    return 0;
}
