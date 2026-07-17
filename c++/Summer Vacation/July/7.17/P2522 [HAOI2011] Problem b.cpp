#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e4 + 10;

int t;
int a, b, c, d, k;
int tot;
int prime[N];
int cnt[N];
int mu[N];
bool vis[N];

int read() {
	char c = getchar();
	int flag = 1;
	while (c < '0' || c > '9') {
		if (c == '-') flag = -1;
		c = getchar();
	}
	int rev = 0;
	while ('0' <= c && c <= '9') {
		rev = (rev << 3) + (rev << 1) + (c ^ 48);
		c = getchar();
	}
	return rev;
}

void Prime() {
	mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!vis[i]) {
			mu[i] = -1;
			prime[++tot] = i;
		}
		for (int j = 1; j <= tot && i * prime[j] < N; j++) {
			vis[i * prime[j]] = true;
			if (i % prime[j]) mu[i * prime[j]] = -mu[i];
			else break;
		}
	}
	for (int i = 1; i < N; i++) mu[i] += mu[i - 1];
}
ll F(int a, int b) {
	ll ans = 0;
	for (int l = 1, r, lim = min(a, b) / k; l <= lim; l = r + 1) {
		r = min(a / (a / l), b / (b / l));
		ans += ((ll)a / ((ll)l * k)) * ((ll)b / ((ll)l * k)) * (mu[r] - mu[l - 1]);
	}
	return ans;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	Prime();
	// cin >> t;
	t = read();
	while (t--) {
		// cin >> a >> b >> c >> d >> k;
		a = read(), b = read(), c = read(), d = read(), k = read();
		// printf("Debug: F(%d,%d)=%d F(%d,%d)=%d F(%d,%d)=%d F(%d,%d)=%d\n", b, d, F(b, d), a - 1, d, F(a - 1, d), b, c - 1, F(b, c - 1), a - 1, c - 1, F(a - 1, c - 1));
		printf("%lld\n", F(b, d) - F(a - 1, d) - F(b, c - 1) + F(a - 1, c - 1));
	}
	return 0;
}