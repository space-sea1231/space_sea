#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int head[N], to[N<<1], nxt[N<<1];
int dep[N], dp[N][31];
int n, m, s, cnt;
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void serch(int u, int fa){
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		dep[v]=dep[u]+1;
		dp[v][0]=u;
		for (int j=1; j<=30; j++){
			dp[v][j]=dp[dp[v][j-1]][j-1];
		}
		serch(v, u);
	}
}
int lca(int x, int y){
	if (dep[x]<dep[y]){
		swap(x, y);
	}
	for (int i=30; i>=0; i--){
		if (dep[dp[x][i]]>=dep[y]){
			x=dp[x][i];
		}
	}
	if (x==y){
		return x;
	}
	for (int i=30; i>=0; i--){
		if (dp[x][i]!=dp[y][i]){
			x=dp[x][i], y=dp[y][i];
		}
	}
	return dp[x][0];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m >> s;
	for (int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	dep[s]=1;
	serch(s, 0);
	for (int i=1; i<=m; i++){
		int x, y;
		cin >> x >> y;
		printf("%d\n", lca(x, y));
	}

	return 0;
}