#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Add(x, y) x = ((ll)x + y) % Mod
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const int Mod = 1e9 + 7;

int T;
int n, m;
int f[N][N][2];

int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = (ll)sum * a % Mod;
		a = (ll)a * a % Mod;
		b >>= 1;
	}
	return sum;
}
int Gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}
int Lcm(int a, int b) {
	return a / Gcd(a, b) * b;
}
void Solve(int cur) {
	cin >> n >> m;
	int ans = 0;
	for (int i = 0; i < m; i++) {
		for (int k = 1, lim = Gcd(m, Gcd(i, 12)); k <= lim; k++) {
			if (lim % k) continue;
			Add(ans, (ll)f[n][k][1] + f[n][k][0]);
			// cerr << i << " " << k << " " << f[n][k][1] + f[n][k][0] << "\n";
		}
	}
	printf("Case #%d: %d\n", cur, (ll)ans * Pow(m, Mod - 2) % Mod);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	f[0][1][0] = f[0][1][1] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= 12; j++) {
			if (12 % j) continue;
			// if (i + 2 < N) f[i + 2][j][0] = ((ll)f[i + 2][j][0] + f[i][j][1]) % Mod;
			if (i + 2 < N) Add(f[i + 2][j][0], f[i][j][1]);
			if (i + 1 < N) Add(f[i + 1][j][1], f[i][j][0]);
			if (i + 2 < N) Add(f[i + 2][Lcm(j, 6)][1], 6LL * f[i][j][0]);
			if (i + 2 < N) Add(f[i + 2][Lcm(j, 3)][1], 3LL * f[i][j][0]);
			if (i + 3 < N) Add(f[i + 3][Lcm(j, 4)][1], 4LL * f[i][j][0]);
		}
	}
	cin >> T;
	for (int _ = 1; _ <= T; _++) Solve(_);

	return 0;
}
/*
Trees sleep deeply and dream of green again.
树沉睡着，梦见重回绿色
*/