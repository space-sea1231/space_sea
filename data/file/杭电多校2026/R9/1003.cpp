#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define pb push_back
using namespace std;
const int N=510,inf=0x3f3f3f3f,mod=998244353;
int n,m,s,t;
vector<int>g[N],f[N],dep[N];
int dis[2][N],tag[N];
pii dp[N][N];
bitset<N>b[N];
void dij(int *dis,int s)
{
    for(int i=1;i<=n;i++)dis[i]=inf;
    dis[s]=1;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(auto y:g[x])if(dis[y]==inf)
            dis[y]=dis[x]+1,q.push(y);
    }
}
void solve()
{
    cin>>n>>m>>s>>t;
    for(int i=0;i<=n;i++)
    {
        g[i].clear(),dep[i].clear(),b[i].reset(),f[i].clear();
        b[i][i]=1;
        tag[i]=0;
    }
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[i][j]={inf,0};
    for(int i=1;i<=m;i++)
    {
        int x,y;cin>>x>>y;
        g[x].push_back(y),g[y].push_back(x);
        b[x][y]=b[y][x]=1;
    }
    dij(dis[0],s);dij(dis[1],t);
    int d=dis[0][t];
    for(int i=1;i<=n;i++)if(dis[0][i]+dis[1][i]==d+1)
        tag[i]=1,dep[dis[0][i]].push_back(i);
    for(int x=1;x<=n;x++)if(tag[x])for(auto y:g[x])if(tag[y]&&dis[0][y]==dis[0][x]+1)f[x].push_back(y);
    dep[0].push_back(0);
    f[0].push_back(s);
    dp[0][s]={(int)b[s].count(),1};
    for(int i=1;i<d;i++)
        for(auto x:dep[i-1])
            for(auto y:f[x])if(dp[x][y].fi!=inf)
                for(auto z:f[y])
                {
                    int v=dp[x][y].fi+(int)((b[z]&(~(b[x]|b[y]))).count());
                    if(v<dp[y][z].fi)dp[y][z]={v,dp[x][y].se};
                    else if(v==dp[y][z].fi)dp[y][z]={v,(dp[y][z].se+dp[x][y].se)%mod};
                }
    int ans=inf,c=0;
    for(auto x:dep[d-1])for(auto y:f[x])if(y==t)
    {
        if(ans>dp[x][y].fi)ans=dp[x][y].fi,c=dp[x][y].se;
        else if(ans==dp[x][y].fi)c=(c+dp[x][y].se)%mod;
    }
    cout<<ans<<' '<<c<<endl;
}
signed main()
{
//   freopen("hdu.in","r",stdin);
//   freopen("hdu.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _;cin>>_;while(_--)solve();
    return 0;
}
