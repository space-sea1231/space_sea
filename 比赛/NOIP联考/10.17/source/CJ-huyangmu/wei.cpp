#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 4e5 + 5;
const int KMod = (1ll << 32);
int t, n, a[N], b[N], dp[N], sum, ans = -1;
void init (){
	ans = -1, sum = 0;
	return ;
}
signed main (){
	freopen ("wei.in", "r", stdin);
	freopen ("wei.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> t;
	while (t --){
		cin >> n;
		init();
		for (int i = 1; i <= n; ++i){
			cin >> a[i];
			b[i] = a[i];
		}
		for (int i = 1; i <= n; ++i){
			for (int j = i + 1; j <= n; ++j){
				swap (a[i], a[j]);
				dp[n] = n;
				sum = 1;
				for (int k = n - 1; k >= 1; --k){
					if (a[k] < a[k + 1]){
						dp[k] = dp[k + 1];
						sum += (dp[k] - k + 1);
					}
					else{
						dp[k] = k;
						sum += 1;
					}
				}
				ans = max (ans, sum);
				for (int k = 1; k <= n; ++k) a[k] = b[k];
			}
		}
		cout << ans % KMod << '\n';
	}
	return 0;
} 
