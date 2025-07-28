#include <bits/stdc++.h>
using namespace std;
const int N=70;
const int M=3.2e4+10;
int n, m, now;
int w[N], v[N], with_w[N][3], with_v[N][3];
int dp[M];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> m >> n;
	for (int i=1; i<=n; i++){
		int x, y, opt;
		cin >> x >> y >> opt;
		if (opt==0){
			w[i]=x;
			v[i]=y;
		}else{
			if (with_w[opt][1]){
				with_w[opt][2]=x;
				with_v[opt][2]=y;
			}else{
				with_w[opt][1]=x;
				with_v[opt][1]=y;
			}
		}
	}
	for (int i=1; i<=n; i++){
		if (w[i]){
			for (int j=m; j>=w[i]; j--){
				dp[j]=max(dp[j], dp[j-w[i]]+w[i]*v[i]);
				if (j>=w[i]+with_w[i][1]){
					dp[j]=max(dp[j], dp[j-w[i]-with_w[i][1]]+w[i]*v[i]+with_w[i][1]*with_v[i][1]);
				}
				if (j>=w[i]+with_w[i][2]){
					dp[j]=max(dp[j], dp[j-w[i]-with_w[i][2]]+w[i]*v[i]+with_w[i][2]*with_v[i][2]);
				}
				if (j>=w[i]+with_w[i][1]+with_w[i][2]){
					dp[j]=max(dp[j], dp[j-w[i]-with_w[i][1]-with_w[i][2]]+w[i]*v[i]+with_w[i][1]*with_v[i][1]+with_w[i][2]*with_v[i][2]);
				}
			}
		}
	}
	printf("%d", dp[m]);

	return 0;
}