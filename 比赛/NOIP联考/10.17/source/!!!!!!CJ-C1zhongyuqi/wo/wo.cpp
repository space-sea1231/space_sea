#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e2+9,Mod=998244353;
ll T,n,a[N<<1],vis[N],ans,maxx,b[N<<1];
inline void dfs(ll x,ll sum){(sum+=((x%2==0)&&(x>=2)?abs(a[x]-a[x-1]):0));if(x==n*2)return (sum>maxx?maxx=sum,ans=1:(sum==maxx?ans++:0)),void();if(b[x+1]!=0)dfs(x+1,sum);else{for(int i=1;i<=2*n;i++)if(!vis[i]){vis[i]=1;a[x+1]=i;dfs(x+1,sum);vis[i]=0;}}}
int main()
{
	freopen("wo.in","r",stdin);	
	freopen("wo.out","w",stdout);
	cin>>T;
	while(T--)
	{
		memset(vis,0,sizeof(vis));memset(b,0,sizeof(b));ans=maxx=0;
		cin>>n;for(int i=1;i<=n*2;i++)cin>>a[i],vis[a[i]]=1,b[(a[i]?i:0)]=1;
		vis[0]=0;dfs(0,0);cout<<ans<<endl;
	}
	return 0;
}
