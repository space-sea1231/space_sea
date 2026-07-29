#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=5e5+5,M=N*32;
int n,E,T,head[N],cnt,X[N],Y[N],Z[N];
LL ans[N];
int dep[N],rt[N],ls[M],rs[M],sz[M],nod;
LL sum[M];
struct edge{
	int to,nxt;
}e[N*2];
void insert(int&o,int l,int r,const int&pos){
	if(!o)o=++nod,ls[o]=rs[o]=0,sz[o]=0,sum[o]=0;
	++sz[o];
	sum[o]+=pos;
	if(l<r){
		const int mid=(l+r)/2;
		if(pos<=mid)insert(ls[o],l,mid,pos);
		else insert(rs[o],mid+1,r,pos);
	}
}
LL findL(int o,int l,int r,int rk){
	if(l==r)return(LL)rk*l;
	const int mid=(l+r)/2;
	if(sz[ls[o]]>=rk)return findL(ls[o],l,mid,rk);
	return sum[ls[o]]+findL(rs[o],mid+1,r,rk-sz[ls[o]]);
}
LL findR(int o,int l,int r,int rk){
	if(l==r)return(LL)rk*l;
	const int mid=(l+r)/2;
	if(sz[rs[o]]>=rk)return findR(rs[o],mid+1,r,rk);
	return sum[rs[o]]+findR(ls[o],l,mid,rk-sz[rs[o]]);
}
int merge(int ld,int rd){
	if(!ld||!rd)return ld|rd;
	sz[ld]+=sz[rd];
	sum[ld]+=sum[rd];
	ls[ld]=merge(ls[ld],ls[rd]);
	rs[ld]=merge(rs[ld],rs[rd]);
	return ld;
}
void dfs(int u,int p){
	int deg=0;
	for(int i=head[u];i;i=e[i].nxt)if(e[i].to!=p){
		++deg;
		dep[e[i].to]=dep[u]+1;
		dfs(e[i].to,u);
		rt[u]=merge(rt[u],rt[e[i].to]);
	}
	if(sz[rt[u]]+dep[u]-1>=E){
		X[u]=max(X[u],E-sz[rt[u]]);
		Y[u]=max(Y[u],E-dep[u]+1);
		ans[u]=1e18;
		LL L=(1LL+X[u])*X[u]/2+Z[u];
		LL R=(dep[u]-1LL+dep[u]-X[u])*X[u]/2+Z[u];
		LL L_=findL(rt[u],1,n,E-X[u]),R_=findR(rt[u],1,n,E-X[u]);
		L_-=(LL)dep[u]*(E-X[u]);
		R_-=(LL)dep[u]*(E-X[u]);
		if(max(L,L_)<=min(R,R_))ans[u]=0;
		else if(R_<=L)ans[u]=L-R_;
		else if((X[u]<1||X[u]==dep[u]-2)&&L_-R==1){
			ans[u]=1;
			if(X[u]+Y[u]+1<=E&&sz[rt[u]]>deg)ans[u]=0;
		}else{
			L=(1LL+E-Y[u])*(E-Y[u])/2+Z[u];
			R=(dep[u]-1LL+dep[u]-(E-Y[u]))*(E-Y[u])/2+Z[u];
			L_=findL(rt[u],1,n,Y[u]),R_=findR(rt[u],1,n,Y[u]);
			L_-=(LL)dep[u]*Y[u];
			R_-=(LL)dep[u]*Y[u];
			if(max(L,L_)<=min(R,R_))ans[u]=0;
			else if(R_<=L)ans[u]=0;
			else ans[u]=L_-R;
		}
	}
	insert(rt[u],1,n,dep[u]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>E;
	cnt=nod=0;
	for(int i=1;i<=n;++i)head[i]=rt[i]=0,ans[i]=-1;
	for(int i=1;i<n;++i){
		int u,v;
		cin>>u>>v;
		e[++cnt]=(edge){v,head[u]},head[u]=cnt;
		e[++cnt]=(edge){u,head[v]},head[v]=cnt;
	}
	for(int i=1;i<=n;++i)cin>>X[i]>>Y[i]>>Z[i];
	dfs(dep[1]=1,0);
	for(int i=1;i<=n;++i)
		cout<<ans[i]<<" \n"[i==n];
	return 0;
}