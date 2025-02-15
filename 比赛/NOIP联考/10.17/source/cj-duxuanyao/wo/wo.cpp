#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define db double
using namespace std;
const int N=2e6+5,M=998244353,INF=1e18;
int n,ans,a[N],jc[N],p0,pl,pr;
int qp(int x,int y){
    int res=1;
    while(y){
        if(y&1)res=res*x%M;
        x=x*x%M,y>>=1;
    }return res;
}
void sv(){
    cin>>n,n<<=1,pl=pr=p0=0;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i+=2){
        if(a[i]&&a[i+1])continue;
        if(a[i]+a[i+1]==0){p0++;continue;}
        if(a[i]+a[i+1]<=n/2)pl++;
        else pr++;
    }printf("%lld\n",jc[p0+pl]*jc[p0+pr]%M*qp(2,p0)%M);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    jc[0]=1;
    for(int i=1;i<N;i++)jc[i]=jc[i-1]*i%M;
    int T=1;cin>>T;while(T--)sv();
    return 0;
}