#include <bits/stdc++.h>
#define int long long
const long long mod = 998442353;
using namespace std;
int t, n, m, dy[200005], dx[2000005], p[18][18], dp[(1 << 18)][18], g[(1 << 18)][18], s, dis[18][18], c[18][18];

int qpow(int a, int b, int p){
	int res = 1;
	while(b){
		if(b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}

signed main(){
	freopen("ge.in", "r", stdin);
	freopen("ge.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	dx[0] = dy[0] = 1;
	for( int i = 1; i <= 200000; i++ ){
		dx[i] = dx[i - 1] * i % mod;
		dy[i] = qpow(dx[i], mod - 2, mod) % mod;
	}
	for( int i = 200001; i <= 2000000; i++ ) dx[i] = dx[i - 1] * i % mod;
	cin >> t;
	while(t--){
		int ans1 = 1e18, ans2 = 0;
		cin >> m >> n;
		for( int i = 0; i < n; i++ ){
			for( int j = 1; j <= m; j++ ){
				cin >> p[i][j];
			}
		}
		for( int i = 0; i < n; i++ ){
			for( int j = 0; j < n; j++ ){
				dis[i][j] = 0;
				for( int k = 1; k <= m; k++ ){
					dis[i][j] += abs(p[i][k] - p[j][k]);
				}
				c[i][j] = dx[dis[i][j]];
				for( int k = 1; k <= m; k++ ){
					c[i][j] = c[i][j] * dy[abs(p[i][k] - p[j][k])] % mod;
				}
			}
		}
		for( int i = 0; i < (1 << n); i++ ){
			for( int j = 0; j < n; j++ ){
				g[i][j] = 0;
				dp[i][j] = 1e16;
			}
		}
		for( int i = 0; i < n; i++ ){
			cin >> s;
			if(s){
				g[(1 << i)][i] = 1;
				dp[(1 << i)][i] = 0;
			}
		}
		for( int i = 0; i < (1 << n); i++ ){
			for( int j = 0; j < n; j++ ){
				if(!((i >> j) & 1)) continue;
				for( int k = 0; k < n; k++ ){
					if(!(((i ^ (1 << j)) >> k) & 1)) continue;
					if(dp[i][j] > dp[i ^ (1 << j)][k] + dis[j][k]){
						dp[i][j] = dp[i ^ (1 << j)][k] + dis[j][k];
						g[i][j] = g[i ^ (1 << j)][k] * c[j][k] % mod;
					}
					else if(dp[i][j] == dp[i ^ (1 << j)][k] + dis[j][k]) g[i][j] = (g[i][j] + g[i ^ (1 << j)][k] * c[j][k] % mod) % mod;
				}
			}
		}
		for( int i = 0; i < n; i++ ){
			if(dp[(1 << n) - 1][i] < ans1){
				ans1 = dp[(1 << n) - 1][i];
				ans2 = g[(1 << n) - 1][i];
			}
			else if(dp[(1 << n) - 1][i] == ans1) ans2 = (ans2 + g[(1 << n) - 1][i]) % mod;
		}
		if(ans1 > 1e9) cout << "NIE" << endl;
		else cout << ans1 << ' ' << ans2 << endl;
	}
	return 0;
}
