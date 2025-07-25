#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int INF=1e9;
int head[N], to[N*2], nxt[N*2], ji[N], ou[N];
int n, m, q, cnt;
void add(int u, int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void init(){
	for (int i=1; i<=n; i++)
		ji[i]=INF, ou[i]=INF;
}
void bfs()
{
	init();
	queue<pair<int, int> >q;
	int u, v, dis;
	for (int i=head[1]; i; i=nxt[i])
	{
		v=to[i], ji[v]=1;
		q.push(make_pair(1, v));
	}
	while (!q.empty())
	{
		u=q.front().second, dis=q.front().first;
		q.pop();
		for (int i=head[u]; i; i=nxt[i])
		{
			v=to[i];
			if (dis%2)
			{
				if (dis+1<ou[v])
				{
					ou[v]=dis+1;
					q.push(make_pair(dis+1, v));
				}
			}
			else
			{
				if (dis+1<ji[v])
				{
					ji[v]=dis+1;
					q.push(make_pair(dis+1, v));
				}
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> q;
	int u, v;
	for (int i=1; i<=m; i++)
	{
		cin >> u >> v;
		add(u, v), add(v, u);
	}
	bfs();
	for (int i=1; i<=q; i++)
	{
		cin >> u >> v;
		if (v%2)
		{
			if (v>=ji[u])
				printf("Yes\n");
			else
				printf("No\n");
		}
		else
		{
			if (v>=ou[u])
				printf("Yes\n");
			else
				printf("No\n");
		}
	}
	return 0;
}