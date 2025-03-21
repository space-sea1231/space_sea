#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n, m, ans=1<<30;//n:小组数 m：天数
int a[N][N], dp[N][N];//dp[i][j]:第i天的事由第j个小组来处理的最小时间
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> m >> n;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			cin >> a[j][i];
		}
	}
	for (int i=1; i<=n; i++){
		dp[1][i]=a[1][i];
	}
	for (int i=2; i<=m; i++){
		for (int j=1; j<=n; j++){
			dp[i][j]=min(dp[i-1][j], dp[i-1][(j-1)?(j-1):n])+a[i][j];
		}
	}
	for (int i=1; i<=n; i++){
		ans=min(ans, dp[m][i]);
	}
	printf("%d", ans);

	return 0;
}