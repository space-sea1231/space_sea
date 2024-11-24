#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
const int M=1e4+10;
const int INF=1e9;
int n, m, k, cnt;
int head[N], dis[N], tot[N];
bool vis[N];
struct node{
	int to, next, w;
}e[M*4];
void add(int u, int v, int w){
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void init(int s){
	for (int i=0; i<=n; i++){
		dis[i]=INF, tot[i]=0, vis[i]=0;
	}
	dis[s]=0, vis[s]=1;
}
void SPFA(int s){
	init(s);
	queue<int> q;
	q.push(s);
	int u, v, w;
	while (!q.empty()){
		u=q.front();
		q.pop();
		vis[u]=0;
		if (++tot[u]>n){
			printf("-1");
			exit(0);
		}
		for (int i=head[u]; i; i=e[i].next){
			v=e[i].to, w=e[i].w;
			if (dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if (vis[v]){
					continue;
				}
				vis[v]=1;
				q.push(v);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	int u, v, w;
	for (int i=1; i<=m; i++){
		cin >> u >> v >> w;
		add(u, v, w);
	}
	for (int i=1; i<=k; i++){
		cin >> u >> v >> w;
		add(v, u, -w);
	}
	for (int i=1; i<n; i++){
		add(i+1, i, 0);
	}
	for (int i=1; i<=n; i++){
		add(0, i, 0);
	}
	SPFA(0);
	if (dis[n]==INF){
		printf("-2");
	}else{
		SPFA(1);
		if (dis[n]==INF){
			printf("-2");
		}else{
			printf("%d", dis[n]);
		}
	}
	return 0;
}