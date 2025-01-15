#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int Mod=998244353;
int n, m;
int a[N];
bool vis[N];
void init(){
	for (int i=0; i<N; i++){
		vis[i]=0;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		cin >> a[i];
		int tmp=a[i];
		for (int j=1; j<=a[i]; j++){
			tmp-=vis[j];
		}
		vis[a[i]]=1;
		a[i]=tmp-1;
	}
	a[n]+=m;
	for (int i=n; i>=1; i--){
		a[i-1]+=a[i]/(n-i+1);
		a[i]%=(n-i+1);
	}
	init();
	for (int i=1; i<=n; i++){
		for (int j=0; j<=a[i]; j++){
			a[i]+=vis[j];
		}
		printf("%lld ", a[i]+1);
		vis[a[i]]=1;
	}

	return 0;
}