#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10;
const int INF=1e9;
int n, m, cnt;
int head[N], dis[N], tot[N];
struct node{
	int to, next, w;
}e[N*2];
void add(int u, int v, int w){
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void init(){
	for (int i=1; i<=n; i++){
		dis[i]=INF;
	}
	tot[0]++;
}
void SPFA(){
	init();
	queue<int> q;
	q.push(0);
	int u, v, w;
	while(!q.empty()){
		u=q.front();
		q.pop();
		for (int i=head[u]; i; i=e[i].next){
			v=e[i].to, w=e[i].w;
			if (dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if (++tot[v]>n){
					printf("NO");
					return ;
				}
				q.push(v);
			}
		}
	}
	for (int i=1; i<=n; i++){
		printf("%lld ", dis[i]);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	int u, v, w;
	for (int i=1; i<=n; i++){
		cin >> u >> v >> w;
		add(v, u, w);
	}
	for (int i=1; i<=n; i++){
		add(0, i, 0);
	}
	SPFA();

	return 0;
}