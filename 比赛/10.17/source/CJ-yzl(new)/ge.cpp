#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=998442353;
int t,n,m;
int a[20][20];
int s[20],d[20],frac[4000040],inv[4000040];
int po(int x,int y){
	int z=1;
	while(y){
		if(y%2) z*=x,z%=mo;
		x*=x,x%=mo;
		y/=2;
	}
	return z;
}
int calc(int x,int y){
	return frac[x]*inv[y]%mo*inv[x-y]%mo;
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=m;i++){
		cin>>s[i];
	}
	if(n==1){
		int maxn=-1e9,minn=1e9;
		int ans=1e9;
		for(int i=1;i<=m;i++){
			maxn=max(maxn,a[i][1]);
			minn=min(minn,a[i][1]);
		}
		for(int i=1;i<=m;i++){
			if(!s[i]) continue;
			ans=min(ans,maxn-minn+min(abs(a[i][1]-minn),abs(a[i][1]-maxn)));
		}
		cout<<ans<<" ";
		int cnt=0;
		for(int i=1;i<=m;i++){
			if(!s[i]) continue;
			if(maxn-minn+min(abs(a[i][1]-minn),abs(a[i][1]-maxn))==ans) cnt++;
		}
		cout<<cnt<<'\n';
	}else if(m==2){
		int ans=0;
		for(int i=1;i<=n;i++){
			d[i]=abs(a[1][i]-a[2][i]);
			ans+=d[i];
		}
		cout<<ans<<" ";
		frac[0]=inv[0]=1;
		for(int i=1;i<=ans;i++){
			frac[i]=frac[i-1]*i%mo;
			inv[i]=po(frac[i],mo-2);
		}
		int cnt=1;
		for(int i=1;i<=n;i++){
			cnt*=calc(ans,d[i]);
			cnt%=mo;
			ans-=d[i];
		}
		cout<<cnt*(s[1]+s[2])%mo<<'\n';
	}
}
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}