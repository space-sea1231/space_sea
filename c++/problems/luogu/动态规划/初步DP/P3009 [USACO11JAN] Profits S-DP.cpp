#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, ans=-(1<<30), dp[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<=n; i++){
		int a;
		cin >> a;
		dp[i]=max(a, dp[i-1]+a);
		ans=max(ans, dp[i]);
	}
	printf("%d", ans);

	return 0;
}