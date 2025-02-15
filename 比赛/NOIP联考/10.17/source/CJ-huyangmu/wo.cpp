#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
const int KMod = 998244353;
int t, n, a[N << 1], vis[N << 1], cnt, maxn = -1;
void dfs (int x){
	if (x > 2 * n){
		int sum = 0ll;
		for (int i = 1; i <= n; ++i) sum += abs (a[2 * i - 1] - a[2 * i]);
		if (maxn < sum){
			maxn = sum;
			cnt = 1;
		}else cnt = (cnt + 1) % KMod;
		return ;
	}
	if (a[x] != 0) dfs (x + 1);
	else{
		for (int i = 1; i <= 2 * n; ++i){
			if (vis[i] == 0){
				a[x] = i;
				vis[i] = 1;
				dfs (x + 1);
				vis[i] = 0;
				a[x] = 0;
			}
		}
	}
}
void init (){
	cnt = 0, maxn = -1;
	for (int i = 1; i <= 2 * n; ++i) vis[i] = 0;
	return ;
}
signed main (){
	freopen ("wo.in", "r", stdin);
	freopen ("wo.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> t;
	while (t --){
		cin >> n;
		init();
		for (int i = 1; i <= 2 * n; ++i){
			cin >> a[i];
			if (a[i] > 0ll) vis[a[i]] = 2;
		}
		dfs (1);
		cout << cnt << '\n'; 
	}                       
	return 0;                                                   
}
