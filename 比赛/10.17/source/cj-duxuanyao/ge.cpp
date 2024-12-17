#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define db double
using namespace std;
const int N=20,M=998442353,INF=1e18;
int n,m,p[N][N],s[N],fl;
void sv(){
    cin>>n>>m,fl=0;char op;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            cin>>p[i][j];
    for(int i=1;i<=m;i++)cin>>op,s[i]=op-'0',fl|=s[i];
    if(!fl){printf("NIE\n");return;}
    if(n==1){
        int ans=INF,ct=0,mn=INF,mx=-INF;
        for(int i=1;i<=m;i++)mn=min(mn,p[i][1]),mx=max(mx,p[i][1]);
        for(int i=1;i<=m;i++)if(s[i]){
            if(ans>(p[i][1]-mn)*2+mx-p[i][1])
                ans=(p[i][1]-mn)*2+mx-p[i][1],ct=1;
            else if(ans==(p[i][1]-mn)*2+mx-p[i][1])ct++;
            if(ans>p[i][1]-mn+(mx-p[i][1])*2)
                ans=p[i][1]-mn+(mx-p[i][1])*2,ct=1;
            else if(ans==p[i][1]-mn+(mx-p[i][1])*2)ct++;
        }printf("%lld %lld\n",ans,ct);
        return;
    }
    if(m==1){printf("1 0\n");return;}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    int T=1;cin>>T;while(T--)sv();
    return 0;
}