#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,MOD=998244353;
int T,n,a[N],b[N],jc[N];
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ans;
}
void solve(){
	cin>>n;
	for(int i=1;i<=2*n;i++){
		if(i&1) cin>>a[(i+1)/2];
		else cin>>b[i/2];
	}
	int ans=1,tot=0,tot1=0,tot2=0;
	for(int i=1;i<=n;i++){
		if(a[i]==0 && b[i]==0) ++tot;
		if(a[i]!=0){
			if(a[i]<=n) ++tot1;
			else ++tot2;
		}
		if(b[i]!=0){
			if(b[i]<=n) ++tot1;
			else ++tot2;
		}
	}
	int pre_tot1=0,pre_tot2=0;
	for(int i=1;i<=n;i++){
		if(a[i]!=0 && b[i]==0){
			if(a[i]<=n) ans=ans*(n-tot2-pre_tot1),++pre_tot1;
			else ans=ans*(n-tot1-pre_tot2),++pre_tot2;
		}
		if(a[i]==0 && b[i]!=0){
			if(b[i]<=n) ans=ans*(n-tot2-pre_tot1),++pre_tot1;
			else ans=ans*(n-tot1-pre_tot2),++pre_tot2;
		}
	}
	ans=ans*jc[tot]%MOD*jc[tot]%MOD*ksm(2,tot)%MOD;
	cout<<ans<<'\n';
	return ;
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	jc[0]=1;
	for(int i=1;i<=1000000;i++) jc[i]=jc[i-1]*i%MOD;
	while(T--) solve();
	return 0;
}
