#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("-O2")
#pragma GCC optimize("-O3")
#pragma GCC optimize("inline")
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define ll long long
#define N 100005
using namespace std;
int n,m,opt,x,y,p,l[N],r[N],bel[N];
int c,a[N],add[N],mul[N],s[N];
void push_down(int x)
{
    for (int i=l[x];i<=r[x];i++)
        a[i]=((ll)a[i]*mul[x]+add[x])%p;
    add[x]=0,mul[x]=1;
}
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]),a[i]%=p;
    int lar=(int)sqrt(n);
    for (int i=1;i<=n;i++)
    {
        bel[i]=(i+lar-1)/lar;
        if (bel[i]!=bel[i-1])
            l[bel[i]]=i;
        r[bel[i]]=i;
        s[bel[i]]=(s[bel[i]]+a[i])%p;
    }
    for (int i=1;i<=bel[n];i++)
        add[i]=0,mul[i]=1;
    while (m --> 0)//
    {
        scanf("%d%d%d",&opt,&x,&y);
        int rx=bel[x],ry=bel[y];
        if (opt==1)
        {
            scanf("%d",&c);
            if (rx==ry)
            {
                push_down(rx);
                for (int i=x;i<=y;i++)
                    s[rx]=((ll)s[rx]+(ll)a[i]*(c-1)%p),a[i]=(ll)a[i]*c%p;
                continue;
            }
            push_down(rx),push_down(ry);
            for (int i=x;i<=r[rx];i++)
                s[rx]=((ll)s[rx]+(ll)a[i]*(c-1)%p),a[i]=(ll)a[i]*c%p;
            for (int i=rx+1;i<=ry-1;i++)
                add[i]=(ll)add[i]*c%p,mul[i]=(ll)mul[i]*c%p,s[i]=(ll)s[i]*c%p;
            for (int i=l[ry];i<=y;i++)
                s[ry]=((ll)s[ry]+(ll)a[i]*(c-1)%p),a[i]=(ll)a[i]*c%p;
        } else
        if (opt==2)
        {
            scanf("%d",&c);
            if (rx==ry)
            {
                push_down(rx);
                for (int i=x;i<=y;i++)
                    a[i]=(a[i]+c)%p;
                s[rx]=((ll)s[rx]+(ll)c*(y-x+1))%p;
                continue;
            }
            push_down(rx),push_down(ry);
            for (int i=x;i<=r[rx];i++)
                a[i]=(a[i]+c)%p;
            s[rx]=((ll)s[rx]+(ll)c*(r[rx]-x+1))%p;
            for (int i=rx+1;i<=ry-1;i++)
                add[i]=(add[i]+c)%p,s[i]=((ll)s[i]+(ll)c*(r[i]-l[i]+1))%p;
            for (int i=l[ry];i<=y;i++)
                a[i]=(a[i]+c)%p;
            s[ry]=((ll)s[ry]+(ll)c*(y-l[ry]+1))%p;
        } else
        {
            int ans=0;
            if (rx==ry)
            {
                for (int i=x;i<=y;i++)
                    ans=((ll)ans+(ll)mul[rx]*a[i]+add[rx])%p;
                ans=(ans%p+p)%p;
                printf("%d\n",ans);
                continue;
            }
            for (int i=x;i<=r[rx];i++)
                ans=((ll)ans+(ll)mul[rx]*a[i]+add[rx])%p;
            for (int i=rx+1;i<=ry-1;i++)
                ans=(ans+s[i])%p;
            for (int i=l[ry];i<=y;i++)
                ans=((ll)ans+(ll)mul[ry]*a[i]+add[ry])%p;
            ans=(ans%p+p)%p;
            printf("%d\n",ans);
        }
    }
    return 0;
}
