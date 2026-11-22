#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;
const int Mod = 1e9 + 7;

int T;
int n;
int a[N];

int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = (ll)sum * a % Mod;
		a = (ll)a * a % Mod;
		b >>= 1;
	}
	return sum;
}
void Solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, [&](int a, int b) {
		return a > b;
	});
	int pos = n;
	for (int i = 1; i < n; i++) {
		if (a[i] == a[i + 1]) {
			pos = i - 1;
			break;
		}
	}
	int ans = 1;
	for (int i = 1; i <= pos; i++) {
		ans = ((ll)ans + Pow(a[i] - 1, i)) % Mod;
	}
	printf("%d\n", pos == 0 ? 1 : ans);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) Solve();
	return 0;
}