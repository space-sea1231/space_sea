#include <bits/stdc++.h>
#define int long long
const long long p = pow(2, 32);
using namespace std;
int t, n, a[400005], siz[400005];

int solve(){
	int lin = 0;
	for( int i = 1; i <= n; i++ ){
		if(a[i] > a[i - 1]) siz[i] = siz[i - 1] + 1;
		else siz[i] = 1;
		lin += siz[i];
	}
	return lin; 
}

signed main(){
	freopen("wei.in", "r", stdin);
	freopen("wei.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t--){
		int ans = 0;
		cin >> n;
		for( int i = 1; i <= n; i++ ) cin >> a[i];
		for( int i = 1; i <= n; i++ ){
			for( int j = 1; j <= i; j++ ){
				swap(a[i], a[j]);
				ans = max(ans, solve());
				swap(a[i], a[j]);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
