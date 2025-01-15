#include <bits/stdc++.h>
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

inline static int read(){
    int sum=0,neg=0,ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=sum*10+(ch^48),ch=getchar();
    return neg?-sum:sum;
}

constexpr int mod=998244353;
int a[2000005];
bool v1[2000005];
bool v2[2000005];
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    int T=read();
    while(T--){
        int n=read(),ct=n; ll ans=1;
        for(int i=1;i<=2*n;i++) v1[a[i]=read()]=1;
        for(int i=1;i<=n;i++){
            if(a[i*2-1] && a[i*2]) ct--,v2[a[i*2-1]]=v2[a[i*2]]=1;
            else if(!a[i*2-1] && !a[i*2]) ans=ans*2%mod;
        }
        int i=1,p,x;
        for(p=ct,x=0;p;i++){
            if(v2[i]) continue; p--;
            if(!v1[i]) ans=ans*++x%mod;
        }
        for(p=ct,x=0;p;i++){
            if(v2[i]) continue; p--;
            if(!v1[i]) ans=ans*++x%mod;
        }
        memset(v1+1,0,2*n),memset(v2+1,0,2*n);
        printf("%lld\n",ans);
    }
    return 0;
}
