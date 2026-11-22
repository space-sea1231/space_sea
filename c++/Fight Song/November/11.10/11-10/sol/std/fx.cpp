#include<iostream>

#define int long long

using namespace std;

const int lim=1e7;
const int mod=998244353;

static inline int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1)
            ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
const int _2=qpow(2,mod-2);
int fac[lim+5];
int invfac[lim+5];
static inline int C(int n,int m){
    if(n<0||m<0||n<m)
        return 0;
    return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

int n;
int a[10000005];
bool vis[10000005];

signed main(){
    freopen("fx.in","r",stdin);
    freopen("fx.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    fac[0]=invfac[0]=1;
    for(int i=1;i<=lim;++i)
        fac[i]=fac[i-1]*i%mod;
    invfac[lim]=qpow(fac[lim],mod-2);
    for(int i=lim;i>1;--i)
        invfac[i-1]=invfac[i]*i%mod;
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    int p=n;
    while(p&&a[1]==a[p])
        --p;
    if(!p){
        cout<<fac[n]<<endl;
        return 0;
    }
    int m=0;
    for(int i=1;i<=p;++i){
        if(a[i]!=a[i-1]){
            if(vis[a[i]]){
                cout<<0<<endl;
                return 0;
            }
            ++m;
            vis[a[i]]=true;
        }
    }
    if(m==n){
        cout<<1<<endl;
        return 0;
    }
    bool ok=false;
    a[n+1]=a[1],a[n+2]=a[2];
    for(int i=1;i<=n;++i){
        if(a[i]==a[i+1]&&a[i+1]==a[i+2]){
            ok=true;
            break;
        }
    }
    if(!ok){
        cout<<0<<endl;
        return 0;
    }
    int ans=m*fac[n-m]%mod*C(n,m)%mod;
    ans-=n*m%mod*fac[n-m-1]%mod*C(n-2*(n-m)-1,n-m-1)%mod;
    if(n>4&&!(n&1)&&m==n-2)
        ans=ans*_2%mod;
    ans=(ans%mod+mod)%mod;
    cout<<ans<<endl;
    return 0;
}