#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 7, mod = 998244353;
int t, n, m, cnt1, cnt2, ans, a[N], c[N];

inline int qpow(int x, int y = mod - 2, int z = 1) {
	if (!x) return 1;
	for (; y; x = x * x % mod, y >>= 1) if (y & 1) z = z * x % mod;
	return z;
}

signed main() {
	freopen("wo.in", "r", stdin);
	freopen("wo.out", "w", stdout);
	cin >> t;
	while (t--) {
		cin >> n, m = n + n, ans = 1;
		for (int i = 1; i <= m; ++i) cin >> a[i], c[i] = 0;
		for (int i = 1, p, q, x, y; i <= n; ++i) {
			x = a[p = i << 1], y = a[q = i - 1 << 1 | 1];
			if (x && y) {
				swap(a[p], a[n << 1]), swap(a[q], a[n - 1 << 1 | 1]);
				++c[x], ++c[y], --n, --i;
			}
		}
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		m = n + n, cnt1 = cnt2 = n;
		for (int i = 1; i <= m; ++i) a[i] -= c[a[i]];
		for (int i = 1; i <= m; ++i) if (a[i]) {
			if (a[i] <= n) --cnt1;
			else --cnt2;
		}
		for (int i = 1, x, y; i <= n; ++i) {
			x = a[i << 1], y = a[i - 1 << 1 | 1];
			if (x || y) {
				if (x <= n && !y || !x && y <= n) ans = ans * cnt2 % mod, --cnt2;
				if (x >  n && !y || !x && y >  n) ans = ans * cnt1 % mod, --cnt1;
			} else ans = ans * (cnt1 * cnt2 * 2 % mod) % mod, --cnt1, --cnt2;
		}
		cout << ans << '\n';
	}
	return 0;
}