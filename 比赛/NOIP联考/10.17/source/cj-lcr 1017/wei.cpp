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
const int N=4e5+5;
mt19937 rnd(time(0));
int T,n,a[N];
int calc(int x,int y){
    swap(a[x],a[y]);
    int res=0,l=1;
    for (int i=1;i<=n;i++){
        if (a[i]<a[i-1]) l=i;
        res+=(i-l+1);
    }
    swap(a[x],a[y]);
    return res;
}
signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    T=read();
    while (T--){
        n=read();
        for (int i=1;i<=n;i++)
            a[i]=read();
        int ans=calc(1,1);
        if (n<=300){
            for (int i=1;i<=n;i++)
                for (int j=i+1;j<=n;j++)
                    ans=max(ans,calc(i,j));
        }
        else{
            for (int _=1;_<=100000000/T;_++){
                int x=rnd()%n+1,y=rnd()%n+1;
                ans=max(ans,calc(x,y));
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}