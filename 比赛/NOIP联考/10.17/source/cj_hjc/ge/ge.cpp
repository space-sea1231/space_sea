#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int P=998442353;
int T,n,m,p[20][20],s[20],ans1,ans2,d,dis,fac[3000001],inv[3000001],cou;
bool vis[20];
pii dt[20][20];
pii ddt(int i,int j)
{
    int res=0,ct=1;
    for(int k=1;k<=n;++k)res+=abs(p[i][k]-p[j][k]),ct=1ll*ct*inv[abs(p[i][k]-p[j][k])]%P;
    ct=1ll*ct*fac[res]%P;
    return {res,ct};
}
int ds[20*20];
void dfs(int x,int ct)
{
    // cou++;
    if(d==m-1)
    {
        if(ans1>dis)ans1=dis,ans2=ct;
        else if(ans1==dis)ans2=((ans2+ct>=P)?ans2+ct-P:ans2+ct);
        return;
    }
    vis[x]=true;
    for(int i=1;i<=m;++i)
    {
        if(!vis[i])
        {
            d++;dis+=dt[x][i].fi;
            if(dis<=ans1)
            dfs(i,1ll*ct*dt[x][i].se%P);
            d--;dis-=dt[x][i].fi;
        }
    }
    vis[x]=false;
}
// int qp(int a,int b)
// {
//     int res=1;
//     while(b)
//     {
//         if(b&1)res=1ll*res*a%P;
//         a=1ll*a*a%P;
//         b>>=1;
//     }
//     return res;
// }
int main()
{
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    fac[0]=1;for(int i=1;i<=3000000;++i)fac[i]=1ll*fac[i-1]*i%P;
    inv[3000000]=932252372;for(int i=3000000;i;--i)inv[i-1]=1ll*inv[i]*i%P;
    cin>>T;
    while(T--)
    {
        cin>>n>>m;ans1=1e8,ans2=0;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                cin>>p[i][j];
            }
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=i+1;j<=m;++j)
            {
                if(i!=j)
                {
                    dt[i][j]=dt[j][i]=ddt(i,j);
                }
            }
        }
        for(int i=1;i<=m;++i)
        {
            cin>>s[i];
            if(s[i])
            {
                dfs(i,1);
            }
        }
        if(ans1==1e8)cout<<"NIE\n";
        else cout<<ans1<<" "<<ans2<<"\n";
    }
    return 0;
}