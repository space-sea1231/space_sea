#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=9;
int t, l, r, n, ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> t;
	while (t--){
		cin >> l >> r;
		n=(r-l+1)%Mod;
		ans=n*l%Mod+n*(n-1)%Mod*5%Mod;
		printf("%lld\n", ans%Mod);
	}

	return 0;
}