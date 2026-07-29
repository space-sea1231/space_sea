#include<cstdio>
#include<cctype>
#include<set>
#include<algorithm>

#define lowbit(k) ((k)&(-(k)))

#define maxn 1001001

const int inf=1e9;

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

template<class T>

inline T max(T a,T b){
	return a>b?a:b;
}

struct Seg{
	int l,r,num;
	bool operator <(const Seg &seg) const{
		return l^seg.l?l<seg.l:r>seg.r;
	}
}seg[maxn];

int n,m,K,a[maxn],id[maxn],rk[maxn],ans[maxn];

namespace BIT{

	int c[maxn];

	inline void add(int k,int v){
		for(;k<=n;k+=lowbit(k))c[k]+=v;
	}

	inline int ask(int k){
		int Sum=0;
		for(;k;k^=lowbit(k))Sum+=c[k];
		return Sum;
	}

}

std::set<Seg> s;

std::set<std::pair<int,int> > Ls,Rs;

struct D{
	int val,pos,num;
	D() {val=-inf,pos=0,num=inf;}
	D(int val,int pos,int num):val(val),pos(pos),num(num) {}
	bool operator >(const D &d) const{return val>=d.val;}
};

namespace S_T{

#define ls (p<<1)
#define rs ((p<<1)|1)

	D Max[maxn<<2];

	int tag[maxn<<2];

	inline void update(int p,int v){
		Max[p].val+=v,tag[p]+=v;
	}

	inline void spread(int p){
		if(!tag[p])return;
		update(ls,tag[p]);
		update(rs,tag[p]);
		tag[p]=0;
	}

	void change(int p,int l,int r,int x,int v){
		if(l==r){
			Max[p]=D(v,l,seg[l].num);
			return;
		}
		spread(p);
		int mid=(l+r)>>1;
		if(x<=mid)change(ls,l,mid,x,v);
		else change(rs,mid+1,r,x,v);
		Max[p]=max(Max[ls],Max[rs]);
	}

	void add(int p,int l,int r,int L,int R,int v){
		if(L<=l&&r<=R)
			return update(p,v);
		spread(p);
		int mid=(l+r)>>1;
		if(L<=mid)add(ls,l,mid,L,R,v);
		if(R>mid)add(rs,mid+1,r,L,R,v);
		Max[p]=max(Max[ls],Max[rs]);
	}

	D ask(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return Max[p];
		spread(p);
		int mid=(l+r)>>1;
		if(R<=mid)return ask(ls,l,mid,L,R);
		if(L>mid)return ask(rs,mid+1,r,L,R);
		return max(ask(ls,l,mid,L,R),ask(rs,mid+1,r,L,R));
	}

	inline void Add(int l,int r,int v){
		if(l<=r)S_T::add(1,1,m,l,r,v);
	}

#undef ls
#undef rs

}

namespace ST{

#define ls (p<<1)
#define rs ((p<<1)|1)

	D Max[maxn<<2];

	int tag[maxn<<2];

	void build(int p,int l,int r){
		if(l==r){
			Max[p]={seg[l].r,l,seg[l].num};
			return;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		Max[p]=max(Max[ls],Max[rs]);
	}

	void change(int p,int l,int r,int x){
		if(l==r){
			Max[p]=D(-inf,0,0);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)change(ls,l,mid,x);
		else change(rs,mid+1,r,x);
		Max[p]=max(Max[ls],Max[rs]);
	}

	D ask(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return Max[p];
	    int mid=(l+r)>>1;
		if(R<=mid)return ask(ls,l,mid,L,R);
		if(L>mid)return ask(rs,mid+1,r,L,R);
		return max(ask(ls,l,mid,L,R),ask(rs,mid+1,r,L,R));
	}

	D query(int l,int r){
		return l>r?D():ask(1,1,m,l,r);
	}

#undef ls
#undef rs

}

bool up[maxn];

inline void Add(int i){
	int val=BIT::ask(seg[i].r)-BIT::ask(seg[i].l)+up[seg[i].l];
	S_T::change(1,1,m,i,val),s.insert(seg[i]);
	Ls.insert({seg[i].r,i}),Rs.insert({seg[i].l,i});
}

inline void add(int pos){
	up[pos]=1;
	int l,r,L,R;
	l=(*Ls.upper_bound({pos,0})).second;
	r=(*(--Rs.upper_bound({pos+1,0}))).second;
    L=(*Ls.upper_bound({pos+1,0})).second;
	R=(*(--Rs.upper_bound({pos,0}))).second;
	if(l==r&&seg[l].l==seg[r].r)S_T::Add(l,r,1);
	else{
		if(!(up[pos-1]|up[pos+1]))S_T::Add(L,R,1);
		if(!up[pos-1])S_T::Add(l,L-1,1);
		if(!up[pos+1])S_T::Add(R+1,r,1);
		if(up[pos-1]&up[pos+1])S_T::Add(L,R,-1);
	}
	/*
	if(!(up[pos-1]|up[pos+1]))S_T::Add(l,r,1);
	else if(!up[pos-1])S_T::Add(l,L-1,1);
	else if(!up[pos+1])S_T::Add(R+1,r,1);
	if(up[pos-1]&up[pos+1])S_T::Add(l,r,-1);
	else if(!up[pos-1])S_T::Add(R+1,r,-1);
	else if(!up[pos+1])S_T::Add(l,L-1,-1);
	*/
	if(pos>1&&a[pos-1]<a[pos])BIT::add(pos,1);
	if(pos<n&&a[pos]<a[pos+1])BIT::add(pos+1,-1);
}

inline void Del(int i){
	s.erase(seg[i]);
	Ls.erase({seg[i].r,i});
	Rs.erase({seg[i].l,i});
	ST::change(1,1,m,i);
	S_T::change(1,1,m,i,-inf);
	auto It=s.lower_bound(seg[i]);
	int R=It!=s.end()?rk[(*It).num]:m+1;
	D d=ST::query(1,R-1);
	while(d.pos&&d.pos>i)
		Add(d.pos),d=ST::query(1,d.pos-1);
}

int main(){
    //freopen("stone.in","r",stdin);
    //freopen("stone.out","w",stdout);
	n=read<int>();
	m=read<int>();
	K=read<int>();
	for(int i=1;i<=n;i++)
		a[i]=read<int>(),id[i]=i;
	for(int i=1;i<=m;i++){
		ans[i]=-1;
		seg[i].num=i;
		seg[i].l=read<int>();
		seg[i].r=read<int>();
	}
	std::sort(seg+1,seg+1+m);
	ST::build(1,1,m);
    for(int i=1,Max=-inf;i<=m;i++){
		rk[seg[i].num]=i;
		if(Max>=seg[i].r)continue;
		Max=seg[i].r,s.insert(seg[i]);
		Ls.insert({seg[i].r,i});
		Rs.insert({seg[i].l,i});
		S_T::change(1,1,m,i,0);
	}
	Ls.insert({n+1,n+1}),Rs.insert({0,0});
	std::sort(id+1,id+1+n,[&](int x,int y){
		return a[x]>a[y];
	});
	for(int l=1,r=0;l<=n;l=r+1){
		while(r<n&&a[id[r+1]]==a[id[l]])add(id[++r]);
		while(true){
			D d=S_T::Max[1];
			if(d.val<K)break;
		    ans[d.num]=a[id[l]],Del(d.pos);
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}