#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 100003;

ll n, m;
ll Pow(ll a, ll b) {
    a %= Mod;
    ll sum = 1;
    while (b) {
        if (b & 1) sum = (sum * a) % Mod;
        a = (a * a) % Mod;
        b >>= 1;
    }
    return sum;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> m >> n;
    printf("%lld\n", (Pow(m, n) - m % Mod * Pow(m - 1, n - 1) % Mod + Mod) % Mod);
    
    return 0;
}