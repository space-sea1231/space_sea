#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int Mod = 19930726;

ll n, m;
string s;
int f[N];
ll cnt[N];

bool Cmp(int a, int b) {return a > b;}
int Pow(int a, int b) {
	int rev = 1;
	while (b) {
		if (b & 1) rev = ((ll)rev * a) % Mod;
		a = ((ll)a * a) % Mod;
		b >>= 1;
	}
	return rev;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> s;
	s = "$" + s + "@";
	int l = 0, r = -1;
	for (int i = 1; i <= n; i++) {
		int k = (i > r) ? 1 : min(f[l + r - i], r - i + 1);
		while (s[i - k] == s[i + k]) k++;
		cnt[k * 2 - 1]++; f[i] = k--;
		// printf("f[%d]=%d\n", i, f[i]);
		if (r < i + k) l = i - k, r = i + k;
	}
	int ans = 1;
	// Debug(n);
	for (int i = n; i >= 1; i--) {
		// printf("cnt[%d]=%d\n", i, cnt[i]);
		if (m < cnt[i]) {
			ans = ((ll)ans * Pow(i, m)) % Mod;
			m = 0; break;
		} else {
			ans = ((ll)ans * Pow(i, cnt[i])) % Mod;
			m -= cnt[i];
		}
		if (i >= 3) cnt[i - 2] += cnt[i];
	}
	if (m) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}