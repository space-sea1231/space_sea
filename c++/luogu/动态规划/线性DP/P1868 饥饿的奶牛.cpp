#include <bits/stdc++.h>
using namespace std;
const int N=3e6+10;
vector<int> q[N];
int n, maxn, dp[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<=n; i++){
		int x, y;
		cin >> x >> y;
		q[y].push_back(x);
		maxn=max(maxn, y);
	}
	for (int i=1; i<=maxn; i++){
		dp[i]=dp[i-1];
		for (int j=0; j<q[i].size(); j++){
			int x=q[i][j], y=i;
			dp[y]=max(dp[y], dp[x-1]+y-x+1);
		}
	}
	printf("%d", dp[maxn]);

	return 0;
}