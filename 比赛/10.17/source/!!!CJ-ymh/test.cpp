#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
bool vis[2000005];
int t, n, cnt, tot, tot2, a[2000005], fac[2000005], inv[2000005];
int fpow(int x, int y) {
	int s = 1;
	while(y) {
		if(y & 1)
			s = 1ll * s * x % mod;
		x = 1ll * x * x % mod, y >>= 1;
	}
	return s;
}
int c(int n, int m) {
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
bool check(int x) {
	int s1 = 0, s2 = 0;
	for(int i = 1; i <= x; i++)
		if(!vis[i])
			s1++;
	for(int i = x + 1; i <= (n << 1); i++)
		if(!vis[i])
			s2++;
	for(int i = 1; i <= n; i++) {
		if(a[(i << 1) - 1] && a[i << 1])
			continue;
		if(a[i << 1])
			if(a[i << 1] > x)
				s1--;
			else
				s2--;
		else if(a[(i << 1) - 1])
			if(a[(i << 1) - 1] > x)
				s1--;
			else
				s2--;
		else
			s1--, s2--;
	}
	return s1 >= 0;
}
int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t, fac[0] = 1;
	for(int i = 1; i < 2000001; i++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[2000000] = fpow(fac[2000000], mod - 2);
	for(int i = 1999999; ~i; i--)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
	while(t--) {
		cin >> n, cnt = tot = tot2 = 0, fill(vis + 1, vis + (n << 1) + 1, 0);
		for(int i = 1; i <= (n << 1); i++)
			cin >> a[i], vis[a[i]] = 1;
		for(int i = 1; i <= n; i++)
			cnt += !a[(i << 1) - 1] && !a[i << 1];
		int l = 0, r = n << 1 | 1;
		while(l + 1 < r) {
			int mid = l + r >> 1;
			if(check(mid))
				r = mid;
			else
				l = mid;
		}
		for(int i = 1; i <= r; i++)
			if(!vis[i])
				tot++;
		for(int i = r + 1; i <= (n << 1); i++)
			if(!vis[i])
				tot2++;
		cout << 1ll * fac[tot] * fac[tot2] % mod * fpow(2, cnt) % mod << '\n';
	}
	return 0;
}