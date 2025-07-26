#include<bits/stdc++.h>
using namespace std;
const int N=2000005,P=998244353;
int T,n,p[N],k,a[N],x,y,fac[N],inv[N];
int qp(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)res=1ll*res*a%P;
        a=1ll*a*a%P;
        b>>=1;
    }
    return res;
}
int Pl(int n,int m){return 1ll*fac[n]*inv[n-m]%P;}
int main()
{
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    fac[0]=1;
    for(int i=1;i<=1000000;++i)fac[i]=1ll*fac[i-1]*i%P;
    inv[1000000]=qp(fac[1000000],P-2);
    for(int i=1000000;i;--i)inv[i-1]=1ll*inv[i]*i%P;
    cin>>T;
    while(T--)
    {
        cin>>n;k=x=y=0;
        for(int i=1;i<=2*n;++i)
        {
            cin>>p[i];a[i]=i;
        }
        for(int i=1;i<=n;++i)
        {
            if(!p[2*i-1]||!p[2*i])k++;
            if(p[2*i-1]&&p[2*i])a[p[2*i-1]]=a[p[2*i]]=100000000;
        }
        sort(a+1,a+2*n+1);
        int mid=a[k];
        for(int i=1;i<=n;++i)
        {
            if(!p[2*i-1]||!p[2*i])
            {
                if(p[2*i-1]|p[2*i])
                {
                    if((p[2*i-1]|p[2*i])<=mid)x++;
                    else y++;
                }
            }
        }
        cout<<1ll*Pl(k-x,y)*Pl(k-y,x)%P*qp(2,k-x-y)%P*fac[k-x-y]%P*fac[k-x-y]%P<<"\n";
    }
    return 0;
}