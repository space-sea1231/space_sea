#include<iostream>
#include<algorithm>

#define int long long

using namespace std;

const int lim=1e6;
const int mod=998244353;

int pw[lim+5];
int fac[lim+5];

int n;
int a[1000005];
int b[1000005];
int blk[2000005],len;
int mp[2000005];

static inline void solve(){
    cin>>n;
    len=0;
    for(int i=1;i<=n;++i){
        cin>>a[i]>>b[i];
        if(a[i]&&b[i]){
            blk[++len]=a[i];
            blk[++len]=b[i];
            continue;
        }
    }
    sort(blk+1,blk+len+1);
    int cnt=0,ptr=1;
    for(int i=1;i<=2*n;++i){
        if(ptr<=len&&blk[ptr]==i)
            continue;
        mp[i]=++cnt;
    }
    int up=0,dn=0,free=0;
    for(int i=1;i<=n;++i){
        if(a[i]&&b[i])
            continue;
        int x=mp[a[i]];
        int y=mp[b[i]];
        if(!x&&!y){
            ++up;++dn;++free;
            continue;
        }
        int z=x|y;
        if(z<=n-len/2)
            ++dn;
        else
            ++up;
    }
    int ans=fac[up]*fac[dn]%mod*pw[free]%mod;
    cout<<ans<<endl;
}

signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    pw[0]=fac[0]=1;
    for(int i=1;i<=lim;++i){
        pw[i]=pw[i-1]*2%mod;
        fac[i]=fac[i-1]*i%mod;
    }
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}