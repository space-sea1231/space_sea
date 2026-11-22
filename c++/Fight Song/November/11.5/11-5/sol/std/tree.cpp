#include<bits/stdc++.h>
#define N 800005
#define ll long long
using namespace std;
template<typename T> void read(T &x){
	x=0;int f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	if(f) x=-x;
}
mt19937 rd(time(0));
int n,m;
int a[N],b[N],lc[N],rc[N];

int rt[N],tot;
int ls[N],rs[N],pri[N],siz[N],val[N],val2[N];
int sum[N],mn[N];
int vl[N],vr[N],pos[N];
int newnode(int x,int f){
	int p=++tot;
	val[p]=x,val2[p]=f;
	sum[p]=mn[p]=vl[p]=vr[p]=f;
	siz[p]=1;
	pri[p]=rd();
	return p;
}
void maintain(int x){
	siz[x]=siz[ls[x]]+siz[rs[x]]+1;
	sum[x]=sum[ls[x]]+sum[rs[x]]+val2[x];
	mn[x]=min(min(mn[ls[x]],sum[ls[x]]+val2[x]),sum[ls[x]]+val2[x]+mn[rs[x]]);
	
	if(pos[rs[x]]) pos[x]=siz[ls[x]]+1+pos[rs[x]];
	else if(val2[x]==1&&vl[rs[x]]==1) pos[x]=siz[ls[x]]+2;
	else if(val2[x]==1&&vr[ls[x]]==1) pos[x]=siz[ls[x]]+1;
	else pos[x]=pos[ls[x]];
	
	if(rs[x]) vr[x]=vr[rs[x]];
	else vr[x]=val2[x];
	if(ls[x]) vl[x]=vl[ls[x]];
	else vl[x]=val2[x];
}
void split(int p,int k,int f,int &l,int &r){
	if(!p){l=r=0;return;}
	if(val[p]<k||val[p]==k&&val2[p]>=f){
		l=p;
		split(rs[p],k,f,rs[p],r);
	}else{
		r=p;
		split(ls[p],k,f,l,ls[p]);
	}
	maintain(p);
}
void split2(int p,int k,int &l,int &r){
	if(!p){l=r=0;return;}
	if(siz[ls[p]]+1<=k){
		l=p;
		split2(rs[p],k-siz[ls[p]]-1,rs[p],r);
	}else{
		r=p;
		split2(ls[p],k,l,ls[p]);
	}
	maintain(p);
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(pri[x]>pri[y]){
		rs[x]=merge(rs[x],y);
		maintain(x);
		return x;
	}else{
		ls[y]=merge(x,ls[y]);
		maintain(y);
		return y;
	}
}
int join(int x,int y){
	if(!x||!y) return x+y;
	if(pri[x]<pri[y]) swap(x,y);
	int l,r;
	split(y,val[x],val2[x],l,r);
	ls[x]=join(ls[x],l);
	rs[x]=join(rs[x],r);
	maintain(x);
	return x;
}

int f[N];
void dfs(int x){
	if(a[x]>b[x]){
		rt[x]=merge(newnode(m-a[x],1),newnode(m-b[x],-1));
	}
	if(a[x]<b[x]){
		int p1=newnode(0,1),p2=newnode(m-b[x],-1),p3=0,p4=0;
		if(a[x]) p3=newnode(m-a[x],1),p4=newnode(m,-1);
		rt[x]=merge(merge(p1,p2),merge(p3,p4));
	}
	if(lc[x]) {
		dfs(lc[x]);
		rt[x]=join(rt[x],rt[lc[x]]);
		f[x]+=f[lc[x]];
	}
	if(rc[x]) {
		dfs(rc[x]);
		rt[x]=join(rt[x],rt[rc[x]]);
		f[x]+=f[rc[x]];
	}
	int l,t,r;
	while(siz[rt[x]]){
		split2(rt[x],siz[rt[x]]-1,l,r);
		split2(l,1,l,t);
		if(mn[t]>=0&&val[l]==0&&val[r]==m){
			f[x]++;
			rt[x]=t;
		}else {
			rt[x]=merge(merge(l,t),r);
			break;
		}
	}
	while(pos[rt[x]]){
		int p=pos[rt[x]];
		split2(rt[x],p+1,l,r);
		split2(l,p-1,l,t);
		rt[x]=merge(l,r);
	}
}

int main(){
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
	read(n),read(m);
	for(int i=1;i<=n;i++) read(a[i]),read(b[i]),read(lc[i]),read(rc[i]);
	dfs(1);
	int l,r;
	split2(rt[1],1,l,r);
	cout<<f[1]+(l&&val[l]==0);
	return 0;
}
