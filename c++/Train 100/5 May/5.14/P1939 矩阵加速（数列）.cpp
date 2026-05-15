#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 4;
const int Mod = 1e9 + 7;

ll a[N][N];
ll f[N][N];
ll tmp[N][N];

void Mul(ll a[][N], ll b[][N]) {
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			tmp[i][j] = 0;
			for (int k = 1; k <= 3; k++) {
				tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j] % Mod) % Mod;
			}
		}
	}
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			a[i][j] = tmp[i][j];
		}
	}
}

void Pow(ll k) {
	while (k) {
		if (k & 1) Mul(f, a);
		Mul(a, a);
		k >>= 1;
	}
}

int T, n;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		memset(a, 0, sizeof(a));
		memset(f, 0, sizeof(f));
		a[1][1] = a[1][3] = a[2][1] = a[3][2] = 1;
		f[1][1] = f[2][2] = f[3][3] = 1;
		cin >> n;
		Pow(n - 1);
		printf("%lld\n", f[1][1]);
	}
	return 0;
}