#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+5,MOD=4294967296;
int T,n,a[N],pre[N];
int run(){
	int ans=0;
	for(int i=1;i<=n;i++){
		if(i==1) pre[i]=i;
		else{
			if(a[i]>a[i-1]) pre[i]=pre[i-1];
			else pre[i]=i;
		}
		ans=(ans+i-pre[i]+1)%MOD;
	}
	return ans;
}
void solve(){
	int ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	ans=max(ans,run());
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			swap(a[i],a[j]);
			ans=max(ans,run());
			swap(a[i],a[j]);
		}
	}
	cout<<ans<<'\n';
	return ;
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}

