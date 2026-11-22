#include<bits/stdc++.h>
using namespace std;
#define N 500004
#define ll long long
int n,ans;ll a[N];
inline int read(){
	static char c;
	static int r,f;r=f=0;
	while((c<48||c>57)&&c!=45)c=getchar();
	if(c==45)f=1,c=getchar();
	while(c>47&&c<58)r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}
int head[N],nxt[N<<1],to[N<<1],cnt;
inline void addedge(int a,int b){
    ++cnt;nxt[cnt]=head[a],to[cnt]=b;head[a]=cnt;
}
ll f[N][2];int g[N];
void dfs1(int p,int fa){
    f[p][0]=0;f[p][1]=a[p];g[p]=1;
    for(int j=head[p],i;j;j=nxt[j])if((i=to[j])!=fa){
        dfs1(i,p);f[p][0]+=max(f[i][0],f[i][1]);f[p][1]+=f[i][0];
        if(f[i][0]<f[i][1])g[p]+=g[i];
    }
}
ll F[N][2];int G[N];
void dfs2(int p,int fa){
    if(fa){
        ll d1=F[fa][1]-f[p][0];
        ll d0=F[fa][0]-max(f[p][0],f[p][1]);
        F[p][0]=f[p][0]+max(d0,d1),F[p][1]=f[p][1]+d0;
        G[p]=g[p];
        if(d0<d1)G[p]+=G[fa]-(f[p][0]<f[p][1]?g[p]:0);
    }
    else F[p][0]=f[p][0],F[p][1]=f[p][1],G[p]=g[p];
    for(int j=head[p],i;j;j=nxt[j])if((i=to[j])!=fa)dfs2(i,p);
}
void MoLing_qwq(){
    n=read();
    for(int i=1;i<=n;++i)head[i]=0;
    cnt=0;
    for(int i=1;i<=n;++i)a[i]=read();
    for(int i=1,x,y;i<n;++i){
        x=read(),y=read();
        addedge(x,y);addedge(y,x);
    }
    dfs1(1,0);
    dfs2(1,0);
    ans=0;
	for (int i = 1; i <= n; i++) printf("f[%d]=%d,%d\n", i, f[i][0], f[i][1]);
    for(int i=1;i<=n;++i)if(F[i][0]!=F[i][1])ans=max(ans,G[i]);
    printf("%d\n",ans);
}
int main(){
    // freopen("night.in","r",stdin);
    // freopen("night.out","w",stdout);
    int T;
    T=read();
    while(T--)MoLing_qwq();
    return 0;
}