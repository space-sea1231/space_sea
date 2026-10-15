#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1000005,mod=1e9+7;
int n,a[N];
int f[N],g[N];
signed main(){
    freopen("resona.in","r",stdin);
    freopen("resona.out","w",stdout);
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		if(a[i]==a[i-1]) i--,n--;
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]+g[a[i]];
		g[a[i]]+=f[i-1];
		if(g[a[i]]>=mod) g[a[i]]-=mod;
		if(f[i]>=mod) f[i]-=mod;
	}
    cout << f[n] << "\n";
	return 0;
}