#include<bits/stdc++.h>
using namespace std;
int q , ans , n , cnt , fuck;
bool vis[20005] ;
int a[20005] ;
map<pair<int,int>,int>mp;
void dfs (int now ) {
	if (now > n) {
		int q = 0;
		for (int i = 1;i <= n;++i) q += abs(a[2 * i] - a[2 * i - 1ll]);
		if (q > ans) {
			ans = q , cnt = 1;
			
		}
		else if (q == ans) ++ cnt;
		return ;
	}
	if (a[now] != 0) dfs (now + 1);
	else {
		for (int i = 1;i <= n;++i) if (!vis[i]) vis[i] = 1 , a[now] = i, dfs (now + 1) , a[now] = 0 , vis[i] = 0;
	}
}
signed main() {
	cin >> n;
	n = n << 1;
	for (int i = 1;i <= n;++i) cin >> a[i] , vis[a[i]] = 1;
	dfs (1);
	cout << cnt << "\n";
	return 0;
}

