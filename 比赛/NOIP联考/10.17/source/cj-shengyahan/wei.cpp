#include <bits/stdc++.h>
#define int long long 
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
const int MAXN=4e5+10;
int T,n,ans,a[MAXN],dp[MAXN];
signed main()
{
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;i++)
            a[i]=read();
        for(int x=1;x<=n;x++)
        {
            for(int y=x+1;y<=n;y++)
            {
                swap(a[x],a[y]);
                for(int i=1;i<=n;i++)
                    dp[i]=1;
                int res=0;
                for(int i=2;i<=n;i++)
                {
                    if(a[i]>a[i-1])
                        dp[i]=dp[i-1]+1;
                    res+=dp[i];
                }
                ans=max(ans,res+1);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}