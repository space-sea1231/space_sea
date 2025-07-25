#include <iostream>
#include <stdio.h>

using namespace std;

const int N=30;

int n;
int ans, id;
int dp[N];
int val[N], pre[N];
bool dist[N][N];

void dfs(int now){
	if (pre[now]==0){
		return ;
	}
	dfs(pre[now]);
	printf("%d ", pre[now]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> val[i];
	}
	for (int i=1; i<=n; i++){
		for (int j=i+1; j<=n; j++){
			bool x;
			cin >> x;
			dist[i][j]=dist[j][i]=x;
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			if (dp[j]>dp[i]&&dist[i][j]){
				dp[i]=dp[j];
				pre[i]=j;
			}
		}
		dp[i]+=val[i];
		if (dp[i]>=ans){
			ans=dp[i];
			id=i;
		}
	}
	dfs(id);
	printf("%d\n%d", id, ans);
	
	return 0;
}