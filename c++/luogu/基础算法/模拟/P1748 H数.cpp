#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10;
const int INF=1LL<<60;
int n, sum[N];
int a=1, b=1, c=1, d=1;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	sum[1]=1;
	for (int i=2; i<=n; i++){
		sum[i]=INF;
		sum[i]=min(sum[i], sum[a]*2);
		sum[i]=min(sum[i], sum[b]*3);
		sum[i]=min(sum[i], sum[c]*5);
		sum[i]=min(sum[i], sum[d]*7);
		if (sum[i]==sum[a]*2){
			a++;
		}
		if (sum[i]==sum[b]*3){
			b++;
		}
		if (sum[i]==sum[c]*5){
			c++;
		}
		if (sum[i]==sum[d]*7){
			d++;
		}
	}
	printf("%lld", sum[n]);

	return 0;
}