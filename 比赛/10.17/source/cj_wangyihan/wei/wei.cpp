#include<bits/stdc++.h>
#define int long long 
using namespace std;
int t,mod;
int p[400005];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
signed main()
{
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    mod=1;
    for(int i=1;i<=32;i++)
        mod=mod*2; 
    t=read();
    while(t--)
    {
        int manx=0;
        int n=read();
        for(int i=1;i<=n;i++)
            p[i]=read();
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
            {
                int ans=0;
                swap(p[i],p[j]);
                for(int l=1;l<=n;l++)
                {
                    int tot=1;
                    for(int r=l+1;r<=n;r++)
                        if(p[r]>p[r-1]) tot++;
                        else break;
                    ans+=tot;
                }
                manx=max(manx,ans);
                swap(p[i],p[j]);
            }
        cout<<manx%mod<<endl;
    }
}