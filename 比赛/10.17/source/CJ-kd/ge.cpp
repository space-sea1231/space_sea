#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=21,mod=998442353;
int n,m,a[N][N],val[N][N],ff[N][N],f[(1<<16)+5][N],g[(1<<16)+5][N],vis[(1<<16)+5][N],fac[2000005];
inline int read(){
    register int x=0,t=0;
    static char ch=getchar();
    while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return t?-x:x;
}
struct node{
	int S,x,dist;
	bool operator <(const node& A)const{
		return dist>A.dist;
	}
};
priority_queue<node> q;
inline void exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}
inline int ksm(int a,int b){
	int x=1;
	while(b){
		if(b&1) x=x*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return x;
}
inline int inv(int x){return ksm(x,mod-2);}
inline int C(int x,int y){
	return fac[x]*inv(fac[x-y])%mod*inv(fac[y])%mod;
}
inline void work(){
	m=read();n=read();
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++) a[i][j]=read();
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			val[i][j]=0;
			ff[i][j]=1;
			for(register int k=1;k<=m;k++) val[i][j]+=labs(a[i][k]-a[j][k]);
			int lft=val[i][j];
			for(register int k=1;k<=m;k++){
				ff[i][j]=ff[i][j]*C(lft,labs(a[i][k]-a[j][k]))%mod;
				lft-=labs(a[i][k]-a[j][k]);
			}
		}
	}
	int all=(1ll<<n)-1;
	for(register int S=0;S<=all;S++) for(register int i=1;i<=n;i++) f[S][i]=1e18,g[S][i]=vis[S][i]=0;
	for(register int i=1;i<=n;i++){
		int now=read();
		if(now) q.push({1ll<<(i-1),i,0}),f[1ll<<(i-1)][i]=0,g[1ll<<(i-1)][i]=1;
	}
	while(q.size()){
		int S=q.top().S,x=q.top().x;q.pop();
		if(vis[S][x]) continue;
		vis[S][x]=1;
		if(S==all) continue;
		for(register int y=1;y<=n;y++){
			if(S&(1ll<<(y-1))) continue;
			int T=S|(1ll<<(y-1));
			if(f[T][y]>f[S][x]+val[x][y]){
				f[T][y]=f[S][x]+val[x][y];
				g[T][y]=g[S][x]*ff[x][y]%mod;
				if(!vis[T][y]) q.push({T,y,f[T][y]});
			}
			else if(f[T][y]==f[S][x]+val[x][y]) (g[T][y]+=g[S][x]*ff[x][y]%mod)%=mod;
		}
	}
	int ans=1e18,ans2=0;
	for(register int i=1;i<=n;i++) ans=min(ans,f[all][i]);
	for(register int i=1;i<=n;i++) if(f[all][i]==ans) (ans2+=g[all][i])%=mod;
	if(!ans2){
		puts("NIE");
		return;
	}
	printf("%lld %lld\n",ans,ans2);
}
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	fac[0]=1;
	for(register int i=1;i<=2e6;i++) fac[i]=fac[i-1]*i%mod;
	int T=read();
	while(T--) work();
	return 0;
}
/*
1
6 7
1 -2 -1 0 -1 0
1 0 -2 -2 1 -1
-1 0 -1 -1 1 0
-1 -1 -1 0 -1 1
0 2 -1 1 2 -2
-1 0 -1 -1 -1 2
0 2 2 -1 0 -1
1 1 0 0 1 0 1
*/