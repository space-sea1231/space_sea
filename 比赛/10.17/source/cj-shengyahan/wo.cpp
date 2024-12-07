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
// void solve()
// {
//     int res=0;
//     for(int i=1;i<=n/2;i++)
//         res+=abs(ans[2*i-1]-ans[2*i]);
//     if(res==maxn) tot++;
//     if(res>maxn) tot=1,maxn=res;
//     if(res==5)
//     {
//         for(int i=1;i<=n;i++)
//             cout<<ans[i]<<" ";
//         cout<<'\n';
//     }
//     return ;
// }
// void dfs(int now)
// {
//     if(a[now])
//     {
//         ans[now]=a[now];
//         dfs(now+1);
//         return ;
//     }
//     if(now==n+1)
//     {
//         solve();
//         return ;
//     }
//     for(int i=1;i<=n;i++)
//     {
//         if(!vis[i])
//         {
//             vis[i]=1;
//             ans[now]=i;
//             dfs(now+1);
//             vis[i]=0;
//         }
//     }
//     return ;
// }
inline int ksm(int a,int b,int res=1)
{
    while(b){
        if(b&1) res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
signed main()
{
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
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
            if(a[i]==0) count++;
            p[i]=-1;
        }
        if(count==1 || count==0)
        {
            cout<<1<<'\n';
            continue;
        }
        int t1=1,t2=n;
        for(int i=1;i<=n;i++)
        {
            if(i%2==0 && a[i] && !a[i-1])
            {
                while(vis[t1]) t1++;
                while(vis[t2]) t2--;
                if(abs(t1-a[i])>abs(t2-a[i]))
                    a[i-1]=t1,vis[t1]=1;
                else a[i-1]=t2,vis[t2]=1;
                if(a[i-1]<a[i]) p[i]=p[i-1]=1;
                else p[i]=p[i-1]=0;
            }
            if(i%2==1 && a[i] && !a[i+1])
            {
                while(vis[t1]) t1++;
                while(vis[t2]) t2--;
                if(abs(t1-a[i])>abs(t2-a[i]))
                    a[i+1]=t1,vis[t1]=1;
                else a[i+1]=t2,vis[t2]=1;
                if(a[i]<a[i+1]) p[i]=p[i+1]=1;
                else p[i]=p[i+1]=0;
            }
        }
        // t1=1,t2=n;
        // while(vis[t1]) t1++;
        // while(vis[t2]) t2--;
        int h=0;
        for(int i=1;i<=n;i++)
        {
            if(!a[i])
            {
                h++;
                while(vis[t1]) t1++;
                while(vis[t2]) t2--;
                a[i]=t1,a[i+1]=t2;
                vis[t1]=1,vis[t2]=1;
                if(a[i]<a[i+1]) p[i]=p[i+1]=1;
                else p[i]=p[i+1]=0;
            }
        }
        for(int i=1;i<=n;i++)
            cout<<a[i]<<" ";
        cout<<'\n';
        int zero=0,one=0;
        for(int i=1;i<=n;i+=2)
        {
            if(p[i]==0 && p[i+1]==0)
                zero++;
            else if(p[i]==1 && p[i+1]==1) one++;
            cout<<i<<":"<<p[i]<<" "<<i+1<<":"<<p[i+1]<<' ';
        }
        cout<<h<<" "<<zero<<" "<<one<<'\n';
        int ANS=fac[zero]*fac[one]%mod*ksm(2,h)%mod*fac[h]%mod/**fac[h]%mod*/;
        cout<<ANS<<'\n';
        // dfs(1);
        // cout<<maxn<<" "<<tot<<'\n';
    }
    return 0;
}
