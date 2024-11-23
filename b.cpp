#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
int n, m, cnt;
int head[N], nxt[N<<1], to[N<<1];
bool vis[N];
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void dfs(int u, int fa){
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		if (vis[v]){
			node=v;
			return ;
		}
		vis[v]=1;
		dfs(v, u);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<=m; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	vis[1]=1;
	dfs(1, 0);
	for (int i)
	return 0;
}