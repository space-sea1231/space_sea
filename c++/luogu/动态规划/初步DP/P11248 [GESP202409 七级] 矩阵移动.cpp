#include <bits/stdc++.h>
using namespace std;
const int N=5e2+10;
const int M=3e2+10;
int t, n, m, x, dp[N][N][M];
char c[N][N];
void init(){
	for (int k=0; k<M; k++){
		for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				dp[i][j][k]=0;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> t;
	while (t--){
		// init();
		cin >> n >> m >> x;
		for (int i=1; i<=n; i++){
			for (int j=1; j<=m; j++){
				cin >> c[i][j];
			}
		}
		for (int k=0; k<=x; k++){
			for (int i=1; i<=n; i++){
				for (int j=1; j<=m; j++){
					dp[i][j][k]=0;
					int tmp=(c[i][j]=='?'?0:c[i][j]-'0');
					dp[i][j][k]=max(dp[i-1][j][k], dp[i][j-1][k])+tmp;
					if (c[i][j]=='?'&&k){
						dp[i][j][k]=max(dp[i][j][k], dp[i-1][j][k-1]+1);
						dp[i][j][k]=max(dp[i][j][k], dp[i][j-1][k-1]+1);
					}
				}
			}
		}
		int ans=0;
		for (int i=0; i<=x; i++){
			ans=max(ans, dp[n][m][i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}