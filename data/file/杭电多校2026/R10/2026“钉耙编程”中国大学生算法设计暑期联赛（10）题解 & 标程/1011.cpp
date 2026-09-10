#include<bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;
const int maxn=1e5+10;
int q,x,p[10],cnt;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
    return x*f;
}
inline void solve(){
    for(int k=1;k<=13;k++){
        int x=2*k*k*k;
        if(__builtin_popcountll(x)==k)p[++cnt]=x;
        if(__builtin_popcountll(x+1)==k)p[++cnt]=x+1;
    }
    sort(p+1,p+cnt+1);
    q=read();
    while(q--){
        x=read();
        int pos=lower_bound(p+1,p+cnt+1,x)-p;
        if(pos>cnt)puts("-1");
        else printf("%lld\n",p[pos]);
    }
}
signed main(){
    solve();
    return 0;
}
