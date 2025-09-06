#include <bits/stdc++.h>
using namespace std;
#define int unsigned int
#define endl '\n'
#define more_test 1

inline void solve(){
	int n;
	cin >> n;
	vector<int>p(n);
	for(int i = 0;i < n;i++){
		cin >> p[i];
	}
	int ans = 0;
	for(int i = 0;i < n;i++){
		for(int j = i + 1;j < n;j++){
			int res = 0 , dww = 0 , lst = -1;
			swap(p[i] , p[j]);
			for(int k = 0;k < n;k++){
				if(p[k] > lst) dww++;
				else dww = 1;
				lst = p[k];
				res += dww;
			}
			ans = max(ans , res);
			swap(p[i] , p[j]);
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	freopen("wei.in" , "r" , stdin);
	freopen("wei.out" , "w" , stdout);
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	int _ = 1;
	if(more_test) cin >> _;
	while(_--) solve();
}