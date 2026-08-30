#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define ll long long
#define cmax(a,b) a=max(a,b)
#define cmin(a,b) a=min(a,b)
#define ls p<<1
#define rs p<<1|1
#define FAST ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
using namespace std;
const int N(5e5+5);
struct segment_tree1{
	struct node{
		int mn,c1,c2,tg;
		void upd(int v){
			mn+=v;
			tg+=v;
		}
	}t[1<<20|5];
	node merge(node x,node y){
		node res={min(x.mn,y.mn),0,0,0};
		if(x.mn==res.mn) res.c1+=x.c1,res.c2+=x.c2;
		else if(x.mn==res.mn+1) res.c2+=x.c1;
		if(y.mn==res.mn) res.c1+=y.c1,res.c2+=y.c2;
		else if(y.mn==res.mn+1) res.c2+=y.c1;
		return res;
	}
	void down(int p){
		if(t[p].tg){
			t[ls].upd(t[p].tg);
			t[rs].upd(t[p].tg);
			t[p].tg=0;
		}
	}
	void build(int l,int r,int p){
		t[p]={0,r-l+1,0,0};
		if(l==r) return ;
		int mid=l+r>>1;
		build(l,mid,ls);build(mid+1,r,rs);
	}
	void update(int l,int r,int p,int L,int R,int v){
		if(L<=l&&r<=R) return t[p].upd(v);
		int mid=l+r>>1;down(p);
		if(L<=mid) update(l,mid,ls,L,R,v);
		if(R>mid) update(mid+1,r,rs,L,R,v);
		t[p]=merge(t[ls],t[rs]);
	}
	node query(int l,int r,int p,int L,int R){
		if(L<=l&&r<=R) return t[p];
		int mid=l+r>>1;down(p);
		if(R<=mid) return query(l,mid,ls,L,R);
		if(L>mid) return query(mid+1,r,rs,L,R);
		return merge(query(l,mid,ls,L,R),query(mid+1,r,rs,L,R));
	}
}T1[20];

struct node1{
	int mn1,mn2;
};

node1 merge(node1 x,node1 y){
	node1 res={min(x.mn1,y.mn1),0};
	if(x.mn1==res.mn1) res.mn2=min(x.mn2,y.mn1);
	else res.mn2=min(x.mn1,y.mn2);
	return res;
}
	
struct segment_tree2{
	node1 t[1<<20|5];
	void build(int l,int r,int p){
		t[p]={inf,inf};
		if(l==r) return ;
		int mid=l+r>>1;
		build(l,mid,ls);build(mid+1,r,rs);
	}
	void update(int l,int r,int p,int x,node1 v){
		if(l==r) return t[p]=v,void();
		int mid=l+r>>1;
		if(x<=mid) update(l,mid,ls,x,v);
		else update(mid+1,r,rs,x,v);
		t[p]=merge(t[ls],t[rs]);
	}
	int query1(int l,int r,int p,int x,int v){
		if(t[p].mn1>v) return inf-1;
		if(l==r) return l;
		int mid=l+r>>1;
		if(x>mid) return query1(mid+1,r,rs,x,v);
		int res=query1(l,mid,ls,x,v);
		if(res==inf-1) return query1(mid+1,r,rs,x,v);
		return res;
	}
	int query2(int l,int r,int p,int x,int v){
		if(t[p].mn1>v) return inf;
		if(x<=l&&t[p].mn2>v) return inf-1;
		if(l==r) return l;
		int mid=l+r>>1;
		if(x>mid) return query2(mid+1,r,rs,x,v);
		int res=query2(l,mid,ls,x,v);
		if(res==inf) return query2(mid+1,r,rs,x,v);
		if(res==inf-1) return query1(mid+1,r,rs,x,v);
		return res;
	}
}T2[20];

struct node2{
	int mx1,mx2;
};
	
node2 merge(node2 x,node2 y){
	node2 res={max(x.mx1,y.mx1),0};
	if(x.mx1==res.mx1) res.mx2=max(x.mx2,y.mx1);
	else res.mx2=max(x.mx1,y.mx2);
	return res;
}
	
