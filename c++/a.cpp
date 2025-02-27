#include<bits/stdc++.h>
using namespace std;
const int N=16;
int a,b,t[N],w[N],T[1<<N],W[1<<N],dp[1<<N];
signed main() {
	scanf("%d%d",&a,&b);
	const int mx=(1<<b)-1;
	for(int i=1;i<=b;i++) scanf("%d%d",&t[i],&w[i]);
	for(int i=0;i<=mx;i++) {
		for(int j=1;j<=b;j++) {
			if(i&(1<<(j-1))) {
				T[i]=max(T[i],t[j]);//预处理出状态i的T和W
				W[i]+=w[j];
			}
		}
	}
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;//初始化dp
	for(int i=0;i<=mx;i++) {
		for(int j=i;;j=i&(j-1)) {//这样就可以枚举完i的所有属于它的状态j，原理就不再多说了
			if(W[i^j]<=a) dp[i]=min(dp[i],dp[j]+T[i^j]);
			if(!j) break;
		}
	}
	printf("%d",dp[mx]);//dp[max]即为所求
	return 0;
}