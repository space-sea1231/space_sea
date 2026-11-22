#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e7 + 10;
const int Mod = 998244353;

int T;
int n, m, k;
int pw[N], inv[N];

int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = (ll)sum * a % Mod;
		a = (ll)a * a % Mod;
		b >>= 1;
	}
	return sum;
}
int C(int n, int m) {
	// cerr << n << " " << m << "\n";
	if (n < 0 || m < 0 || n - m < 0) return 0;
	return (ll)pw[n] * inv[n - m] % Mod * inv[m] % Mod;
}

void Solve() {
	cin >> n >> m >> k;
	// if (min(n, m) * 2 - (n == m) < k) {
		// printf("0\n");
		// return ;
	// }
	// if (n == 1 || m == 1) {
		// printf("%d\n", k == (n & m));
		// return ;
	// }
	int ans0 = (ll)C(n - 1, k / 2) * C(m - 1, (k - 1) / 2) % Mod;
	int ans1 = (ll)C(m - 1, k / 2) * C(n - 1, (k - 1) / 2) % Mod;
	printf("%d\n", ((ll)ans0 + ans1) % Mod);
	// if (Ans ^ (((ll)ans0 + ans1) % Mod)) {
	// 	printf("Wrong Answer on (%d %d %d)\nOut:%d\nAns:%d\n", n, m, k, ((ll)ans0 + ans1) % Mod, Ans);
	// 	exit(0);
	// }
}
signed main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	pw[0] = 1;
	for (int i = 1; i < N; i++) pw[i] = (ll)pw[i - 1] * i % Mod;
	inv[N - 1] = Pow(pw[N - 1], Mod - 2);
	for (int i = N - 2; ~i; i--) inv[i] = (ll)inv[i + 1] * (i + 1) % Mod;
	
	cin >> T;
	while (T--) Solve();
	return 0;
}