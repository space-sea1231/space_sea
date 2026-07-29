#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        long long w, l;
        scanf("%lld%lld", &w, &l);
        long long ans = (qpow(w, l) + l - 1 + MOD) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
