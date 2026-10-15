#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 998244353;

ll n, m, l, r;

ll Pow(ll a, ll b) {
	a %= Mod;
	ll sum = 1;
	while (b) {
		if (b & 1) sum = sum * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return sum;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> l >> r;
	if ((n & 1) && (m & 1)) printf("%d\n", Pow(r - l + 1, n * m));
	else {
		ll e = (r >> 1) - (l - 1 >> 1);
		ll o = r - l + 1 - e;
		printf("%d\n", (Pow((o + e), n * m) + Pow(o - e + Mod, n * m)) % Mod * Pow(2, Mod - 2) % Mod);
	}
	return 0;
}