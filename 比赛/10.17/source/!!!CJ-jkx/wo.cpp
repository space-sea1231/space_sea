#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int t,n,a[2000005];
bool vis[2000005];
void solve(){
	cin>>n;
	for(int i=1; i<=2*n; i++) vis[i]=false;
	for(int i=1; i<=2*n; i++) cin>>a[i];
	int cnt=2*n;
	for(int i=1; i<=2*n; i+=2) if(a[i]&&a[i+1]) vis[a[i]]=vis[a[i+1]]=true,cnt-=2;
	cnt/=2;
	int val=0;
	for(int i=1; i<=2*n; i++){
		if(vis[i]==true) continue;
		val++;
		if(val==cnt){
			val=i;
			break;
		}
	}
	int sum0=cnt,sum1=cnt;
	for(int i=1; i<=2*n; i+=2){
		if(a[i]<a[i+1]) swap(a[i],a[i+1]);
		if(a[i+1]==0&&a[i]){
			if(a[i]<=val) sum0--;
			else sum1--;
		}
	}
	int val0=sum0,val1=sum1,ans=1;
	// cout<<cnt<<' '<<val0<<' '<<val1<<'\n';
	for(int i=cnt; i>sum0; i--) (ans*=val1--)%=mod;
	for(int i=cnt; i>sum1; i--) (ans*=val0--)%=mod;
	// cout<<val0<<' '<<val1<<'\n';
	for(int i=1; i<=val0; i++) (ans*=i*i%mod)%=mod,(ans*=2)%=mod;
	cout<<ans<<'\n';
	return;
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) solve();
	return 0;
}