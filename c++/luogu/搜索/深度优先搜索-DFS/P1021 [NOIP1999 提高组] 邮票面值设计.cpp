#include <bits/stdc++.h>
using namespace std;
const int N=51;
const int INF=1<<30;
int n, m, ans;
int dp[N<<8], sum[N], tmp[N];
void serch(int dep){
	if (dep>m){
		int i=0;
		while (dp[i]<=n){
			i++;
			dp[i]=INF;
			for (int j=0; j<=m&&i-tmp[j]>=0; j++){
				dp[i]=min(dp[i], dp[i-tmp[j]]+1);
			}
		}
		if (i-1>ans){
			ans=i-1;
			for (int j=1; j<=m; j++){
				sum[j]=tmp[j];
			}
		}
		return ;
	}
	for (int i=tmp[dep-1]+1; i<=tmp[dep-1]*n+1; i++){
		tmp[dep]=i;
		serch(dep+1);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	serch(1);
	for (int i=1; i<=m; i++){
		printf("%d ", sum[i]);
	}
	printf("\nMAX=%d", ans);

	return 0;
}