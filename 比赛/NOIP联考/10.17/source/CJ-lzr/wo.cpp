#include<bits/stdc++.h>
#define int long long
const int mod=998244353;
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n,p[2000010],fac[2000010],inv[2000010];
int qpow(int x,int y){int ans=1;for(;y;y>>=1,x=x*x%mod) if(y&1) ans=ans*x%mod;return ans;}
int c(int n,int m){if(n<m) return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
void solve(){
	n=read();for(int i=1;i<=(n<<1);i++) p[i]=read();int cnt=0;for(int i=1;i<=n;i++) if(p[(i<<1)-1]&&p[i<<1]) cnt++;
	int A=0,B=0;for(int i=1;i<=n;i++){if(p[(i<<1)-1]&&!p[i<<1]) (p[(i<<1)-1]<=n-cnt?A++:B++);else if(!p[(i<<1)-1]&&p[i<<1]) (p[i<<1]<=n-cnt?A++:B++);}
	int ans=c(n-cnt-B,A)*fac[A]%mod*c(n-cnt-A,B)%mod*fac[B]%mod,res=0;for(int i=0;i<=n-cnt-A-B;i++) (res+=c(n-cnt-A-B,i)*c(n-cnt-A-B,n-cnt-A-B-i)%mod*fac[n-cnt-A-B]%mod*fac[n-cnt-A-B-i]%mod*fac[i]%mod)%=mod;
	cout<<ans*res%mod<<'\n';
}
signed main(){
	freopen("wo.in","r",stdin);freopen("wo.out","w",stdout);
	fac[0]=1;for(int i=1;i<=1e6;i++) fac[i]=fac[i-1]*i%mod;inv[1000000]=qpow(fac[1000000],mod-2);for(int i=1e6-1;~i;i--) inv[i]=inv[i+1]*(i+1)%mod;
	T=read();while(T--) solve();
	return 0;
}