# include<bits/stdc++.h>
# define int long long
using namespace std;
const int N = 4e5 + 5 , mod = 4294967296 , inv = 1;
int n , a[N];
int ksm (int a , int b) {
	__int128 ans = 1ll;
	while (b) {
		if (b & 1) ans = __int128(ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return (int)(ans % mod);
}
int calc () {
	int sum = n;
	for (int i = 1;i <= n;) {
		int j = i + 1;
		while (1) {
			if (a[j] <= a[j - 1]) break;
			++j;
		}
		--j;
		sum += (j - i + 2ll) * (j - i + 1ll) / 2ll - (j - i + 1ll); 
		i = j + 1;
	}
	return sum % mod;
}
void solve () {
	int ans = 0;
	cin >> n;
	memset (a , 0 , sizeof a);
	for (int i = 1;i <= n;++i) cin >> a[i];
	ans = calc();
	for (int x = 1; x <= n ;++ x) {
		for (int y = x + 1; y <= n;++y) {
			swap (a[x] , a[y]) ;
			ans = max(calc() , ans);
			swap (a[x] , a[y]);
		}
	}
	cout << ans << "\n";
}
signed main() {
	freopen ("wei.in" , "r" , stdin);
	freopen ("wei.out" , "w" , stdout);
	int T;
	cin >> T;
	while (T-->0) solve();
	return 0;
}

