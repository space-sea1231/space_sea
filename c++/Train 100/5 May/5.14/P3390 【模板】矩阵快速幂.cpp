#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;
const int Mod = 1e9 + 7;

ll n, k;
ll a[N][N];
ll sum[N][N];
ll tmp[N][N];

void Mul(ll a[][N], ll b[][N]) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			tmp[i][j] = 0;
			for (int k = 1; k <= n; k++) {
				tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j] % Mod) % Mod;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = tmp[i][j];
		}
	}
}

void Pow(ll k) {
	while (k) {
		if (k & 1) Mul(sum, a);
		Mul(a, a);
		k >>= 1;
	}
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
		sum[i][i] = 1;
	}
	Pow(k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%lld ", sum[i][j]);
		}
		printf("\n");
	}
	return 0;
}