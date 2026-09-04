#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define gc getchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
template<typename T> void out(T *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1e5+5,inf=1e9;
struct People{
	int x,v;
	People(){x=0,v=inf;}
	bool operator<(const People &y)const{re v<y.v;}
	bool operator>(const People &y)const{re v>y.v;}
}a[N<<1];
vector<int> e[N];
int n,m,k,dfn[N],rk[N],ti,siz[N],son[N],Tid,top[N],lst[N<<1],fa[N];

void dfs1(int x){
	siz[x]=1;
	int mx=0;
	for(int i:e[x]){
		dfs1(i);
		siz[x]+=siz[i];
		if(siz[i]>mx) mx=siz[i],son[x]=i;
	}
}

void dfs2(int x,int t){
	top[x]=t;
	dfn[x]=++ti;rk[ti]=x;
	if(son[x]) dfs2(son[x],t);
	for(int i:e[x]) if(i!=son[x]) dfs2(i,i);
}

#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
namespace DS1{//维护子树最小值
//auto cmp=[](int x,int y){re a[x]<a[y];};
//priority_queue<int,vector<int>,decltype(cmp)> pq[N];
struct qwq{
	int id;
	qwq(){id=0;}
	qwq(int o){id=o;}
	bool operator<(const qwq &x)const{
		if(a[id].v!=a[x.id].v) re a[id]<a[x.id];
		re id<x.id;
	}
};
set<qwq> pq[N];
int tr[N<<2];
void ps(int x){
	if(a[tr[ls]]<a[tr[rs]]) tr[x]=tr[ls];
	else tr[x]=tr[rs];
}
void upd(int x,int l,int r,int aim,int k){
	if(l==r){
		tr[x]=k;
		re;
	}
	if(aim<=mid) upd(ls,l,mid,aim,k);
	else upd(rs,mid+1,r,aim,k);
	ps(x);
}

int ask(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R) re tr[x];
	if(R<=mid) re ask(ls,l,mid,L,R);
	if(L>mid) re ask(rs,mid+1,r,L,R);
	int wl=ask(ls,l,mid,L,R);
	int wr=ask(rs,mid+1,r,L,R);
	if(a[wl]>a[wr]) re wr;
	re wl;
}

void ins(int id){
	int x=a[id].x;
	pq[x].insert(qwq(id));
	upd(1,1,n,dfn[x],(*pq[x].begin()).id);
}
void del(int id){
	int x=a[id].x;
//	assert(id==pq[x].top().id);
	pq[x].erase(qwq(id));
	if(pq[x].empty()) upd(1,1,n,dfn[x],0);
	else upd(1,1,n,dfn[x],(*pq[x].begin()).id);
}
}

