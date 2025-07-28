#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n,a[400010],b[400010],dp[400010];
void solve(){
	n=read();for(int i=1;i<=n;i++) a[i]=read();int ans=0;
	auto upd=[&](int i,int j){swap(a[i],a[j]);int res=0;for(int i=1;i<=n;i++){dp[i]=(a[i]>a[i-1]?dp[i-1]+1:1);res+=dp[i];}ans=max(ans,res);swap(a[i],a[j]);};
	int cnt=0;for(int i=1;i<=n;i++) if(i==1||i==n||a[i]<a[i-1]||a[i]>a[i+1]) b[++cnt]=i;for(int i=1;i<=cnt;i++) for(int j=i+1;j<=cnt;j++) upd(b[i],b[j]);cout<<ans%(1ll<<32)<<'\n';
}
signed main(){
	freopen("wei.in","r",stdin);freopen("wei.out","w",stdout);
	T=read();while(T--) solve();
	return 0;
}