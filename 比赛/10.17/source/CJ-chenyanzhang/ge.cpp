#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998442353;
int q,n,m,p[20][20],dis[20][20];
bool f[20],vis[20],flag;
int ans,t;
void getw(int u,int v){
	for(int i=1;i<=n;i++) dis[u][v]=(dis[u][v]+abs(p[u][i]-p[v][i])%mod)%mod;
	dis[v][u]=dis[u][v];
	return;
}
void dfs(int now,int k,int tim){
	if(k==m-1){
		flag=1;
		if(tim<t){t=tim;ans=1;}
		else if(tim==t) ans=(ans+1)%mod;
		return;
	}
	for(int i=1;i<=m;i++){
		if(vis[i]) continue;
		vis[i]=1;
		dfs(i,k+1,tim+dis[now][i]);
		vis[i]=0;
	}
}
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>q;
	while(q--){
		cin>>n>>m;
		ans=0,t=1e9,flag=0;
		memset(dis,0,sizeof(dis));
		for(int i=1;i<=16;i++) vis[i]=0;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				cin>>p[i][j];
		for(int i=1;i<=m;i++) cin>>f[i];
		for(int i=1;i<=m;i++){
			for(int j=i+1;j<=m;j++){
				getw(i,j);
			}
		}
		for(int i=1;i<=m;i++){
			if(f[i]){
				vis[i]=1;
				dfs(i,0,0);
				vis[i]=0;
			}
		}
		if(!flag) cout<<"NIE\n";
		else cout<<t<<" "<<ans<<"\n";
	}
	return 0;
} 
