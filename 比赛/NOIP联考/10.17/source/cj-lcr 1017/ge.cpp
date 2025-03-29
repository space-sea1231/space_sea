#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define fr first
#define sc second
inline int read(){
	int res=0,f=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {res=res*10+(c-'0');c=getchar();}
	return res*f;
}
const int N=22,P=2e5+5,M=998442353;
int n,m,p[N][N],t[N],d[N][N],c[N][N],vis[N],a[N],ans,res;
int fac[P],ifac[P],inv[P];
int Abs(int x){
    if (x>=0) return x;
    return -x;
}
int C(int _,int __){
	if (_<0||__<0||_<__) return 0;
	return fac[_]*ifac[__]%M*ifac[_-__]%M;
}
void dfs(int w){
    if (w==m+1){
        int s=0,cnt=1;
        for (int i=2;i<=m;i++){
            s+=d[a[i-1]][a[i]];
            cnt*=c[a[i-1]][a[i]],cnt%=M;
        }
        if (s<ans) ans=s,res=0;
        if (s==ans) res=(res+cnt)%M;
        return;
    }
    for (int i=1;i<=m;i++){
        if (vis[i]||(w==1&&!t[i])) continue;
        vis[i]=1,a[w]=i,dfs(w+1),vis[i]=0;
    }
}
signed main(){
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
	int T=read();
    fac[0]=ifac[0]=1;
	for (int i=1;i<P;i++){
		if (i==1) inv[i]=1;
		else inv[i]=((-(M/i)*inv[M%i])%M+M)%M;
		fac[i]=fac[i-1]*i%M;
		ifac[i]=ifac[i-1]*inv[i]%M;
	}
	for (int _=1;_<=T;_++){
		n=read(),m=read();
        for (int i=1;i<=m;i++)
            for (int j=1;j<=n;j++)
                p[j][i]=read();
        for (int i=1;i<=m;i++)
            t[i]=read();
        if (n==1){
            int l=1e18,r=-1e18;
            ans=1e18,res=0;
            for (int i=1;i<=m;i++)
                l=min(l,p[1][i]),r=max(r,p[1][i]);
            for (int i=1;i<=m;i++){
                if (!t[i]) continue;
                int x=Abs(p[1][i]-l)+r-l,y=Abs(p[1][i]-r)+r-l;
                if (x<ans) ans=x,res=0;
                if (x==ans) res=(res+1)%M;
                if (y<ans) ans=y,res=0;
                if (y==ans) res=(res+1)%M;
            }
            cout<<ans<<' '<<res<<'\n';
            continue;
        }
        for (int i=1;i<=m;i++)
            for (int j=1;j<=m;j++){
                d[i][j]=0,c[i][j]=1;
                for (int x=1;x<=n;x++)
                    d[i][j]+=Abs(p[x][i]-p[x][j]);
                int s=d[i][j];
                for (int x=1;x<=n;x++){
                    c[i][j]=c[i][j]*C(s,Abs(p[x][i]-p[x][j]))%M;
                    s-=Abs(p[x][i]-p[x][j]);
                }
            }
        ans=1e18,res=0,dfs(1);
        cout<<ans<<' '<<res<<'\n';
	}
	return 0;
}