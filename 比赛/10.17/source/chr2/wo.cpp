#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int mod=998244353;
int ksm(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
bool book[N*2];
int jc[N],inv[N];
int A(int x,int y){return jc[x]*inv[x-y]%mod;}
void run()
{
    int n;
    cin>>n;
    inv[0]=inv[1]=jc[0]=jc[1]=1;
    for(int i=2;i<=n;i++) jc[i]=jc[i-1]*i%mod;
    for(int i=2;i<=n;i++) inv[i]=mod-mod/i*inv[mod%i]%mod;
    for(int i=2;i<=n;i++) inv[i]=inv[i-1]*inv[i]%mod;
    int cnt0=0,cnt1=0;
    vector<int> res;
    for(int i=0;i<=2*n;i++) book[i]=0;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        cin>>x>>y;
        if(x&&y) book[x]=book[y]=1;
        else if(!x&&!y) cnt0++;
        else res.push_back(x+y),cnt1++;
    }
    int p=0;
    for(int i=1;i<=cnt0+cnt1;i++) 
    {
        p++;
        while(book[p]) p++;
    }
    int zero=0,one=0;
    for(int i:res) 
        if(i<=p) zero++;
        else one++;
    int ans=A(cnt0+cnt1-one,zero)*A(cnt0+cnt1-zero,one)%mod;
    ans=ans*jc[cnt0]%mod*jc[cnt0]%mod*ksm(2,cnt0)%mod;
    cout<<ans<<'\n';
}
signed main()
{
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) run();
	return 0;
}
