#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
vector<int> g[N<<1];
int sum[N],a[N],dep[N],fa[N][20],n,m;
inline int read(){
  	int x=0,w=1;char ch=0;
  	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
  	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
  	return x*w;
}

inline void write(int x){
  	static int sta[35];int top=0;
  	do{sta[top++]=x%10,x/=10;}while (x);
  	while(top)putchar(sta[--top]+48);
}
void dfs(int u,int fath)
{
	dep[u]=dep[fath]+1;
	fa[u][0]=fath;
	for(int i=1;(1<<i)<=dep[u];i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fath)
			continue;
		sum[v]=sum[u]+a[v];
		dfs(v,u);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int d=dep[x]-dep[y];
	for(int i=0;i<=log2(n);i++)
		if((1<<i)&d)
			x=fa[x][i];
	if(x==y)
		return x;
	for(int i=log2(n);i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	}
	return fa[x][0];
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)
		a[i]=g[i].size(),sum[i]=g[i].size();
	dfs(1,0);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
//		cout<<sum[u]<<" "<<sum[v]<<" "<<sum[lca(u,v)]<<" "<<a[lca(u,v)]<<endl;
		cout<<sum[u]+sum[v]-2*sum[lca(u,v)]+a[lca(u,v)]<<endl;
	}
	return 0;
}

