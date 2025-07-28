#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n, a[N], dp[N];
void init(){
	for (int i=2; i<=n; i++){
		a[i]=1;
		for (int j=2; j*j<=i; j++){
			if (i%j==0){
				a[i]+=j;
				if (i/j!=j){
					a[i]+=i/j;
				}
			}
		}
		// printf("Debug: %d %d\n", i, a[i]);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	init();
	for (int i=2; i<=n; i++){
		for (int j=0; j<=i; j++){
			dp[i]=max(dp[i], dp[i-j]+a[j]);
		}
	}
	printf("%d", dp[n]);

	return 0;
}