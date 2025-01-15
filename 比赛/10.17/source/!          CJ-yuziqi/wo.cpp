#include <bits/stdc++.h>
#define int long long
const long long p = 998244353;
using namespace std;
int t, n, a[2000005], dx[2000005], d2[2000005], ans, maxn, dis[10];
bool vis[10];

int qpow(int a, int b, int p){
	int res = 1;
	while(b){
		if(b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}
void dfs(int x, int s){
	if(x > 2 * n){
		if(s > maxn) ans = 1;
		else if(s == maxn) ans++;
		maxn = max(maxn, s);
		return;
	} 
	if(a[x]){
		dis[x] = a[x];
		dfs(x + 1, s + ((!(x & 1)) ? abs(dis[x] - dis[x - 1]) : 0));
		return;
	}
	for( int i = 1; i <= 2 * n; i++ ){
		if(vis[i]) continue;
		vis[i] = 1;
		dis[x] = i;
		dfs(x + 1, s + ((!(x & 1)) ? abs(dis[x] - dis[x - 1]) : 0));
		vis[i] = 0;
	}
	return;
}

signed main(){
	freopen("wo.in", "r", stdin);
	freopen("wo.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	dx[0] = d2[0] = 1;
	for( int i = 1; i <= 2000000; i++ ){
		dx[i] = dx[i - 1] * i % p;
		d2[i] = d2[i - 1] * 2 % p;
	}
	cin >> t;
	while(t--){
		cin >> n;
		for( int i = 1; i <= n; i++ ) cin >> a[2 * i - 1] >> a[2 * i];
		if(n <= 4){
			memset(vis, 0, sizeof(vis));
			for( int i = 1; i <= 2 * n; i++ ) vis[a[i]] = 1;
			ans = maxn = 0;
			dfs(1, 0);
			cout << ans << '\n';
			continue;
		}
		int cnt = 0, sum1 = n, sum2 = n;
		ans = 1;
		for( int i = 1; i <= n; i++ ){
			if(a[2 * i - 1] <= n && a[2 * i - 1]) sum1--;
			if(a[2 * i - 1] > n) sum2--;
			if(a[2 * i] <= n && a[2 * i]) sum1--;
			if(a[2 * i] > n) sum2--;
			if(!a[2 * i - 1] && !a[2 * i]) cnt++;
		}
		for( int i = 1; i <= n; i++ ){
			if(a[2 * i]) swap(a[2 * i - 1], a[2 * i]);
			if(!a[2 * i]){
				if(a[2 * i - 1] > n){
					if(sum1){
						ans = (ans * sum1) % p;
						sum1--;
					}
					else sum2--;
				}
				else if(a[2 * i - 1]){
					if(sum2){
						ans = (ans * sum2) % p;
						sum2--;
					} 
					else sum1--;
				}
			}
		}
		int maxn = max(sum1, sum2), minn = min(sum1, sum2);
		ans = ans * dx[maxn] % p * qpow(dx[maxn - minn], p - 2, p) % p * dx[cnt] % p * qpow(dx[cnt - minn], p - 2, p) % p * d2[minn] % p;
		sum1 -= minn, sum2 -= minn;
		int need = max(sum1, sum2);
		cout << ans * dx[need / 2] % p * d2[need / 2] % p << '\n'; 
	}
	return 0;
}
