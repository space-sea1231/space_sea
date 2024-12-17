#include<bits/stdc++.h>
#define int long long
#define pc putchar
using namespace std;
void read(int &p){
    int res=0,fh=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') fh=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
    p=res*fh;
}
void prt(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) prt(x/10);
    putchar(x%10+'0');
}
const int N=2e6+10;
const int inf=0x7fffffffffffffff;
const int MOD=998244353;
int T,n,a[N],vis[N],b[N],tot;
int powe[N],pow2[N];
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    powe[0]=1,pow2[0]=1;
    for(int i=1;i<=2e6;i++) powe[i]=powe[i-1]*i%MOD;
    for(int i=1;i<=2e6;i++) pow2[i]=pow2[i-1]*2%MOD;
    read(T);
    while(T--){
        tot=0;
        read(n);n*=2;
        for(int i=1;i<=n;i++) read(a[i]),vis[i]=0;
        for(int i=1;i<=n;i+=2) if(a[i]!=0&&a[i+1]!=0) vis[a[i]]=vis[a[i+1]]=1;
        for(int i=1;i<=n;i++) if(!vis[i]) b[++tot]=i;
        int half=tot/2;
        int lh=b[half],rh=b[half+1];
        int mx=0,mn=0,fre=0;
        for(int i=1;i<=n;i+=2){
            if(a[i]!=0&&a[i+1]!=0) continue;
            if(a[i]==0&&a[i+1]==0) {fre++;continue;}
            if(a[i]==0){if(a[i+1]<=lh) mx++;else mn++;continue;}
            if(a[i+1]==0){if(a[i]<=lh) mx++;else mn++;continue;}
        }
        // prt(mx);pc(' ');prt(mn);pc(' ');prt(fre);pc('\n');
        int ans=powe[mx+fre]*powe[mn+fre]%MOD*pow2[fre]%MOD;
        prt(ans);pc('\n');
    }
    return 0;
}