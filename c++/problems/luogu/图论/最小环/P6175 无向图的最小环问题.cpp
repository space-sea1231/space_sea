#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int INF=1e8;
int n, m, ans=INF;
int edge[N][N], dis[N][N];
void init()
{
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			if (i!=j) dis[i][j]=INF, edge[i][j]=INF;
}
void add(int u, int v, int w)
{
	edge[u][v]=min(edge[u][v], w);
	dis[u][v]=edge[u][v];
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	int u, v, w;
	init();
	for (int i=1; i<=m; i++)
	{
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}
	for (int k=1; k<=n; k++)
	{
		for (int i=1; i<k; i++)
			for (int j=i+1; j<k; j++)
				ans=min(ans, dis[i][j]+edge[j][k]+edge[k][i]);
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				dis[i][j]=min(dis[i][j], dis[i][k]+dis[k][j]);
	}
	if (ans==INF) printf("No solution.");
	else printf("%d", ans);

	return 0;
}