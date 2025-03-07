#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n, top;
int sum[N], vis[N];
void init(){
	for (int i=2; i<=n; i++){
		if (!vis[i]){
			sum[++top]=i;
		}
		for (int j=1; j<=top&&i*sum[j]<=n; j++){
			vis[i*sum[j]]=1;
			if (i%sum[j]==0){
				break;
			}
		}
	}
}
int mi(int a, int b){
	int sum=1;
	while (b){
		if (b&1){
			sum=(sum*a);
		}
		a=(a*a);
		b>>=1;
	}
	return sum;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	init();
	for (int i=1; i<=top; i++){
		int tmp=0;
		for (int j=1; mi(sum[i], j)<=n; j++){
			tmp+=n/mi(sum[i], j);
		}
		printf("%lld %lld\n", sum[i], tmp);
	}

	return 0;
}