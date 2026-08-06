#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

static const int64 MOD = 1000000007LL;

int64 mod_pow(int64 a, long long e) {
    int64 r = 1;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

pair<int64, int64> pow_sum(int64 a, long long n) {
    if (n == 0) return {1, 0};

    auto [p, s] = pow_sum(a, n >> 1);
    int64 p2 = p * p % MOD;
    int64 s2 = s * ((p + 1) % MOD) % MOD;

    if ((n & 1) == 0) {
        return {p2, s2};
    } else {
        return {p2 * a % MOD, (s2 + p2) % MOD};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long n, c;
        int m;
        cin >> n >> m >> c;

        vector<long long> w(m + 1);

        // sufW[i] = sum_{v=i}^m w_v
        // sufV[i] = sum_{v=i}^m v*w_v
        vector<i128> sufW(m + 2, 0), sufV(m + 2, 0);

        for (int i = 1; i <= m; ++i) {
            cin >> w[i];
        }

        for (int i = m; i >= 1; --i) {
            sufW[i] = sufW[i + 1] + w[i];
            sufV[i] = sufV[i + 1] + (i128)i * w[i];
        }

        i128 totalW = sufW[1];
        i128 target = (i128)c * totalW;

        /*
          A(x) = E[(Y-x)^+]
               = [sum_{v>x} (v-x) w_v] / W
        */
        int K = -1;
        for (int x = 0; x < m; ++x) {
            i128 improve = sufV[x + 1] - (i128)x * sufW[x + 1];
            if (improve > target) K = x;
        }

        if (K == -1) {
            cout << 0 << '\n';
            continue;
        }

        int64 Wmod = (int64)(totalW % MOD);
        int64 invW = mod_pow(Wmod, MOD - 2);

        /*
          q = P(Y <= K)
          h = E[Y * [Y>K]]
        */
        int64 prefix = 0;
        int64 lowPowSum = 0;

        for (int x = 1; x <= K; ++x) {
            prefix = (prefix + w[x]) % MOD;

            if (x < K) {
                int64 fx = prefix * invW % MOD;
                lowPowSum += mod_pow(fx, n);
                if (lowPowSum >= MOD) lowPowSum -= MOD;
            }
        }

        int64 q = prefix * invW % MOD;
        int64 h = (int64)(sufV[K + 1] % MOD) * invW % MOD;

        auto [qn, geometricSum] = pow_sum(q, n);
        // geometricSum = 1 + q + ... + q^(n-1)

        /*

          E[max ; all <=K]
            = K * F(K)^n - sum_{x=0}^{K-1} F(x)^n
        */
        int64 terminalLow = ((int64)K * qn % MOD - lowPowSum + MOD) % MOD;

        int64 perAttempt = (h - c % MOD + MOD) % MOD;
        int64 ans = (perAttempt * geometricSum + terminalLow) % MOD;

        cout << ans << '\n';
    }

    return 0;
}