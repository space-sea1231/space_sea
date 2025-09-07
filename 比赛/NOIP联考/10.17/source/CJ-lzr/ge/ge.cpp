#include<bits/stdc++.h>
#define int long long
const int mod=998442353;
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n,m,p[20][20],s[20],dis[20][20],vis[20],fac[5000010],inv[5000010];
int qpow(int x,int y){int ans=1;for(;y;y>>=1,x=x*x%mod) if(y&1) ans=ans*x%mod;return ans;}
void solve(){
	n=read();m=read();for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) p[i][j]=read();for(int i=1;i<=m;i++) s[i]=read();
	memset(dis,0,sizeof(dis));for(int i=1;i<=m;i++) for(int j=1;j<=m;j++) for(int k=1;k<=n;k++) dis[i][j]+=abs(p[i][k]-p[j][k]);
	int ans=1e18,way=0;function<void(int,int,int,int)>dfs=[&](int u,int now,int sum,int cnt){
		if(sum>ans) return ;if(u>m){if(sum<ans) ans=sum,way=cnt;else if(sum==ans) (way+=cnt)%=mod;return ;}
		for(int i=1;i<=m;i++) if(!vis[i]){
			int mul=fac[dis[now][i]];for(int j=1;j<=n;j++) (mul*=inv[abs(p[now][j]-p[i][j])])%=mod;
			vis[i]=1;dfs(u+1,i,sum+dis[now][i],cnt*mul%mod);vis[i]=0;
		}
	};for(int i=1;i<=m;i++) if(s[i]) vis[i]=1,dfs(2,i,0,1),vis[i]=0;if(ans==1e18) cout<<"NIE\n";else cout<<ans<<' '<<way<<'\n';
}
signed main(){
	freopen("ge.in","r",stdin);freopen("ge.out","w",stdout);
	fac[0]=1;for(int i=1;i<=5e6;i++) fac[i]=fac[i-1]*i%mod;inv[5000000]=qpow(fac[5000000],mod-2);for(int i=5e6-1;~i;i--) inv[i]=inv[i+1]*(i+1)%mod;
	T=read();while(T--) solve();
	return 0;
}