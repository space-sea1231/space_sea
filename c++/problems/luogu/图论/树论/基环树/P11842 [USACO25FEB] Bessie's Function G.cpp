#include <iostream>

using namespace std;

typedef long long ll;

const int N=3e5+10;
int n;
ll cnt, ans;
ll fa[N], val[N];
ll dp[N][2];
int head[N], to[N], nxt[N];
bool vis[N];

inline void Add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

inline void Dp(int u, int root){
	vis[u]=1;
	dp[u][0]=0;
	dp[u][1]=val[u];
	if (fa[u]==u){
		dp[u][1]=0;
	}
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==root){
			continue;
		}
		Dp(v, root);
		dp[u][0]+=dp[v][1];
		dp[u][1]+=min(dp[v][0], dp[v][1]);
	}
}

inline ll Solve(int x){
	while (!vis[x]){
		vis[x]=1;
		x=fa[x];
	}
	Dp(x, x);
	ll res=dp[x][1];
	Dp(fa[x], fa[x]);
	res=min(res, dp[fa[x]][1]);
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> fa[i];
		Add(fa[i], i);
	}
	for (int i=1; i<=n; i++){
		cin >> val[i]; 
	}
	for (int i=1; i<=n; i++){
		if (!vis[i]){
			ans+=Solve(i);
		}
	}
	printf("%lld\n", ans);
	
	return 0;
}