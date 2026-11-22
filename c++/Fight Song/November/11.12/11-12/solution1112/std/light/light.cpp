#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200004
int n,a[N];ll c[N],f[N],y[N],ans;
int main(){
    freopen("light.in","r",stdin);
    freopen("light.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%lld",&c[i]);
    y[n]=c[n];
    for(int i=n-1;i>=1;--i)y[i]=max(y[i+1],c[i]);
    int p=n;
    while(p>1&&c[p]<0)--p;
    for(int i=1;i<=p;++i)f[i]=(c[i]<0?0:i-1);
    int h=0;
    for(int i=p;i>=1;--i)if(c[i]>=0)a[i]=++h;
    for(int i=1;i<=p;++i)if(c[i]<0)a[i]=++h;
    int t=0;
    for(int i=1;i<=p;++i)if(a[i]==p)t=i;
    while(p<n){
        int q=p+1;
        while(c[q]!=y[q])++q;
        a[q]=a[t],f[q]=q-p,++a[t];
        for(int i=p+1;i<q;++i)a[i]=a[t]+i-p,f[i]=0;
        if(p+1<q)t=q-1;
        p=q;
    }
    ans=0;
    for(int i=1;i<=n;++i)ans+=c[i]*f[i];
    printf("%lld\n",ans);
    for(int i=1;i<=n;++i)printf("%d%c",a[i],i==n?'\n':' ');
    return 0;
}