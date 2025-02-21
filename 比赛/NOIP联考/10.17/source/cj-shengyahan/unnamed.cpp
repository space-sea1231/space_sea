#include <bits/stdc++.h>
#define int long long 
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
const int MAXN=2e6+10,mod=998244353;
int T,n,maxn,tot,a[MAXN],ans[MAXN],vis[MAXN],p[MAXN],fac[MAXN];
void solve()
{
    int res=0;
    for(int i=1;i<=n/2;i++)
        res+=abs(ans[2*i-1]-ans[2*i]);
    if(res==maxn) tot++;
    if(res>maxn) tot=1,maxn=res;
    return ;
}
void dfs(int now)
{
    if(a[now])
    {
        ans[now]=a[now];
        dfs(now+1);
        return ;
    }
    if(now==n+1)
    {
        solve();
        return ;
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            vis[i]=1;
            ans[now]=i;
            dfs(now+1);
            vis[i]=0;
        }
    }
    return ;
}
signed main()
{
    fac[0]=1;
    for(int i=1;i<=2e6;i++)
        fac[i]=fac[i-1]*i%mod;
    T=read();
    while(T--)
    {
        n=read();
        n*=2;
        int count=0;
        for(int i=1;i<=n;i++)
            vis[i]=0;
        for(int i=1;i<=n;i++)
        {
            a[i]=read(),vis[a[i]]=1;
            if(!a[i]) count++;
            p[i]=-1;
        }
        if(count==1 || count==0)
        {
            cout<<1<<'\n';
            continue;
        }
        dfs(1);
        cout<<maxn<<" "<<tot<<'\n';
    }
    return 0;
}