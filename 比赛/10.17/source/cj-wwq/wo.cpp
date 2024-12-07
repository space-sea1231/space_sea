#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,M=998244353;
int T,fac[N],inv[N],n,cnt,p[N],a[N];
bool v[N],vis[N];
int qpow(int x,int y,int res=1){
    while(y){
        if(y&1)res=1ll*res*x%M;
        x=1ll*x*x%M,y>>=1;
    } return res;
}
inline static int read(){
    char ch=getchar();
    int x=0,fl=0;
    while(!isdigit(ch))fl|=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return fl?-x:x;
}
int C(int x,int y){return 1ll*fac[x]*inv[y]%M*inv[x-y]%M;}
signed main(){
    ios::sync_with_stdio(false);
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    int i,j,k,l,r,x,y,z;
    T=read(),fac[0]=inv[0]=1;
    for(i=1;i<N;++i)fac[i]=1ll*fac[i-1]*i%M;
    inv[N-1]=qpow(fac[N-1],M-2);
    for(i=N-2;i;--i)inv[i]=inv[i+1]*(i+1ll)%M;
    while(T--){
        n=read(),cnt=l=r=0;
        for(i=1;i<=2*n;++i){
            p[i]=read(),v[p[i]]=true;
            if(!(i&1)&&p[i]&&p[i-1])vis[p[i]]=vis[p[i-1]]=true;
        } for(i=1;i<=2*n;++i)if(!vis[i])a[++cnt]=i;
        for(i=1,cnt/=2;i<=a[cnt];++i)if(v[i]&&!vis[i])l++;
        for(i=a[cnt]+1;i<=2*n;++i)if(v[i]&&!vis[i])r++; 
        printf("%lld\n",1ll*qpow(2,cnt-l-r)*fac[cnt-l-r]%M*fac[cnt-l-r]%M*C(cnt-l,r)%M*C(cnt-r,l)%M*fac[r]%M*fac[l]%M);
        for(i=1;i<=2*n;++i)v[i]=vis[i]=0;
    }
    return 0;
}