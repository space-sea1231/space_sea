#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=998244353;
int t,n;
int a[2000020],b[2000020];
int frac[2000020],inv[2000020];
bool vis[2000020];
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
	cin>>n;
	for(int i=1;i<=2*n;i++) vis[i]=0;
	for(int i=1;i<=2*n;i+=2){
		cin>>a[i]>>a[i+1];
		if(a[i]&&a[i+1]) vis[a[i]]=vis[a[i+1]]=1;
	}
	int cnt=0;
	inv[0]=frac[0]=1;
	for(int i=1;i<=2*n;i++){
		if(!vis[i]) b[++cnt]=i;
		frac[i]=frac[i-1]*i%mo;
		inv[i]=po(frac[i],mo-2);
	}
	sort(b+1,b+1+cnt);
	int cnt1=0,cnt2=0;
	for(int i=1;i<=2*n;i+=2){
		if(a[i]&&!a[i+1]){
			int x=lower_bound(b+1,b+1+cnt,a[i])-b;
			if(x<=cnt/2) cnt1++;
			else cnt2++;
		}else if(a[i+1]&&!a[i]){
			int x=lower_bound(b+1,b+1+cnt,a[i+1])-b;
			if(x<=cnt/2) cnt1++;
			else cnt2++;
		}
	}
	int ans=calc(cnt/2-cnt2,cnt1)*frac[cnt1]%mo;
	ans*=calc(cnt/2-cnt1,cnt2)*frac[cnt2]%mo;
	ans%=mo;
	cnt=cnt/2-cnt1-cnt2;
	ans*=frac[cnt]*frac[cnt]%mo*po(2,cnt)%mo;
	ans%=mo;
	cout<<ans<<'\n';
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}