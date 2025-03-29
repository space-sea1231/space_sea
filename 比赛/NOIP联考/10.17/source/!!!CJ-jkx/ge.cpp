#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998442353;
int T,n,m,p[105][105],ans1,ans2,pt[1000005],fact[1000005],inv[1000005];
bool vis[1000005],s[1000005];
int quick_pow(int a,int b){
	if(!b) return 1ll;
	int sum=quick_pow(a,b>>1);
	(sum*=sum)%=mod;
	if(b&1) (sum*=a)%=mod;
	return sum;
}
int C(int n,int m){
	if(n<m||n<0||m<0) return 0;
	return fact[n]*inv[m]%mod*inv[n-m]%mod;
}
void dfs(int cur,int val1,int val2){
	if(cur>m){
		if(ans1>val1) ans1=val1,ans2=val2;
		else if(ans1==val1) (ans2+=val2)%=mod;
		return;
	}
	if(val1>ans1) return;
	for(int i=1; i<=m; i++) if(vis[i]==false&&(cur!=1||s[i]==true)){
		pt[cur]=i,vis[i]=true;
		int sum1=val1,sum2=val2;
		if(cur==1) dfs(cur+1,0,1);
		else{
			int s=0;
			for(int j=1; j<=n; j++) s+=abs(p[i][j]-p[pt[cur-1]][j]);
			sum1+=s;
			for(int j=1; j<=n; j++) (sum2*=C(s,abs(p[i][j]-p[pt[cur-1]][j])))%=mod,s-=abs(p[i][j]-p[pt[cur-1]][j]);
			dfs(cur+1,sum1,sum2);
		}
		vis[i]=false;
	}
	return;
}
int val=0;
void solve(){
	cin>>n>>m;
	for(int i=1; i<=m; i++) for(int j=1; j<=n; j++) cin>>p[i][j];
	for(int i=1; i<=m; i++) cin>>s[i];
	bool f=false;
	for(int i=1; i<=m; i++) f|=s[i];
	if(!f){cout<<"NIE\n";return;}
	ans1=(int)1e18,ans2=0;
	dfs(1,0,1);
	cout<<ans1<<' '<<ans2<<'\n';
	return;
}
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	fact[0]=1;
	for(int i=1; i<=1000000; i++) fact[i]=fact[i-1]*i%mod;
	inv[1000000]=quick_pow(fact[1000000],mod-2);
	for(int i=999999; i>=0; i--) inv[i]=inv[i+1]*(i+1)%mod;
	cin>>T;
	while(T--) solve();
	return 0;
}