struct segment_tree3{
	node2 t[1<<20|5];
	void build(int l,int r,int p){
		t[p]={0,0};
		if(l==r) return ;
		int mid=l+r>>1;
		build(l,mid,ls);build(mid+1,r,rs);
	}
	void update(int l,int r,int p,int x,node2 v){
		if(l==r) return t[p]=v,void();
		int mid=l+r>>1;
		if(x<=mid) update(l,mid,ls,x,v);
		else update(mid+1,r,rs,x,v);
		t[p]=merge(t[ls],t[rs]);
	}
	int query1(int l,int r,int p,int x,int v){
		if(t[p].mx1<v) return 0;
		if(l==r) return l;
		int mid=l+r>>1;
		if(x<=mid) return query1(l,mid,ls,x,v);
		int res=query1(mid+1,r,rs,x,v);
		if(res==0) return query1(l,mid,ls,x,v);
		return res;
	}
	int query2(int l,int r,int p,int x,int v){
		if(t[p].mx1<v) return -1;
		if(x>=r&&t[p].mx2<v) return 0;
		if(l==r) return l;
		int mid=l+r>>1;
		if(x<=mid) return query2(l,mid,ls,x,v);
		int res=query2(mid+1,r,rs,x,v);
		if(res==-1) return query2(l,mid,ls,x,v);
		if(res==0) return query1(l,mid,ls,x,v);
		return res;
	}
}T3[20];

multiset <int> mst[N*2];
unordered_map <ll,int> mp;
int tot,dep[1<<20|5];

void build(int l,int r,int p,int d){
	dep[p]=d;
	T1[d].build(l,r,p);
	if(l==r) return ;
	int mid=l+r>>1;
	T2[d].build(l,mid,ls);T3[d].build(mid+1,r,rs);
	build(l,mid,ls,d+1);build(mid+1,r,rs,d+1);
}

int n,q;

void update(int l,int r,int p,int L,int R,int v){
	int d=dep[p];
	T1[d].update(l,r,p,L,R,v);
	if(l==r) return ;
	int mid=l+r>>1;
	if(R<=mid) return update(l,mid,ls,L,R,v);
	if(L>mid) return update(mid+1,r,rs,L,R,v);
	ll idL=(1ll*n*d+L)*2,idR=(1ll*n*d+R)*2+1;
	if(!mp[idL]) mp[idL]=++tot;
	if(!mp[idR]) mp[idR]=++tot;	
	idL=mp[idL];idR=mp[idR];
	if(v==1){
		mst[idL].insert(R);
		mst[idR].insert(L);
	}else{
		mst[idL].erase(mst[idL].find(R));
		mst[idR].erase(mst[idR].find(L));
	}
	node1 vL={inf,inf};
	auto itL=mst[idL].begin();
	if(mst[idL].size()>0) vL.mn1=*itL;
	if(mst[idL].size()>1) vL.mn2=*++itL;
	T2[d].update(l,mid,ls,L,vL);
	node2 vR={0,0};
	auto itR=mst[idR].end();
	if(mst[idR].size()>0) vR.mx1=*--itR;
	if(mst[idR].size()>1) vR.mx2=*--itR;
	T3[d].update(mid+1,r,rs,R,vR);
}

int query(int l,int r,int p,int L,int R,node2 x,node1 y){
	int d=dep[p];
	if(L<=l&&r<=R){
		auto calc=[&](int L,int R,int v){
			cmax(L,l);cmin(R,r);
			if(L>R) return 0;
			auto res=T1[d].query(l,r,p,L,R);
			if(res.mn==v) return res.c1;
			if(res.mn+1==v) return res.c2;
			return 0;
		};
		auto [r1,r2]=x;
		auto [l1,l2]=y;
		int ans=0;
		if(r1<=r&&l1>=l){
			ans+=calc(r1+1,l1-1,1);
			ans+=calc(r2+1,min(l1-1,r1),0);
			ans+=calc(max(r1+1,l1),l2-1,0);			
		}else if(r1<=r){
			ans+=calc(r1+1,l2-1,0);
		}else if(l1>=l){
			ans+=calc(r2+1,l1-1,0);
		}
		return ans;
	}
	int mid=l+r>>1;
	if(R<=mid) return query(l,mid,ls,L,R,x,y);
	if(L>mid) return query(mid+1,r,rs,L,R,x,y);
	return query(l,mid,ls,L,R,x,merge(y,{T2[d].query1(l,mid,ls,L,R),T2[d].query2(l,mid,ls,L,R)}))
	+query(mid+1,r,rs,L,R,merge(x,{T3[d].query1(mid+1,r,rs,R,L),T3[d].query2(mid+1,r,rs,R,L)}),y);
}

void solve(){
	cin>>n>>q;
	for(int i=1;i<=tot;i++) mst[i].clear();
	mp.clear();tot=0;
	build(1,n,1,0);
	while(q--){
		int op,l,r;cin>>op>>l>>r;
		if(op==1) update(1,n,1,l,r,1);
		else if(op==2) update(1,n,1,l,r,-1);
		else cout<<query(1,n,1,l,r,{0,0},{inf,inf})<<'\n';
	}
}

signed main(){
	FAST
	int t=1;cin>>t;
	while(t--) solve();
	return 0;
}