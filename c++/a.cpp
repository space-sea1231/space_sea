#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
const ll N=1e5+10;
priority_queue<PLL,vector<PLL>,greater<PLL>> q;
vector<PLL> e1[N],e2[N];
ll t,n,m,K,p,d[N],dp[N][60];
bool flg,vis1[N],vis2[N][60];
void dij() {
	memset(vis1,0,sizeof(vis1));
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	q.push({0,1});
	while(!q.empty()) {
		ll u=q.top().second;
		q.pop();
		if(vis1[u]) continue;
		vis1[u]=1;
		for(auto x:e1[u]) {
			ll v=x.first,w=x.second;
			if(d[v]>d[u]+w) d[v]=d[u]+w,q.push({d[v],v});
		}
	}
}
ll dfs(ll u,ll x) {
	if(vis2[u][x]) {
		flg=1;
		return 0;
	}
	if(~dp[u][x]) return dp[u][x];
	vis2[u][x]=1;
	dp[u][x]=0;
	for(auto x:e2[u]) {
		ll v=x.first,w=x.second,nk=d[u]-d[v]+x-w;
		if(nk<0 || nk>K) continue;
		dp[u][x]=(dp[u][x]+dfs(v,nk))%p;
		if(flg) {
			vis2[u][x]=0;
			return 0;
		}
	}
	if(u==1 && x==0) dp[u][x]=1;
	vis2[u][x]=0;
	return dp[u][x];
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) {
		cin>>n>>m>>K>>p;
		for(ll i=1; i<N; i++) e1[i].clear(),e2[i].clear();
		for(ll i=1,a,b,c; i<=m; i++) {
			cin>>a>>b>>c;
			e1[a].push_back({b,c});
			e2[b].push_back({a,c});
		}
		dij();
		flg=0;
		memset(dp,-1,sizeof(dp));
		ll ans=0;
		for(ll i=0; i<=K; i++) {
			ans=(ans+dfs(n,i))%p;
			if(flg) break;
		}
		if(flg) cout<<"-1\n";
		else cout<<ans<<"\n";
	}
	return 0;
}