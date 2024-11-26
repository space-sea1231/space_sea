#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxx=2e6,mod=998244353;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int t,n;
int a[2000005],vis[2000005],p[2000005],fac[2000005];
signed main()
{
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    t=read();
    fac[0]=1,p[0]=1;
    for(int i=1;i<=maxx;i++)
        fac[i]=fac[i-1]*i%mod,p[i]=p[i-1]*2%mod;
    while(t--)
    {
        n=read();
        int tot=0,cnt=0,num=0;
        for(int i=1;i<=2*n;i++)
        {
            a[i]=read();
            if(i%2==0)
            {
                if(a[i]&&a[i-1]) vis[a[i]]=vis[a[i-1]]=1;
                if(!a[i]||!a[i-1])
                {
                    tot+=2;
                    vis[a[i]]=vis[a[i-1]]=-1;
                    if(a[i]||a[i-1])cnt++;
                }
            }
        }
        int sum=0;
        for(int i=1;i<=2*n;i++)
        {
            num+=(vis[i]==-1);
            if(vis[i]<1)sum++;
            if(sum>=tot/2) 
            {
                sum=i;
                break;
            }
        }
        for(int i=1;i<=2*n;i++) vis[i]=0;
        int ans=fac[tot/2-num]*fac[tot/2-(cnt-num)]%mod*p[tot/2-cnt]%mod;
        cout<<ans<<endl;
    }
}