#include<iostream>
#include<algorithm>
using namespace std;
const int N=5e5+5;
const int M=2*N;
int T,n,m;
int x[N],y[N],d[N],pre[N],lst[N];
int h[M],to[M],nxt[M],cnt;
int dfn[M],low[M],bel[M],st[M],ins[M];
int tim,top,scc;
int bg[N],cur[N],adj[M],dep[N];
int id(int k,int v){
	return 2*k-1+v;
}
int op(int k){
	if(k&1) return k+1;
	return k-1;
}
void add(int u,int v){
	to[++cnt]=v;
	nxt[cnt]=h[u];
	h[u]=cnt;
}
void tarjan(int u){
	dfn[u]=low[u]=++tim;
	st[++top]=u;
	ins[u]=1;
	for(int i=h[u];i;i=nxt[i]){
		int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		scc++;
		while(1){
			int v=st[top--];
			ins[v]=0;
			bel[v]=scc;
			if(v==u) break;
		}
	}
}
void dfs(int u,int fa){
	for(int i=bg[u];i<bg[u+1];i++){
		int w=adj[i];
		if(w==fa) continue;
		dep[w]=dep[u]+1;
		dfs(w,u);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		m=n-1;
		cnt=tim=top=scc=0;
		for(int i=1;i<=n;i++){
			d[i]=pre[i]=lst[i]=0;
		}
		for(int i=1;i<=2*m;i++){
			h[i]=dfn[i]=0;
		}
		for(int i=1;i<=m;i++){
			cin>>x[i]>>y[i];
			pre[x[i]]=lst[x[i]],lst[x[i]]=i,d[x[i]]++;
			pre[y[i]]=lst[y[i]],lst[y[i]]=i,d[y[i]]++;
		}
		bg[1]=1;
		for(int i=1;i<=n;i++) bg[i+1]=bg[i]+d[i];
		for(int i=1;i<=n;i++) cur[i]=bg[i];
		for(int i=1;i<=m;i++){
			adj[cur[x[i]]++]=y[i];
			adj[cur[y[i]]++]=x[i];
		}
		for(int v=1;v<=n;v++){
			int a=id(lst[v],y[lst[v]]==v);
			if(d[v]==1) add(a,op(a));
			else{
				int b=id(pre[v],y[pre[v]]==v);
				add(a,b);
				add(op(b),op(a));
			}
		}
		for(int i=1;i<=2*m;i++){
			if(!dfn[i]) tarjan(i);
		}
		int fl=1;
		for(int i=1;i<=m;i++){
			if(bel[id(i,0)]==bel[id(i,1)]) fl=0;
		}
		if(fl){
			cout<<1<<"\n";
			for(int i=1;i<=m;i++){
				if(bel[id(i,1)]<bel[id(i,0)]) cout<<y[i];
				else cout<<x[i];
				cout<<(i==m?'\n':' ');
			}
		}
		else{
			dep[1]=0;
			dfs(1,0);
			cout<<2<<"\n";
			for(int i=1;i<=m;i++){
				if(dep[x[i]]>dep[y[i]]) cout<<x[i];
				else cout<<y[i];
				cout<<(i==m?'\n':' ');
			}
		}
	}
	return 0;
}
