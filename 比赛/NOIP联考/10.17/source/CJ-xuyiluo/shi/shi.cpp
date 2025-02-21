#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define more_test 1

inline void solve(){
	string s;
	cin >> s;
	int n = s.size();
	s = ' ' + s;
	int sum = 0;
	for(int i = 1;i <= n;i++){
		sum += s[i] - '0';
	}
	if(sum == 0){
		int res = n - n % 3;
		if(n % 3 == 2){
			res++;
			cout<<res<<' ';
			vector<int> ans;
			int i;
			for(i = 3;i <= n;i += 3){
				ans.push_back(i - 1);
			}
			i -= 3;
			ans.push_back(i + 1);
			cout<<ans.size()<<'\n';
			for(auto v:ans){
				cout<<v<<' ';
			}
			cout<<'\n';
			return ;
		}
		cout<<res<<' ';
		vector<int> ans;
		for(int i = 3;i <= n;i += 3){
			ans.push_back(i - 1);
		}
		cout<<ans.size()<<'\n';
		for(auto v:ans){
			cout<<v<<' ';
		}
		cout<<'\n';
		return ;
	}
}
signed main(){
	freopen("shi.in" , "r" , stdin);
	freopen("shi.out" , "w" , stdout);
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	int _ = 1;
	if(more_test) cin >> _;
	while(_--) solve();
}