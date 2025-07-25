#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n, cnt;
int head[N], to[N*2], nxt[N*2], edge[N*2];//建边系列
int dp[N], ans;//树形DP
void add(int u, int v, int w){
	to[++cnt]=v;
	edge[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void serch(int u, int fa){
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i], w=edge[i];
		if (v==fa){
			continue;
		}
		serch(v, u);
		ans=max(ans, dp[u]+dp[v]+w);
		dp[u]=max(dp[u], dp[v]+w);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<n; i++){
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}
	serch(1, 0);
	ans=ans*10+(ans+1)*ans/2;
	printf("%lld", ans);

	return 0;
}