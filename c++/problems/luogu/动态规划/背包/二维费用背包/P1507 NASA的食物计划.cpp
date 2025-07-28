#include <bits/stdc++.h>
using namespace std;
const int N=60;
const int M=4e2+10;
int h, t, n, dp[M][M];
int u[N], v[N], w[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> h >> t >> n;
	for (int i=1; i<=n; i++){
		cin >> u[i] >> v[i] >> w[i];
	}
	for (int i=1; i<=n; i++){
		for (int j=h; j>=u[i]; j--){
			for (int k=t; k>=v[i]; k--){
				dp[j][k]=max(dp[j][k], dp[j-u[i]][k-v[i]]+w[i]);
			}
		}
	}
	printf("%d", dp[h][t]);

	return 0;
}