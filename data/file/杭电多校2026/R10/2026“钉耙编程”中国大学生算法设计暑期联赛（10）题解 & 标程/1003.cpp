#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2e3+50;
const int MAXM=2e5+50;
const ll INF=1e18;
struct Edge
{
	int x,y,Next;
	ll G;
}e[MAXM<<1];
int elast[MAXN],tot=1;
int S,T,Num;
int Depth[MAXN];
int Cur[MAXN];
void Add(int x,int y,ll G)
{
	tot++;
	e[tot].x=x;
	e[tot].y=y;
	e[tot].G=G;
	e[tot].Next=elast[x];
	elast[x]=tot;
	
	tot++;
	e[tot].x=y;
	e[tot].y=x;
	e[tot].G=0;
	e[tot].Next=elast[y];
	elast[y]=tot;
}
bool bfs()
{
	for(int i=0;i<=Num;i++)
	{
		Depth[i]=-1;
	}
	queue<int>q;
	Depth[S]=0;
	q.push(S);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		
		for(int i=elast[u];i;i=e[i].Next)
		{
			int v=e[i].y;
			if(e[i].G>0&&Depth[v]==-1)
			{
				Depth[v]=Depth[u]+1;
				q.push(v);
			}
		}
	}
	return Depth[T]!=-1;
}
ll dfs(int u,ll In)
{
	if(u==T)
	{
		return In;
	}
	ll flow,Out=0;
	for(int &i=Cur[u];i;i=e[i].Next)
	{
		int v=e[i].y;
		if(e[i].G>0&&Depth[v]==Depth[u]+1)
		{
			flow=dfs(v,min(In,e[i].G));
			if(flow>0)
			{
				In-=flow;
				Out+=flow;
				e[i].G-=flow;
				e[i^1].G+=flow;
				if(In<=0)
				{
					return Out;
				}
			}
		}
	}
	return Out;
}
ll Dinic()
{
	ll MaxFlow=0;
	while(bfs())
	{
		for(int i=0;i<=Num;i++)
		{
			Cur[i]=elast[i];
		}
		
		while(true)
		{
			ll pushed=dfs(S,INF);
			if(pushed==0)
			{
				break;
			}
			MaxFlow+=pushed;
		}
	}
	return MaxFlow;
}
void Clear()
{
	tot=1;
	for(int i=0;i<=Num;i++)
	{
		elast[i]=0;
	}
}
int N,K;
string s[MAXN];
bool Check(int Now)
{
	for(int i=1;i<=N;i++)
	{
		Add(S,i,1);
		for(int j=0;j<K;j++)
		{
			if(s[i][j]=='1')
			{
				Add(i,N+j+1,1);
			}
		}
	}
	for(int i=1;i<=K;i++)
	{
		Add(N+i,T,Now);
	}
	ll Max=Dinic();
	Clear();
	if(Max==Now*K)
	return true;
	else
	return false;
}

void Solve()
{
	cin>>N>>K;
	S=0;
	T=N+K+1;
	Num=N+K+2;
	for(int i=1;i<=N;i++)
	{
		cin>>s[i];
	}
	int l=0,r=N,Mid,ans=0;
	while(l<=r)
	{
		Mid=l+r>>1;
		if(Check(Mid))
		{
			ans=Mid;
			l=Mid+1;
		}
		else
		{
			r=Mid-1;
		}
	}
	cout<<ans<<'\n';
}

int main()
{
	ios::sync_with_stdio(false);
	int Test;
	cin>>Test;
	while(Test--)
	{
		Solve();
	}
	return 0;
}
