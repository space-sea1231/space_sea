#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;
const int Mod = 1e9 + 7;

int t, n;
int p[N], q[N];
int a[N], b[N];

int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (sum * a) % Mod;
        a = (a * a) % Mod;
        b >>=1 ; 
    }
    return sum;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    p[0] = 1;
    for (int i = 1; i < N; i++) p[i] = (i * p[i - 1]) % Mod;
    q[N - 1] = Pow(p[N - 1], Mod - 2);
    for (int i = N - 2; i >= 1; i--) q[i] = (q[i + 1] * (i + 1)) % Mod;
    while (t--) {
        cin >> n;
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            cin >> a[i] >> b[i];
            if (a[i] == 0) {ans = (ans * (b[i] + 1)) % Mod; continue;}
            if (b[i] == 0) {ans = (ans * (a[i] + 1)) % Mod; continue;}
            // ans = (ans + ((p[a[i] + b[i]] * q[a[i]] % Mod) * q[b[i]]) % Mod) % Mod;
            // ans = (ans + ((p[a[i] + b[i]] * Pow(p[a[i]], Mod - 2) % Mod) * Pow(p[b[i]], Mod - 2)) % Mod) % Mod;
            ans = (ans * ((p[a[i] + b[i] + 2] / p[a[i] + 1]) % Mod / p[b[i] + 1]) % Mod) % Mod;
            // cerr<<p[a+b]<<" " <<p[a] << " " << p[b] << endl;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
/*
long long ans = (C(n + m + 2, n + 1) - n - m - 2) % MOD;
if (ans < 0) ans += MOD;

const int MOD = 1e9 + 7;

long long mod_pow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long comb(int n, int m) {
    if (m < 0 || m > n) return 0;
    
    // 预处理阶乘
    vector<long long> fact(n + 1), inv_fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    
    inv_fact[n] = mod_pow(fact[n], MOD - 2);  // 费马小定理求逆元
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i+1] * (i + 1) % MOD;
    }
    
    return fact[n] * inv_fact[m] % MOD * inv_fact[n-m] % MOD;
}

// 调用：comb(m+n, m)
*/