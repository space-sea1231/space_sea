# include<bits/stdc++.h>
# define int long long
using namespace std;
const int N = 3e6 + 5 , mod = 998244353;
int n , a[N] , fac[N] , ans , q , cnt;
void solve () {
	int tar = 0 , ans = 1 , cnt = 0 , total = 0 , cnt2 = 0 , dy = 0 , xy = 0 , dyc = 0 , xyc = 0;
	cin >> n;
	n <<= 1;
	for (int i = 1;i <= n;++i) {
		cin >> a[i];
		if (!a[i]) continue;
		++total;
		if (a[i] > (n >> 1)) ++dy;
		else ++xy;
	}
	for (int i = 1;i <= n;i += 2) {
		int gs = (!a[i]) + (!a[i + 1]);
		if (gs == 2) ++ cnt;
		else if (gs == 1) ++ tar;
		else if (gs == 0) ++ cnt2;
	}
	int n2 = n >> 1;
	for (int i = 1;i <= cnt;++i) ans = (ans % mod * (2ll * cnt % mod - 2ll * i % mod + 2ll) % mod ) % mod;
	ans = (ans * fac[cnt]) % mod;
	for (int i = 1;i <= n;i += 2) {
		int gs = (!a[i]) + (!a[i + 1]);
		if (gs == 1) {
			int v = max(a[i] , a[i + 1]);
			if (v <= n2) ans = (ans % mod * max(1ll , (n2 % mod - dy % mod - dyc % mod) + mod) % mod) % mod , ++dyc;
			else  ans = (ans % mod * max(1ll , (n2 % mod - xy % mod - xyc % mod) + mod) % mod) % mod , ++xyc;
 		}
	}
	cout << (ans + mod) % mod << "\n";
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	freopen ("wo.in" , "r" , stdin);
	freopen ("wo.out" , "w" , stdout);
	int T;
	cin >> T;
	fac[0] = 1;
	for (int i = 1;i < N;++i) fac[i] = (i * fac[i - 1] % mod) % mod;
	while (T -- > 0) solve ();
	return 0;
}
/*
5
0 0 0 0 0 1 2 4 0 5
6
4
0 0 0 0 0 0 3 0
7
0 0 0 0 0 0 10 0 6 0 0 0 5 0
5
10 0 3 0 6 0 5 0 8 0
2
3 0 2 0
1
1 0
10
0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 20 0 0 0
*/

