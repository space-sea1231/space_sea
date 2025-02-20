#include <bits/stdc++.h>
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

inline static int read(){
    int sum=0,neg=0,ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=sum*10+(ch^48),ch=getchar();
    return neg?-sum:sum;
}

constexpr int mod=998442353,N=3200000;
int power(ll a,int b=mod-2,ll ret=1){
    while(b){
        if(b&1) ret=ret*a%mod;
        a=a*a%mod,b>>=1;
    } return ret;
}
int n,m,M,fac[N+5],inv[N+5],p[16][16];
struct Dat{
    int x,c;
    void upd(Dat t){if(t.x<x) *this=t; else if(t.x==x) c=(c+t.c)%mod;}
    Dat operator+(Dat t)const{return {x+t.x,(ll)c*t.c%mod};}
}f[16][1<<16],w[16][16];
signed main(){
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    int T=read(); *fac=*inv=1;
    for(int i=1;i<=N;i++) fac[i]=(ll)fac[i-1]*i%mod; inv[N]=power(fac[N]);
    for(int i=N-1;i;i--) inv[i]=inv[i+1]*(i+1ll)%mod;
    while(T--){
        m=read(),n=read(),M=(1<<n)-1;
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) p[i][j]=read();
        for(int i=0;i<n;i++) memset(f[i],0x3f,8<<n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++) if(i!=j){
                w[i][j]={0,1};
                for(int k=0,t;k<m;k++){
                    t=abs(p[i][k]-p[j][k]),w[i][j].x+=t;
                    w[i][j].c=(ll)w[i][j].c*inv[t]%mod;
                } w[i][j].c=(ll)w[i][j].c*fac[w[i][j].x]%mod;
            }
        } bool flag=1;
        for(int i=0;i<n;i++) if(read()==1) f[i][1<<i]={0,1},flag=0;
        if(flag){puts("NIE"); continue;}
        for(int i=1;i<=M;i++) for(int t=i;t;t^=t&-t)
            for(int j=__builtin_ctz(t),t=M^i,k;t;t^=t&-t)
                k=__builtin_ctz(t),f[k][i|(t&-t)].upd(f[j][i]+w[j][k]);
        Dat ans={INT_MAX,0};
        for(int i=0;i<n;i++) ans.upd(f[i][M]);
        printf("%d %d\n",ans.x,ans.c);
    } return 0;
}
