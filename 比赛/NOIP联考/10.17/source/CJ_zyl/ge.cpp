#include<bits/stdc++.h>
#define se second
#define fi first
using namespace std;
using pii=pair<int,int>;
using ll=long long;
const int P=998442353;
const int N=3.2e6+3;
template<class T1,class T2>void add(T1 &x,T2 y){if((x+=y)>=P)x-=P;}
template<class T1,class T2>void dlt(T1 &x,T2 y){if((x-=y)<0)x+=P;}
ll fp(ll a,int b=P-2){
    ll ans=1;
    for(;b;b>>=1,a=a*a%P)
        if(b&1)ans=ans*a%P;
    return ans;
}
int fc[N],inv[N];
ll C(int n,int m){if(n<m)return 0;return (ll)fc[n]*inv[m]%P*inv[n-m]%P;}
const int INF=0x3f3f3f3f;
int n,m;
int p[20][20],f[1<<16][16],g[1<<16][16];
pii dis[20][20];
pii calc(int x,int y){
    int ans=1,sum=0;
    for(int i=1;i<=m;++i){
        int k=abs(p[x][i]-p[y][i]);
        ans=ans*C(sum+k,k)%P;
        sum+=k;
    }
    return {ans,sum};
}
void solve(){
    int x,y,z,u,v,w;
    cin>>m>>n;
    for(int i=0;i<n;++i)
        for(int j=1;j<=m;++j)
            cin>>p[i][j];
    int ans=INF,cnt=0,lim=(1<<n)-1;
    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
            dis[i][j]=dis[j][i]=calc(i,j);
    for(int i=0;i<1<<n;++i)
        for(int j=0;j<n;++j)
            f[i][j]=INF,g[i][j]=0;
    for(int i=0;i<n;++i){
        cin>>x;if(!x)continue;
        f[1<<i][i]=0;g[1<<i][i]=1;
    }
    for(int s=0;s<1<<n;++s)
        for(int i=0;i<n;++i)if((s&1<<i)&&f[s][i]!=INF)
            for(int j=0;j<n;++j)if(!(s&1<<j)){
                int k=s|(1<<j);auto w=dis[i][j];
                int d=w.se+f[s][i],cnt=(ll)g[s][i]*w.fi%P;
                if(f[k][j]>d)f[k][j]=d,g[k][j]=cnt;
                else if(f[k][j]==d)add(g[k][j],cnt);
            }
    for(int i=0;i<n;++i)
        if(ans>f[lim][i])ans=f[lim][i],cnt=g[lim][i];
        else if(ans==f[lim][i])add(cnt,g[lim][i]);
    if(ans==INF)puts("NIE");
    else printf("%d %d\n",ans,cnt);
}
int main(){
    int u,v,w,x,y,z;
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    fc[0]=inv[0]=1;
    for(int i=1;i<N;++i)fc[i]=(ll)fc[i-1]*i%P;
    inv[N-1]=fp(fc[N-1]);
    for(int i=N-2;i;--i)inv[i]=(i+1ll)*inv[i+1]%P;
    int T;for(cin>>T;T--;)solve();
    return 0;
}