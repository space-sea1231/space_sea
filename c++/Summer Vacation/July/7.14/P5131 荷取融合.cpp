#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 3e2 + 10;
const int Mod = 19260817;

int n, k;
int f[2][K], g[2][K];

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
	cin >> n >> k;
	bool flag;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		f[flag][0] = g[flag][0] = 1;
		for (int j = 1; j <= k; j++) {
			f[flag][j] = (f[!flag][j] + f[flag][j - 1]) % Mod;
			g[flag][j] = (g[!flag][j] + g[flag][j - 1] * a) % Mod;
		}
		flag = !flag;
	}
	printf("%lld\n", g[!flag][k] * Pow(f[!flag][k], Mod - 2) % Mod);
	return 0;
}