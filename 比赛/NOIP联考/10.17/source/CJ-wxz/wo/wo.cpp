#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e6+5,mod=998244353;
int n,a[maxn],power[maxn],fac[maxn],vis[maxn];
vector<int> v;
void solve()
{
    int cnt1=0,cnt2=0,cnt3=0;
    cin>>n;
    for(int i=1;i<=2*n;i++) vis[i]=0;
    for(int i=1;i<=2*n;i+=2)
    {
        cin>>a[i]>>a[i+1];
        cnt3+=(a[i]==0&&a[i+1]==0);
        if(a[i]!=0&&a[i+1]!=0) vis[a[i]]=vis[a[i+1]]=1;
    }
    v.clear(),v.push_back(0);
    for(int i=1;i<=2*n;i++)
        if(vis[i]==0) v.push_back(i);
    int p=v[v.size()/2];
    // cout<<p<<"\n";
    for(int i=1;i<=2*n;i+=2)
    {
        if(a[i]==0&&a[i+1]==0){cnt1++;cnt2++;continue;}
        if(a[i]!=0&&a[i+1]!=0) continue;
        if(a[i]==0) cnt1+=(a[i+1]>p),cnt2+=(a[i+1]<=p);
        if(a[i+1]==0) cnt1+=(a[i]>p),cnt2+=(a[i]<=p);
    }
    // cout<<cnt1<<' '<<cnt2<<"\n";
    cout<<fac[cnt1]*fac[cnt2]%mod*power[cnt3]%mod<<"\n";
}
signed main()
{
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    fac[0]=power[0]=1;
    for(int i=1;i<=maxn-5;i++) fac[i]=fac[i-1]*i%mod,power[i]=power[i-1]*2%mod;
    int t;
    cin>>t;
    while(t--) solve();
}