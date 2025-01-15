#include<iostream>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

int n;
int a[400005];

static inline ll calc(){
    ll ret=0;
    int las=1;
    for(int i=2;i<=n;++i){
        if(a[i]<a[i-1]){
            int len=i-las;
            ret+=len*(len-1)/2+len;
            las=i;
        }
    }
    int len=n-las+1;
    ret+=len*(len-1)/2+len;
    return ret;
}

static inline void solve(){
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    ll ans=0;
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            swap(a[i],a[j]);
            ll ret=calc();
            ans=max(ans,ret);
            swap(a[i],a[j]);
        }
    }
    cout<<(ui)ans<<endl;
}

signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}