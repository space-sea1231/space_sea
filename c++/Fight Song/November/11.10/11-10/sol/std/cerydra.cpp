#include<iostream>

#define int long long

using namespace std;

const int lim=1e6;
const int mod=1e9+7;

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
int fac[lim+5];
int invfac[lim+5];
static inline int C(int n,int m){
    return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

int n;
int a[500005];

static inline int solve(int l,int r){
    if(l>r)
        return 1;
    if(l==r)
        return a[l]==1;
    auto check=[&](int x){
        return a[x]==(x-l+1)*(r-x+1);
    };
    int p1=l,p2=r;
    while(p1<p2){
        if(check(p1))
            return solve(l,p1-1)*solve(p1+1,r)%mod*C(r-l,p1-l)%mod;
        if(check(p2))
            return solve(l,p2-1)*solve(p2+1,r)%mod*C(r-l,p2-l)%mod;
        ++p1,--p2;
    }
    if(p1==p2&&check(p1))
        return solve(l,p1-1)*solve(p1+1,r)%mod*C(r-l,p1-l)%mod;
    return 0;
}

static inline void solve(){
    cin>>n;
    int sum=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        sum+=a[i];
    }
    if(sum!=n*(n+1)/2){
        cout<<"0\n";
        return;
    }
    cout<<solve(1,n)<<'\n';
}

signed main(){
    freopen("cerydra.in","r",stdin);
    freopen("cerydra.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    fac[0]=invfac[0]=1;
    for(int i=1;i<=lim;++i)
        fac[i]=fac[i-1]*i%mod;
    invfac[lim]=qpow(fac[lim],mod-2);
    for(int i=lim;i>1;--i)
        invfac[i-1]=invfac[i]*i%mod;
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}