#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
int ans, tot, n;
int a[N], sum[N], all[N];
bool vis[N];
bool check(int x){
	return x<1||x>n;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=1; i<n; i++){
		cin >> a[i];
		sum[i]=sum[i-1]+a[i];
		ans+=(n-i)*a[i];
	}
	tot=n*(n+1)/2;
	tot-=ans;
	if (tot%n){
		printf("-1");
		return 0;
	}
	tot/=n;
	if (check(tot)){
		printf("-1");
		return 0;
	}
	all[1]=tot;
	vis[tot]=1;
	for (int i=2; i<=n; i++){
		if (check(sum[i-1]+tot)){
			printf("-1");
			return 0;
		}
		vis[sum[i-1]+tot]=1;
		all[i]=sum[i-1]+tot;
	}
	for (int i=1; i<=n; i++){
		if (!vis[i]){
			printf("-1");
			return 0;
		}
	}
	for (int i=1; i<=n; i++){
		printf("%lld ", all[i]);
	}

	return 0;
}
