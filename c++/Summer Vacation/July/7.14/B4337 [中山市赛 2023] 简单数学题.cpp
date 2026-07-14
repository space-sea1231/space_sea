#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 998244353;

int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = (sum * a) % Mod;
		a = (a * a) % Mod;
		b >>= 1;
	}
	return sum;
}
int n, a1, a2, b1, b2;
int p, q;
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> a1 >> a2 >> b1 >> b2;
	a1 %= Mod, a2 %= Mod, b1 %= Mod, b1 %= Mod;
	int A = (a1 + a2) % Mod;
	int B = (b1 + b2) % Mod;
	int T = (a1 + b1) % Mod;
	p = (A - 1) % Mod * B % Mod * Pow(A, Mod - 2) % Mod * Pow(B + 1, Mod - 2) % Mod;
	q = T % Mod * Pow(B + 1, Mod - 2) % Mod;
	int x = Pow(p, n) * a1 % Mod + q * (Pow(p, n) - 1 + Mod) % Mod * Pow(p - 1, Mod - 2) % Mod;
	printf("%lld\n", x * Pow(A, Mod - 2) % Mod);
	return 0;
}