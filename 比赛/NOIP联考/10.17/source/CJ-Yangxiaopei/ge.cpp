#include<bits/stdc++.h>
#define int long long
#define mod 998442353
using namespace std;
int t, n, m, ans, minn = 1e18, a[20][20], s[20], f[20], p[20];
void dfs(int step){
	if(step > m){
		int sum = 0, cnt = 1;
		if(s[p[1]] == 0){
			return;
		}
		for(int i = 2; i <= m; i++){
			for(int j = 1; j <= n; j++){
				cnt *= abs(a[p[i]][j] - a[p[i - 1]][j]);
				cnt %= mod;
				sum += abs(a[p[i]][j] - a[p[i - 1]][j]);
			}
		}
		if(sum < minn){
			minn = sum;
			ans = cnt;
			ans %= mod;
		}
		if(sum == minn){
			minn = sum;
			ans += cnt;
			ans %= mod;
		}
		return;
	}
	for(int i = 1; i <= m; i++){
		if(!f[i]){
			f[i] = 1;
			p[step] = i;
			dfs(step + 1);
			f[i] = 0;
		}
	}
}
signed main(){
	freopen("ge.in", "r", stdin);
	freopen("ge.out", "w", stdout);
	cin >> t;
	while(t--){
		cin >> n >> m;
		for(int i = 1; i <= m; i++){
			for(int j = 1; j <= n; j++){
				cin >> a[i][j];
			}
		}
		for(int i = 1; i <= m; i++){
			cin >> s[i];
		}
		if(n == 1){
			int l = -1e6, r = 1e6;
			for(int i = 1; i <= m; i++){
				l = max(l, a[i][1]);
				r = min(r, a[i][1]);
			}
			minn = 1e18;
			int cnt = 0;
			for(int i = 1; i <= m; i++){
				if(s[i] == 1){
					int x = l - r + min(l - a[i][1], a[i][1] - r);
					if(x < minn){
						minn = x, cnt = 1;
					}
					else if(x == minn){
						cnt++;
					}
				}
			}
			if(cnt == 0){
				cout << "NIE\n";
			}
			else{
				cout << minn << " " << cnt << "\n";
			}
			continue;
		}
		minn = 1e18, ans = 0;
		dfs(1);
		cout << minn << ' ' << ans; 
	}
	return 0;
}

