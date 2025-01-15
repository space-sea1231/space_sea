#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
int n, dp[N];
void init(){
	for (int i=1; i<N; i++){
		dp[i]=1<<30;
	}
	dp[3]=1;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	init();
	cin >> n;
	for (int i=5; i<=n; i++){
		dp[i]=min(dp[i-3], dp[i-5])+1;
	}
	if (dp[n]<(1<<30)){
		printf("%d", dp[n]);
	}else{
		printf("-1");
	}
	return 0;
}