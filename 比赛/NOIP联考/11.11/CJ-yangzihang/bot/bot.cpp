#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10;
const int Mod=998244353;
const int INF=665496236;
int n, m, k, dp[N][N];
char c[N][N];
int mi(int a, int b){
	int sum=1;
	while (b){
		if (b&1){
			sum=(sum*a)%Mod;
		}
		a=(a*a)%Mod;
		b>>=1;
	}
	return sum;
}
signed main(){
	freopen("bot.in", "r", stdin);
	freopen("bot.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m >> k;
	for (int i=1; i<=k; i++){
		int x, y;
		cin >> x >> y;
		cin >> c[x][y];
	}
	dp[1][1]=1;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			if (c[i][j]=='D'){
				dp[i+1][j]=(dp[i+1][j]+dp[i][j])%Mod;
			}else if (c[i][j]=='R'){
				dp[i][j+1]=(dp[i][j+1]+dp[i][j])%Mod;
			}else if (c[i][j]=='X'){
				dp[i+1][j]=(dp[i+1][j]+dp[i][j])%Mod;
				dp[i][j+1]=(dp[i][j+1]+dp[i][j])%Mod;
			}else{
				dp[i+1][j]=(dp[i+1][j]+dp[i][j]*INF)%Mod;
				dp[i][j+1]=(dp[i][j+1]+dp[i][j]*INF)%Mod;
			}
		}
	}
	dp[n][m]=(dp[n][m]*mi(3, n*m-k))%Mod;
	printf("%lld", dp[n][m]);

	return 0;
}