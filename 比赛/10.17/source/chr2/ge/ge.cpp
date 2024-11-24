#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=16;
const int M=(2e5+10)*16;
const int mod=998442353;
int f[N][N],g[N][N];
int F[N][1<<N],G[N][1<<N];
signed jc[M],inv[M];
int c(int x,int y){return 1ll*jc[x]*inv[y]%mod*inv[x-y]%mod;}
int p[N][N];
void run()
{
    int n,m;
    cin>>m>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>p[i][j];
    while(1)
    {
        bool flag=1;
        for(int i=0;i<n&&flag;i++)
            for(int j=i+1;j<n&&flag;j++)
            {
                bool can=1;
                for(int k=0;k<m;k++) can&=p[i][k]==p[j][k];
                if(can) 
                {
                    flag=0;
                    for(int k=j;k<n-1;k++)
                        memcpy(p[k],p[k+1],sizeof(p[k]));
                    n--;
                }
            }
        if(flag) break;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<(1<<n);j++)
            F[i][j]=1e18,G[i][j]=0;
    for(int j=0;j<n;j++) 
    {
        cin>>G[j][1<<j];
        if(G[j][1<<j]) F[j][1<<j]=0;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            if(i==j) continue;
            int dis=0;
            for(int k=0;k<m;k++) dis+=abs(p[i][k]-p[j][k]);
            f[i][j]=dis;
            int ans=1;
            for(int k=0;k<m;k++)
            {
                ans=ans*c(dis,abs(p[i][k]-p[j][k]))%mod;
                dis-=abs(p[i][k]-p[j][k]);
            }
            g[i][j]=ans;
        }
    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<n;j++)
        {
            if(!G[j][i]||(i>>j&1^1)) continue;
            for(int k=0;k<n;k++)
            {
                if(i>>k&1) continue;
                if(F[k][i|1<<k]>F[j][i]+f[j][k]) F[k][i|1<<k]=F[j][i]+f[j][k];
                if(F[k][i|1<<k]==F[j][i]+f[j][k]) G[k][i|1<<k]=(G[k][i|1<<k]+G[j][i]*g[j][k]%mod)%mod;
            }
        }
    int ans=1e18,ans2=0,u=(1<<n)-1;
    for(int i=0;i<n;i++)
    {
        if(F[i][u]<ans) ans=F[i][u];
        if(F[i][u]==ans) ans2+=G[i][u];
    }
    if(ans==1e18) cout<<"NIE\n";
    else cout<<ans<<' '<<ans2%mod<<'\n';
} 
signed main()
{
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    jc[0]=inv[0]=jc[1]=inv[1]=1;
    for(int i=2;i<=2e5*16;i++) jc[i]=1ll*jc[i-1]*i%mod;
    for(int i=2;i<=2e5*16;i++) inv[i]=mod-1ll*mod/i*inv[mod%i]%mod;
    for(int i=2;i<=2e5*16;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
    int t;
    cin>>t;
    while(t--) run();
	return 0;
}
