#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e2+10;
const int INF=1e9;
int dis[N][N], edge[N][N], vis[N][N];
int n, m, ans=INF;
vector<int> path;
void init(){
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			if (i!=j){
				edge[i][j]=INF;
				dis[i][j]=INF;
			}
		}
	}
}
void add(int u, int v, int w){
	edge[u][v]=min(edge[u][v], w);
	dis[u][v]=edge[u][v];
}
void serch(int u, int v){
	if (!vis[u][v]){
		return ;
	}
	serch(u, vis[u][v]);
	path.push_back(vis[u][v]);
	serch(vis[u][v], v);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	init();
	int u, v, w;
	for (int i=1; i<=m; i++){
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}
	for (int k=1; k<=n; k++){
		for (int i=1; i<k; i++){
			for (int j=i+1; j<k; j++){
				if (ans>dis[i][j]+edge[j][k]+edge[k][i]){
					ans=dis[i][j]+edge[j][k]+edge[k][i];
					path.clear();
					path.push_back(i);
					serch(i, j);
					path.push_back(j);
					path.push_back(k);
				}
			}
		}
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++){
				if (dis[i][j]>dis[i][k]+dis[k][j]){
					dis[i][j]=dis[i][k]+dis[k][j];
					vis[i][j]=k;
				}
			}
		}
	}
	if (path.empty()){
		printf("No solution.");
	}else{
		for (int i=0; i<path.size()-1; i++){
			printf("%lld ", path[i]);
		}
		printf("%lld", path[path.size()-1]);
	}
	return 0;
}