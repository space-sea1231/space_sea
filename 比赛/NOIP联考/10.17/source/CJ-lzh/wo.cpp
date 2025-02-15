#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5,mod=998244353;
int T,n,a[N],pos[N],tot;
bool vis[N];
#define ll long long
ll frac[N];
void init()
{
    frac[0]=1;
    for(int i=1;i<N;i++) frac[i]=frac[i-1]*i%mod;
}
void solve()
{
    cin>>n;
    fill(vis+1,vis+1+n*2,1);
    for(int i=1;i<=n<<1;i++) cin>>a[i];
    for(int i=1;i<=n<<1;i+=2)
        if(a[i]&&a[i+1]) vis[a[i]]=vis[a[i+1]]=0;
    tot=0;
    for(int i=1;i<=n<<1;i++)
        if(vis[i]) pos[++tot]=i;
    int mid=pos[tot/2];
    int cnt[2]={tot/2,tot/2};
    ll ans=1;
    for(int i=1;i<=n<<1;i+=2)
    {
        if(a[i]&&a[i+1]) continue;
        if(!a[i]&&!a[i+1]) continue;
        if(!a[i]) cnt[a[i+1]>mid]--;
        if(!a[i+1]) cnt[a[i]>mid]--;
    }
    for(int i=1;i<=n<<1;i+=2)
    {
        if(a[i]&&a[i+1]) continue;
        if(!a[i]&&!a[i+1]) ans=ans*2%mod;
    }
    cout<<ans*frac[cnt[0]]%mod*frac[cnt[1]]%mod<<'\n';
}
signed main()
{
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>T; init();
    while(T--) solve();
}