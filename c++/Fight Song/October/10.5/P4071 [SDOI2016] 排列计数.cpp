#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int Mod = 1e9 + 7;

int T;
int n, m;
ll fac[N], inv_fac[N], D[N];

ll Pow(ll a, ll b) {
    ll sum = 1;
    while (b) {
        if (b & 1) sum = sum * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return sum;
}

void Init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % Mod;
    inv_fac[N - 1] = Pow(fac[N - 1], Mod - 2);
    for (int i = N - 2; i >= 0; i--) inv_fac[i] = inv_fac[i + 1] * (i + 1) % Mod;
    D[0] = 1; D[1] = 0;
    for (int i = 2; i < N; i++) D[i] = (i - 1) * (D[i - 1] + D[i - 2]) % Mod;
}

ll C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fac[n] * inv_fac[m] % Mod * inv_fac[n - m] % Mod;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Init();
    cin >> T;
    while (T--) {
        cin >> n >> m;
        if (m > n) { printf("0\n"); continue; }
        printf("%lld\n", C(n, m) * D[n - m] % Mod);
    }
    return 0;
}