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

int n,a[400005];
int calc(int ret=1){
    for(int i=2,l=1;i<=n;i++,ret+=++l) if(a[i-1]>a[i]) l=0;
    return ret;
}
signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    int T=read();
    while(T--){
        n=read(); int ans=0; for(int i=1;i<=n;i++) a[i]=read();
        for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++)
            swap(a[i],a[j]),ans=max(ans,calc()),swap(a[i],a[j]);
        printf("%d\n",ans);
    }
    return 0;
}
