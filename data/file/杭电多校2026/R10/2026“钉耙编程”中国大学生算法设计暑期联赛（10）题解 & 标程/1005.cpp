#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN=1e3+50;
const ll INF=1e18;
struct StoerWagner
{
	int N;
	ll g[MAXN][MAXN];
	bool vis[MAXN];
	bool used[MAXN];
	ll weight[MAXN];
	int last,pre;
	
	void Add(int u,int v,ll w)
	{
		if(u==v)
		{
			return;
		}
		g[u][v]+=w;
		g[v][u]+=w;
	}
	ll phase(int &pre,int &last)
	{
		for(int i=1;i<=N;i++)
		{
			used[i]=false;
			weight[i]=0;
		}
		pre=-1;
		last=-1;
		for(int i=1;i<=N;i++)
		{
			int u=-1;
			for(int j=1;j<=N;j++)
			{
				if(!vis[j]&&!used[j])
				{
					if(u==-1||weight[j]>weight[u])
					{
						u=j;
					}
				}
			}
			if(u==-1)
			{
				break;
			}
			used[u]=true;
			pre=last;
			last=u;
			for(int v=1;v<=N;v++)
			{
				if(!vis[v]&&!used[v])
				{
					weight[v]+=g[u][v];
				}
			}
		}
		return weight[last];
	}
	ll Solve()
	{
		ll ans=INF;
		for(int i=1;i<N;i++)
		{
			int pre,last;
			ll cut=phase(pre,last);
			ans=min(ans,cut);
			if(ans==0)
			{
				return 0;
			}
			vis[last]=true;
			for(int v=1;v<=N;v++)
			{
				if(!vis[v])
				{
					g[pre][v]+=g[last][v];
					g[v][pre]=g[pre][v];
				}
			}
		}
		return ans;
	}
	void Clear()
	{
		for(int i=1;i<=N;i++)
		{
			vis[i]=false;
			used[i]=false;
			weight[i]=0;
			for(int j=1;j<=N;j++)
			{
				g[i][j]=0;
			}
		}
	}
}sw;
int N,M;
void Solve()
{
	cin>>N>>M;
	sw.N=N; 
	for(int i=1;i<=M;i++)
	{
		int u,v;
		ll w;
		cin>>u>>v>>w;
		sw.Add(u,v,w);
	}
	cout<<1ll*(N-1)*sw.Solve()<<'\n';
	sw.Clear();
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
	{
		Solve();
	}
	return 0;
}
