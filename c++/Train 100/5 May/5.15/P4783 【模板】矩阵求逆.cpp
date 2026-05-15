#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int N = 4e2 + 10;
const int Mod = 1e9 + 7;

int n;
int a[N][N << 1];

int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = sum * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return sum;
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
		a[i][i + n] = 1;
	}
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= n * 2; j++) {
	// 		printf("%d ", a[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	for (int i = 1; i <= n; i++) {
		int cur = i;
		for (int j = i + 1; j <= n; j++) {
			if (a[cur][i] < a[j][i]) cur = j;
		}
		if (!a[cur][i]) {
			printf("No Solution\n");
			return 0;
		}
		swap(a[i], a[cur]);
		int div = Pow(a[i][i], Mod - 2);
		for (int j = 1; j <= n; j++) {
			if (j == i) continue;
			int p = a[j][i] * div % Mod;
			for (int k = i; k <= (n << 1); k++) {
				a[j][k] = ((a[j][k] - a[i][k] * p) % Mod + Mod) % Mod;
			}
		}
		for (int j = 1; j <= (n << 1); j++) a[i][j] = a[i][j] * div % Mod;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = n + 1; j <= (n << 1); j++) {
			printf("%lld ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}