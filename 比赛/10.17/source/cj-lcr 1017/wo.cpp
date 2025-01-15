#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr first
#define sc second
inline int read(){
    int res=0,f=1;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {res=res*10+(c-'0');c=getchar();}
    return res*f;
}
const int N=2e6+5,M=998244353;
int T,n,a[N],t[N],fac[N],p[N];
vector<int>e;
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    T=read();
    fac[0]=1,p[0]=1;
    for (int i=1;i<N;i++){
        fac[i]=fac[i-1]*i%M;
        p[i]=p[i-1]*2%M;
    }
    while (T--){
        n=read(),e.clear();
        for (int i=1;i<=(n<<1);i++)
            a[i]=read(),t[i]=0;
        int c=0,d=0,c1=0,c2=0;
        for (int i=1;i<=n;i++){
            if (a[(i<<1)-1]!=0&&a[i<<1]!=0)
                c++,t[a[(i<<1)-1]]=1,t[a[i<<1]]=1;
            else if (!(a[(i<<1)-1]==0&&a[i<<1]==0))
                e.push_back(max(a[(i<<1)-1],a[i<<1]));
        }
        for (int i=1;i<=(n<<1);i++){
            if (t[i]==1){
                t[i]=0;
                continue;
            }
            d++;
            if (d<=n-c) t[i]=1;
            else t[i]=2;
        }
        for (auto i:e){
            if (t[i]==1) c1++;
            else c2++;
        }
        int ans=p[n-c-c1-c2];
        ans=(ans*fac[n-c-c1])%M;
        ans=(ans*fac[n-c-c2])%M;
        cout<<ans<<'\n';
    }
    return 0;
}