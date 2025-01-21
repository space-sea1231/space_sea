#include <bits/stdc++.h>
using namespace std;
const int N=100010;
const int M=1e7+10;
const int INF=0x7fffffff;
int to[N], nxt[N], edge[N];
int n, m, cnt, head[N], ask[N], ans[N];
int root, num, siz[N], mxsiz[N], vis[N], tot[M];
int dis[N], sum[N], top, que[N];
int l, r;
void Add(int u, int v, int w){
	to[++cnt]=v;
	edge[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void Dfs1(int u, int fa){
	siz[u]=1, mxsiz[u]=0;
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa||vis[v]){
			continue;
		}
		Dfs1(v, u);
		siz[u]+=siz[v];
		mxsiz[u]=max(mxsiz[u], siz[v]);
	}
	mxsiz[u]=max(mxsiz[u], num-siz[u]);
	if (mxsiz[u]<mxsiz[root]){
		root=u;
	}
}
void Dfs3(int u, int fa){
	sum[++top]=dis[u];
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i], w=edge[i];
		if (v==fa||vis[v]){
			continue;
		}
		dis[v]=dis[u]+w;
		Dfs3(v, u);
    }
}
void Dfs2(int u, int fa){
	l=0, r=0;
	tot[0]=1, vis[u]=1;
	for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=edge[i];
		if (v==fa||vis[v]){
			continue;
		}
		dis[v]=w;
		Dfs3(v, u);
		for (int j=1; j<=top; j++){
			for (int k=1; k<=m; k++){
				if (ask[k]>=sum[j]){
					ans[k]|=tot[ask[k]-sum[j]];
				}
			}
		}
		for (int j=1; j<=top; j++){
			if (sum[j]<M){
				que[++r]=sum[j];
				tot[sum[j]]=1;
			}
		}
		top=0;
	}
	while (l<=r){
		tot[que[l++]]=0;
	}
	for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
		if (v==fa||vis[v]){
			continue;
		}
		num=siz[v], mxsiz[0]=INF;
		root=0;
		Dfs1(v, u);
		Dfs1(root, 0);
		Dfs2(root, u);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
    cin >> n >> m;
	for (int i=1; i<n; i++){
		int u, v, w;
		cin >> u >> v >> w;
		Add(u, v, w);
		Add(v, u, w);
	}
	for (int i=1; i<=m; i++){
		cin >> ask[i];
	}
	num=n, mxsiz[0]=INF;
	Dfs1(1, 0);
	Dfs1(root, 0);
	Dfs2(root, 0);
	for (int i=1; i<=m; i++){
		if (ans[i]){
			printf("AYE\n");
		}else{
			printf("NAY\n");
		}
	}

	return 0;
}