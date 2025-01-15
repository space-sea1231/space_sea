#include<iostream>
#include<queue>

#define int long long

using namespace std;

const int lim=4e6;
const int mod=998442353;
const int inf=1e18;

static inline int qpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1)
            ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
int fac[lim+5];
int invfac[lim+5];

int n,m;

int a[20][20];
int dist[20][20];
int cc[20][20];

bool vis[100005][20];
int dis[100005][20];
int cnt[100005][20];

void solve(){
    cin>>n>>m;
    for(int i=1;i<=m;++i)
        for(int j=1;j<=n;++j)
            cin>>a[i][j];
    for(int i=1;i<=m;++i){
        for(int j=1;j<=m;++j){
            dist[i][j]=0;
            for(int k=1;k<=n;++k)
                dist[i][j]+=abs(a[i][k]-a[j][k]);
            cc[i][j]=fac[dist[i][j]];
            for(int k=1;k<=n;++k)
                cc[i][j]=cc[i][j]*invfac[abs(a[i][k]-a[j][k])]%mod;
        }
    }
    int ed=(1<<m)-1;
    for(int i=0;i<=ed;++i){
        for(int j=1;j<=m;++j){
            vis[i][j]=false;
            dis[i][j]=inf;
            cnt[i][j]=0;
        }
    }
    queue<pair<int,int>>q;
    for(int i=1;i<=m;++i){
        int x;
        cin>>x;
        if(x==1){
            q.push({(1<<(i-1)),i});
            vis[(1<<(i-1))][i]=true;
            dis[(1<<(i-1))][i]=0;
            cnt[(1<<(i-1))][i]=1;
        }
    }
    while(!q.empty()){
        auto tp=q.front();
        q.pop();
        int x=tp.first;
        int y=tp.second;
        vis[x][y]=false;
        for(int i=1;i<=m;++i){
            if((x>>(i-1))&1)
                continue;
            int xx=x|(1<<(i-1));
            int dd=dis[x][y]+dist[y][i];
            int ww=cnt[x][y]*cc[y][i]%mod;
            if(dd<dis[xx][i]){
                dis[xx][i]=dd;
                cnt[xx][i]=ww;
                if(!vis[xx][i]){
                    vis[xx][i]=true;
                    q.push({xx,i});
                }
            }else if(dd==dis[xx][i])
                cnt[xx][i]=(cnt[xx][i]+ww)%mod;
        }
    }
    int ans1=inf,ans2=0;
    for(int i=1;i<=m;++i){
        if(dis[ed][i]<ans1){
            ans1=dis[ed][i];
            ans2=cnt[ed][i];
        }else if(dis[ed][i]==ans1)
            ans2=(ans2+cnt[ed][i])%mod;
    }
    if(ans1==inf)
        cout<<"NIE\n";
    else
        cout<<ans1<<' '<<ans2<<'\n';
}

signed main(){
    if(freopen("ge.in","r",stdin)==nullptr)return -1;
    if(freopen("ge.out","w",stdout)==nullptr)return -1;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    fac[0]=invfac[0]=1;
    for(int i=1;i<=lim;++i)
        fac[i]=fac[i-1]*i%mod;
    invfac[lim]=qpow(fac[lim],mod-2);
    for(int i=lim;i>1;--i)
        invfac[i-1]=invfac[i]*i%mod;
    int T;
    cin>>T;
    while(T--)
        solve();
    cout.flush();
    return 0;
}