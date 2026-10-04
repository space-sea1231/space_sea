#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
typedef __int128_t i128;

const int N = 5e5 + 10;
const int Mod = 1e9 + 7;

int n;
ll l[N], r[N];

signed main() {
    freopen("street.in", "r", stdin);
    freopen("street.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];

    ll ans = (i128)r[1] % Mod * (r[1] - l[1] + 1) % Mod;
    i128 sum = 2 * (i128)r[1] - l[1];

    for (int i = 2; i <= n; i++) {
        ll m = r[i] - l[i] + 1;
        if (sum + 1 >= (i128)l[i]) {   
            ans = (ans + ((i128)r[i] - l[i] + 2 + sum) % Mod * m % Mod) % Mod;
            sum = sum + 2 * (i128)m;
        } else {                     
            sum = 2 * (i128)r[i] - l[i];
            ans = (ans + (i128)r[i] % Mod * m % Mod) % Mod;
        }
    }
    printf("%lld\n", ans);
    return 0;
}