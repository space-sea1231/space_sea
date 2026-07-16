#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 20100403;

int n, m;

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
	int ans = 1, div = 1;
	for (int i = n + 1; i <= n + m; i++) ans = ans * i % Mod;
	for (int i = 1; i <= m; i++) div = div * i % Mod;
	ans = ans * Pow(div, Mod - 2) % Mod;
	ans = ans * (n - m + 1) % Mod * Pow(n + 1, Mod - 2) % Mod;
	printf("%lld\n", ans);
	return 0;
}