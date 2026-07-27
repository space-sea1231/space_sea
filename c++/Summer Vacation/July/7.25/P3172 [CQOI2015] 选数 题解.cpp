#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 1e9 + 7;
const int N = 1e5 + 10;

int n, k, l, r;
int f[N];

int Pow(ll a, int b) {
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
	cin >> n >> k >> l >> r;
	l = ceil((double)l / k), r = floor((double)r / k);
	for (int i = 1; i <= r - l + 1; i++) {
		int tl = ceil((double)l / i), tr = floor((double)r / i);
		f[i] = (Pow(tr - tl + 1, n) - (tr - tl + 1) + Mod) % Mod;
	}
	for (int i = r - l + 1; i >= 1; i--) {
		for (int j = i * 2; j <= r - l + 1; j += i) {
			f[i] = (f[i] - f[j] + Mod) % Mod;
		}
	}
	if (l == 1) f[1]++;
	printf("%d\n", f[1] % Mod);
	return 0;
}