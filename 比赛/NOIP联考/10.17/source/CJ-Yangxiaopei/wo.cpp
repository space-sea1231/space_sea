#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int q, n, a[6000005], f[6000005], t[600005];
vector<int> g;
unordered_map<int, int> mp;
signed main(){
	freopen("wo.in", "r", stdin);
	freopen("wo.out", "w", stdout);
	cin >> q;
	while(q--){
		cin >> n;
		n *= 2;
		memset(f, 0, sizeof(f));
		g.clear();
		mp.clear();
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			f[a[i]] = 1;
		}
		int l = 1, r = 0;
		for(int i = 1; i <= n; i++){
			if(!f[i]){
				r++;
				t[r] = i;
			}
		}
		int sum = 0, y = 0;
		for(int i = 1; i <= n; i += 2){
			if(a[i] && a[i + 1]){
				continue;
			}
			else if(a[i]){
				if(abs(t[l] - a[i]) > abs(t[r] - a[i])){
					g.push_back(max(a[i], t[l]));
					l++;
				} 
				else{
					g.push_back(max(a[i], t[r]));
					r--;
				}
			}
			else if(a[i + 1]){
				if(abs(t[l] - a[i + 1]) > abs(t[r] - a[i + 1])){
					g.push_back(max(a[i + 1], t[l]));
					l++;
				} 
				else{
					g.push_back(max(a[i + 1], t[r]));
					r--;
				}
			}
			else{
				continue;
			}
		}
		for(int i = l, j = r; i <= (l + r) / 2; i++, j--){
			g.push_back(t[j]);
			y++;
		}
		sort(g.begin(), g.end());
		l = 1, r = 0;
		for(int i = 1; i <= n; i++){
			if(!f[i]){
				r++;
				t[r] = i;
			}
		}
		int ans = 1, x = g.size();
		for(int i = 1; i <= n; i += 2){
			if(a[i] && a[i + 1]){
				continue;
			}
			else if(a[i]){
				if(abs(t[l] - a[i]) > abs(t[r] - a[i])){
					ans *= x, ans %= mod, x--;
					l++;
				} 
				else{
					ans *= x, ans %= mod, x--;
					r--;
				}
			}
			else if(a[i + 1]){
				if(abs(t[l] - a[i + 1]) > abs(t[r] - a[i + 1])){
					ans *= x, ans %= mod, x--;
					l++;
				} 
				else{
					ans *= x, ans %= mod, x--;
					r--;
				}
			}
			else{
				continue;
			}
		}
		for(int i = 1; i <= y; i++){
			ans *= i, ans %= mod;
			ans *= i, ans %= mod;
		}
		ans *= 2, ans %= mod;
		cout << ans << "\n";
	}
	return 0;
}
/*
1000000000
01********
*/
