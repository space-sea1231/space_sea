#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e3 + 10;
const int Mod = 998244353;

int n, m;
int x[N], y[N];

int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = (sum * a) % Mod;
		a = (a * a) % Mod;
		b >>= 1;
	}
	return sum;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int tmp = y[i];
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			tmp = tmp * (m - x[j]) % Mod * Pow(x[i] - x[j], Mod - 2) % Mod;
		}
		ans = (ans + tmp) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}