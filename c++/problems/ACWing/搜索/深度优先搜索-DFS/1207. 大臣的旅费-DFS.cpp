#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n, cnt, ans;
int head[N], to[N*2], nxt[N*2], edge[N*2];//建边系列
int maxn, start;
void add(int u, int v, int w){
	to[++cnt]=v;
	edge[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void dfs_1(int u, int fa, int dep){
	if (maxn<dep){
		maxn=dep;
		start=u;
	}
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i], w=edge[i];
		if (v==fa){
			continue;
		}
		dfs_1(v, u, dep+w);
	}
}
void dfs_2(int u, int fa, int dep){
	ans=max(ans, dep);
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i], w=edge[i];
		if (v==fa){
			continue;
		}
		dfs_2(v, u, dep+w);
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
	dfs_1(1, 0, 0);
	dfs_2(start, 0, 0);
	ans=ans*10+ans*(ans+1)/2;
	printf("%lld", ans);

	return 0;
}