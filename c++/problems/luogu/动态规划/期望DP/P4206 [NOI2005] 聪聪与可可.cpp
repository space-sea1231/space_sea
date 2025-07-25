#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
const int INF=1<<30;
const double res=1e-8;
bool vis[N];
double dp[N][N];
int head[N], to[N<<1], nxt[N<<1];
int go[N][N], out[N], dep[N];
int n, m, cnt;
int cat, mice;
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void init(int root){
	for (int i=0; i<N; i++){
		vis[i]=0;
		dep[i]=INF;
	}
	dep[root]=0;
	vis[root]=1;
}
void dfs(int root){
	queue<int> q;
	q.push(root);
	init(root);
	while (!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for (int i=head[u]; i; i=nxt[i]){
			int v=to[i];
			if (!vis[v]&&dep[u]+1<dep[v]){
				dep[v]=dep[u]+1;
				go[v][root]=u;
				q.push(v);
				vis[v]=1;
			}else if (dep[u]+1==dep[v]){
				if (u<go[v][root]){
					go[v][root]=u;
				}
			}
		}
	}
}
double search(int u, int v){
	if (u==v){
		return 0.0;
	}
	if (go[u][v]==v||go[go[u][v]][v]==v){
		return 1.0;
	}
	if (fabs(dp[u][v])>=res){
		return dp[u][v];
	}
	double sum=search(go[go[u][v]][v], v);
	for (int i=head[v]; i; i=nxt[i]){
		int vv=to[i];
		sum+=search(go[go[u][v]][v], vv);
	}
	return dp[u][v]=sum/(out[v]+1.0)+1.0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m >> cat >> mice;
	for (int i=1; i<=m; i++){
		int u, v;
		cin >> u >> v;
		add(u, v), add(v, u);
		out[u]++, out[v]++;
	}
	for (int i=1; i<=n; i++){
		dfs(i);
	}
	printf("%.3lf", search(cat, mice));

	return 0;
}