#include <bits/stdc++.h>
using namespace std;
const int N=360;
const int M=130;
int n, m, a[N], cnt[5];
int dp[M][M][M][M];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		cin >> a[i];
	}
	for (int i=1; i<=m; i++){
		int b;
		cin >> b;
		cnt[b]++;
	}
	dp[0][0][0][0]=a[1];
	for (int i=0; i<=cnt[1]; i++){
		for (int j=0; j<=cnt[2]; j++){
			for (int k=0; k<=cnt[3]; k++){
				for (int l=0; l<=cnt[4]; l++){
					int r=i*1+j*2+k*3+l*4+1;
					if (i) dp[i][j][k][l]=max(dp[i][j][k][l], dp[i-1][j][k][l]+a[r]);
					if (j) dp[i][j][k][l]=max(dp[i][j][k][l], dp[i][j-1][k][l]+a[r]);
					if (k) dp[i][j][k][l]=max(dp[i][j][k][l], dp[i][j][k-1][l]+a[r]);
					if (l) dp[i][j][k][l]=max(dp[i][j][k][l], dp[i][j][k][l-1]+a[r]);
				}
			}
		}
	}
	printf("%d", dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]]);

	return 0;
}