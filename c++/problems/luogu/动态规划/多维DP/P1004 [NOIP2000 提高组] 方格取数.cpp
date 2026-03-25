#include <bits/stdc++.h>
using namespace std;
const int N=30;
int n, a[N][N];
int dp[N][N][N][N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	while (1){
		int x, y, z;
		cin >> x >> y >> z;
		if (!x&&!y&&!z){
			break;
		}
		a[x][y]=z;
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			for (int k=1; k<=n; k++){
				int l=i+j-k;
				if (l<=0){
					continue;
				}
				dp[i][j][k][l]=max(dp[i][j][k][l], dp[i-1][j][k-1][l]);
				dp[i][j][k][l]=max(dp[i][j][k][l], dp[i][j-1][k-1][l]);
				dp[i][j][k][l]=max(dp[i][j][k][l], dp[i-1][j][k][l-1]);
				dp[i][j][k][l]=max(dp[i][j][k][l], dp[i][j-1][k][l-1]);
				if (i==k&&j==l){
					dp[i][j][k][l]+=a[i][j];
				}else{
					dp[i][j][k][l]+=a[i][j]+a[k][l];
				}
			}
		}
	}
	printf("%d", dp[n][n][n][n]);
	
	return 0;
}