namespace DS2{
	
namespace Sgt{
struct Node{
	int tag,mn;
	Node(){tag=0;mn=inf;}
	void upd(int x){tag+=x,mn+=x;}
}tr[N<<2];

void ps(int x){tr[x].mn=min(tr[ls].mn,tr[rs].mn);}
void pd(int x){
	int &k=tr[x].tag;
	if(!k) re;
	tr[ls].upd(k);
	tr[rs].upd(k);
	k=0;
}

void build(int x,int l,int r){
	if(l==r){
		tr[x].mn=siz[rk[l]];
		re;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	ps(x);
}

void upd(int x,int l,int r,int L,int R,int k){
//	if(x==1) printf("upd(%d,%d,%d,%d,%d,%d)\n",x,l,r,L,R,k);
	if(l>=L&&r<=R){
		tr[x].upd(k);
		re;
	}
	pd(x);
	if(L<=mid) upd(ls,l,mid,L,R,k);
	if(R>mid) upd(rs,mid+1,r,L,R,k);
	ps(x);
}

int ask(int x,int l,int r,int L,int R){
//	if(x==1) printf("Sgt::ask(%d,%d,%d,%d,%d)\n",x,l,r,L,R);
	if(l>=L&&r<=R) re tr[x].mn;
	pd(x);
	if(R<=mid) re ask(ls,l,mid,L,R);
	if(L>mid) re ask(rs,mid+1,r,L,R);
	re min(ask(ls,l,mid,L,R),ask(rs,mid+1,r,L,R));
}

int get(int x,int l,int r,int L,int R){
//	printf("get(%d,%d,%d,%d,%d)\n",x,l,r,L,R);
	if(l>=L&&r<=R){
		if(tr[x].mn>0) re 0;
		while(l<r){
			pd(x);
			if(tr[rs].mn==0) x=rs,l=mid+1;
			else x=ls,r=mid;
		}
		re rk[l];
	}
	pd(x);
	if(R<=mid) re get(ls,l,mid,L,R);
	if(L>mid) re get(rs,mid+1,r,L,R);
	int w=get(rs,mid+1,r,L,R);
	if(w) re w;
	re get(ls,l,mid,L,R);
}
}


void build(){
	Sgt::build(1,1,n);
}

void upd(int x,int k){
	while(x){
		int y=top[x];
		Sgt::upd(1,1,n,dfn[y],dfn[x],k);
		x=fa[y];
	}
}
int ask(int x){
	while(x){
		int y=top[x];
		if(Sgt::ask(1,1,n,dfn[y],dfn[x])>0){
			x=fa[y];
			co;
		}
		re Sgt::get(1,1,n,dfn[y],dfn[x]);
	}
	re 0;
}
} 

namespace Company{
struct Roll{
	int id,loser;
}stk[N<<1];
int top;
ll ans;

void hello_world(int id){//正式步入职业生涯 
	//Hello, world!
//	printf("hello_world(%d)!\n",id);
	ans+=a[id].v;
	DS1::ins(id);
	DS2::upd(a[id].x,-1);
}

void say_goodbye(int id){
//	printf("say_goodbye(%d)!\n",id);
	ans-=a[id].v;
	DS1::del(id);
	DS2::upd(a[id].x,1);
}

bool gao(int id){//把员工 id 加进来 
//	printf("gao(%d)\n",id);
	int t=DS2::ask(a[id].x);
	if(!t){
		++top;
		stk[top].id=id,stk[top].loser=0;//岗位充足，没有产生下岗员工 
		hello_world(id);
		re 1;
	}
	//很遗憾，零和博弈，必定有输家
	int me=DS1::ask(1,1,n,dfn[t],dfn[t]+siz[t]-1);//末位淘汰
	if(a[me]<a[id]){//内卷斗兽场 
		++top;
		stk[top].id=id,stk[top].loser=me;
		hello_world(id);
		say_goodbye(me);
		re 1;
	}
	re 0;
}
void roll(){
//	puts("roll_back");
	int x=stk[top].id,y=stk[top].loser;top--;
	say_goodbye(x);
	if(y) hello_world(y);
}
}
ll ans[N];
namespace DS3{//时间线段树
vector<int> tr[N<<2];
void push(int x,int l,int r,int L,int R,int id){
//	printf("push(%d,%d,%d,%d,%d,%d)\n",x,l,r,L,R,id);
	if(l>=L&&r<=R){
		tr[x].pb(id);
		re;
	}
	if(L<=mid) push(ls,l,mid,L,R,id);
	if(R>mid) push(rs,mid+1,r,L,R,id);	
}
void dfs(int x,int l,int r){
//	printf("dfs(%d,%d,%d)\n",x,l,r);
	int ct=0;
	for(int i:tr[x]) ct+=Company::gao(i);
	if(l==r) ans[l]=Company::ans;
	else dfs(ls,l,mid),dfs(rs,mid+1,r);
	while(ct--) Company::roll();
}
}

void file(){
	freopen("transfer.in","r",stdin);
	freopen("transfer.out","w",stdout);
}

signed main(){
//	file();
	cin>>Tid;
	cin>>n>>k>>m;
	fo(i,2,n) fa[i]=read(),e[fa[i]].pb(i);
	dfs1(1);
	dfs2(1,1);
//	cout<<"son:";out(son,1,n);
//	cout<<"dfn:";out(dfn,1,n);
//	cout<<"top:";out(top,1,n);
	DS2::build();
	fo(i,1,k) a[i].x=read(),a[i].v=read();
	fo(i,1,m){
		int o=read(),x=read();
		if(o==1){
			a[++k].x=x;
			lst[k]=i;
			a[k].v=read();
		}else DS3::push(1,0,m,lst[x],i-1,x),lst[x]=-1;
	}
	fo(i,1,k) if(lst[i]>-1) DS3::push(1,0,m,lst[i],m,i);
	DS3::dfs(1,0,m);
	out(ans,0,m);
	return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
