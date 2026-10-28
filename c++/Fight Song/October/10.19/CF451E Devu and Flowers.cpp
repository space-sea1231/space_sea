#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 21;
const int Mod = 1e9 + 7;

int n;
ll s;
int inv[N];
ll f[N];

int C(ll n, int m) {
    if (n < m || m < 0) return 0;
    int rev = 1;
    for (int i = 1; i <= m; i++) {
        rev = (ll)rev * ((n - i + 1) % Mod) % Mod;
        rev = (ll)rev * inv[i] % Mod;
    }
    // printf("C(%d,%d)=%d\n", n, m, rev);
    return rev;
}
int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1; 
    }
    return sum;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> s;
    int ans = 0;
    for (int i = 1; i <= n; i++) inv[i] = Pow(i, Mod - 2); 
    for (int i = 1; i <= n; i++) cin >> f[i];
    for (int i = 0; i < (1 << n); i++) {
        ll sum = 0;
        int fg = 1;
        for (int j = 1; j <= n; j++) {
            if ((i >> j - 1) & 1) {
                sum += f[j] + 1;
                fg = -fg;
            }
        }
        ans = (ans + (ll)fg * C(s - sum + n - 1, n - 1) % Mod + Mod) % Mod;
    }
    printf("%d\n", ans);
    return 0;
}