#define NDEBUG
#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
#if 0
#define pr(...) fprintf(stderr,__VA_ARGS__)
#else
#define pr(...) void(0)
#endif

namespace IO{
const int BUF_SZ=1<<16;
char ib[BUF_SZ+1],*ip=ib+BUF_SZ;
void ipre(int n){
	int c=ib+BUF_SZ-ip;
	if(c<n){
		memcpy(ib,ip,c);
		ip=ib;
		fread(ib+c,1,BUF_SZ-c,stdin)[ib+c]=0;
	}
}
template<class T>
T read(T L,T R){
	ipre(100);
	T x=0,f=1;
	while(*ip<'0'||*ip>'9')if(*ip++=='-')f=-f;
	while(*ip>='0'&&*ip<='9')x=x*10+*ip++-'0';
	x*=f;
	if(!(L<=x&&x<=R)){
		std::cerr<<x<<" not in ["<<L<<","<<R<<"]\n";
		exit(1);
	}
	return x;
}
char ob[BUF_SZ+1],*op=ob;
void opre(int n){
	int c=ob+BUF_SZ-op;
	if(c<n){
		fwrite(ob,1,BUF_SZ-c,stdout);
		op=ob;
	}
}
template<class T>
void write(T x){
	opre(100);
	char ss[100],*sp=ss;
	if(x<T(0))x=-x,*op++='-';
	do *sp++=x%10+'0';while(x/=10);
	while(sp!=ss)*op++=*--sp;
}
template<class T>
void write(T x,char c){
	write(x);
	*op++=c;
}
struct __{
	__(){}
	~__(){
		fwrite(ob,1,op-ob,stdout);
	}
}_;
};

template<class T>
void alloc(T *&p,int sz,bool init=1){
	p=new T[sz]();
	return;
}

struct Void{
	char _[0];
	template<class T>
	friend void operator*=(T &,Void){}
	friend Void operator+(Void,Void){return Void();}
};

template<class D=Void,class M=Void>
struct MSegTree{
	struct Node{
		D d;
		M m;
		void app(const M &t){
			d*=t;
			m*=t;
		}
		void up(const Node &a,const Node &b){
			d=a.d+b.d;
			d*=m;
		}
	}*tr;
	int mx;
	int n;
	void in(int x){assert(1<=x&&x<=n);}
	void in(int l,int r){assert(1<=l&&l<=r&&r<=n);}
	void alloc(int n){
		for(mx=1;mx<n+2;mx<<=1);
		::alloc(tr,mx+n+3);
		this->n=n;
	}
	D &operator[](int x){
		in(x);
		return tr[mx+x].d;
	}
	void up(int x){
		tr[x].up(tr[x*2],tr[x*2+1]);
	}
	template<class T>
	void update(int x,T y){
		in(x);
		for(tr[x+=mx].d=y;x>1;up(x>>=1));
	}
	template<class T>
	int find_lm(T f){
		int x=1;
		while(x<mx){
			x<<=1;
			if(!f(tr[x].d,tr[x+1].d))++x;
		}
		x-=mx;
		return x;
	}
};

typedef long long i64;
const int maxn=1e6,maxm=1e6,inf=1e9,maxv=1e3,N=maxn+10,M=maxm+10;

using IO::read;
using IO::write;
using std::min;
using std::max;

namespace pmphms{
struct Tag{
	int mn,s0,s1;
	i64 smn;
	void operator*=(int t){
		mn=max(mn,t);
	}
	void operator*=(Tag t){
		assert(mn<t.mn||t.mn==0);
		smn+=t.smn;
		s1+=t.s1;
		if(!mn)s0+=t.s0;
		else{
			smn+=i64(t.s0)*mn;
			s1+=t.s0;
		}
		if(t.mn)mn=t.mn;
	}
	void clr(){
		mn=0;
		s0=0;
		s1=0;
		smn=0;
	}
}_op2{0,1,0,0};
struct Data{
	int mn,mn2,mnc;
	i64 s,ss;
	void operator*=(int t){
		assert(mn<t&&t<mn2);
		s+=i64(t-mn)*mnc;
		mn=t;
	}
	void operator*=(const Tag &t){
		if(t.mn==0&&t.s0==0&&t.s1==0&&t.smn==0)return;
		ss+=t.s0*s+mnc*t.smn+(s-i64(mn)*mnc)*t.s1;
		if(t.mn)*this*=t.mn;
	}
	void clr(){
		mn=0;
		mn2=inf;
		mnc=0;
		s=0;
		ss=0;
	}
	void up(Data a,Data b){
		if(a.mn==b.mn){
			mn=a.mn;
			mn2=min(a.mn2,b.mn2);
			mnc=a.mnc+b.mnc;
		}else if(a.mn<b.mn){
			mn=a.mn;
			mn2=min(a.mn2,b.mn);
			mnc=a.mnc;
		}else{
			mn=b.mn;
			mn2=min(b.mn2,a.mn);
			mnc=b.mnc;
		}
		s=a.s+b.s;
		ss=a.ss+b.ss;
	}
	operator i64(){
		return ss;
	}
};
int _l,_r,_v;
i64 _s;
struct Node{
	Node *lc,*rc;
	Tag tag;
	Data data;
	void app(Tag t){
		if(t.mn<=data.mn)t.mn=0,t.smn=t.s1*i64(data.mn);
		tag*=t;
		data*=t;
	}
	void dn(){
		lc->app(tag);
		rc->app(tag);
		tag.clr();
	}
	void up(){
		data.up(lc->data,rc->data);
	}
	void upd1(int L,int R){
		if(_v<=data.mn)return;
		if(_l<=L&&R<=_r&&_v<data.mn2){
			tag*=_v;
			data*=_v;
			assert(tag.mn==data.mn);
			return;
		}
		dn();
		int M=(L+R)>>1;
		if(_l<=M)lc->upd1(L,M);
		if(_r>M)rc->upd1(M+1,R);
		up();
	}
	void upd2(){
		app(_op2);
	}
	void ena(int L,int R,int x){
		if(L==R){
			assert(data.mnc==0);
			assert(data.s==0);
			data.mnc=1;
			data.s=data.mn;
			return;
		}
		dn();
		int M=(L+R)>>1;
		if(x<=M)lc->ena(L,M,x);
		else rc->ena(M+1,R,x);
		up();
	}
	void que(int L,int R){
		if(_l<=L&&R<=_r){
			_s+=data;
			return;
		}
		dn();
		int M=(L+R)>>1;
		if(_l<=M)lc->que(L,M);
		if(_r>M)rc->que(M+1,R);
	}
}ns[N*2],*np=ns,*rt;

Node *build(int L,int R){
	Node *w=np++;
	w->tag.clr();
	if(L==R){
		w->data.clr();
	}else{
		int M=(L+R)>>1;
		w->lc=build(L,M);
		w->rc=build(M+1,R);
		w->up();
	}
	return w;
}
}

struct LRMax{
	int lmx=0,rmx=0;
};
LRMax operator+(const LRMax &a,const LRMax &b){
	LRMax c;
	c.lmx=max(a.lmx,b.lmx);
	c.rmx=max(a.rmx,b.rmx);
	return c;
}

int T,n,m;
long tt;
struct Op{
	int dir,x,y1,y2,v;
}ops[N],ops0[N];
int opp=0;
struct Q{
	int x1,x2,y1,y2;
}qs[N];
struct Q0{
	int x,y1,y2,id,sgn;
}qs0[N*2];
struct Ev{
	int dir,x,y,v;
}es[N*2];
int pos[N];
struct Pos{
	int x,y;
}ps[N];
i64 ans[N];

template<class T,class F>
void rsort(T *d0,T *d1,int n,int v,F key){
	static int t[1<<20];
	F(i,0,v)t[i]=0;
	F(i,0,n)++t[key(d0[i])];
	int s=0;
	F(i,0,v){
		int a=t[i];
		t[i]=s;
		s+=a;
	}
	F(i,0,n)d1[t[key(d0[i])]++]=d0[i];
}
template<class T,class F>
void rsort2(T *d0,int n,F key){
	static char mem[1<<27];
	assert(sizeof(mem)>=sizeof(T)*n);
	T *d1=(T*)mem;
	rsort(d0,d1,n,2048,[&](T x){return key(x)&2047;});
	rsort(d1,d0,n,2048,[&](T x){return key(x)>>11;});
}

void solve(){
	using namespace pmphms;
	np=ns;
	rt=build(1,n);
	Fe(y,1,n)ps[y]=Pos{pos[y],y};
	rsort2(ps+1,n,[](Pos x){return x.x;});
	rsort2(ops0,opp,[](Op x){return x.x;});
	F(i,0,m){
		Q &q=qs[i];
		qs0[i]=Q0{q.x1-1,q.y1,q.y2,i,-1};
		qs0[i+m]=Q0{q.x2,q.y1,q.y2,i,1};
	}
	rsort2(qs0,m*2,[](Q0 a){return a.x;});
	long tt=clock();
	int p1=1,p2=0,p3=0;
	Fe(x,0,n){
		while(p1<=n&&ps[p1].x<=x){
			rt->ena(1,n,ps[p1++].y);
		}
		while(p2<opp&&ops0[p2].x<=x){
			auto &o=ops0[p2++];
			_l=o.y1;
			_r=o.y2;
			_v=o.v;
			rt->upd1(1,n);
		}
		rt->upd2();

		while(p3<m*2&&qs0[p3].x<=x){
			auto &q=qs0[p3++];
			_l=q.y1;
			_r=q.y2;
			_s=0;
			rt->que(1,n);
			ans[q.id]+=q.sgn*_s;
		}
	}
//	fprintf(stderr,"%.3fs\n",1.0*(clock()-tt)/CLOCKS_PER_SEC);
}
void rev(int &x){x=n+1-x;}
void work(){
	n=read(1,maxn);
	m=read(1,maxm);
	F(i,0,m)ans[i]=0;
	F(i,0,n){
		int x1=read(1,n),x2=read(x1,n);
		assert(x1==1||x2==n);
		int y1=read(1,n),y2=read(y1,n);
		int v=read(1,n);
		if(x1==1)ops[i]=Op{-1,x2,y1,y2,v};
		else ops[i]=Op{1,x1,y1,y2,v};
	}
	F(i,0,n){
		auto &o=ops[i];
		es[i]=Ev{o.dir,o.x,o.y1*2,o.v};
		es[i+n]=Ev{o.dir,o.x,o.y2*2+1,-o.v};
	}
	rsort2(es,n*2,[](Ev a){return a.y;});
	std::vector<std::multiset<int>> st1,st2;
	st1.resize(n+2);
	st2.resize(n+2);
	MSegTree<LRMax> tr;
	tr.alloc(n+2);
	int p=0;
	Fe(y,1,n){
		while(p<n*2&&es[p].y<=y*2){
			auto &e=es[p++];
			int x=e.x;
			if(e.dir==-1)++x;
			auto v=tr[x];
			auto &st=(e.dir==-1?st1:st2).at(x);
			if(e.v>0){
				st.insert(e.v);
				(e.dir==-1?v.lmx:v.rmx)=*--st.end();
			}else{
				auto it=st.find(-e.v);
				assert(it!=st.end());
				st.erase(it);
				(e.dir==-1?v.lmx:v.rmx)=(st.empty()?0:*--st.end());
			}
			tr.update(x,v);
		}
		int rmx=0,lmx=0;
		int x0=tr.find_lm([&](const LRMax &a,const LRMax &b){
			int rmx0=max(rmx,a.rmx),lmx0=max(lmx,b.lmx);
			if(rmx0<lmx0){
				rmx=rmx0;
				return 0;
			}else{
				lmx=lmx0;
				return 1;
			}
		});
		pos[y]=x0;
	}
//	fprintf(stderr,"%.3fs\n",1.0*(clock()-tt)/CLOCKS_PER_SEC);
	F(i,0,m){
		int x1=read(1,n),x2=read(x1,n);
		int y1=read(1,n),y2=read(y1,n);
		qs[i]=Q{x1,x2,y1,y2};
	}
	opp=0;
	F(i,0,n)if(ops[i].dir==1)ops0[opp++]=ops[i];
	solve();
	F(i,0,m){
		Q &q=qs[i];
		rev(q.x1);
		rev(q.x2);
		std::swap(q.x1,q.x2);
	}
	Fe(y,1,n)rev(pos[y]),++pos[y];
	opp=0;
	F(i,0,n)if(ops[i].dir==-1)ops0[opp++]=ops[i];
	F(i,0,opp)rev(ops0[i].x);
	solve();
	F(i,0,m)IO::write(ans[i],'\n');
	delete[]tr.tr;
}
int main(){
	tt=clock();
	T=read(1,50);
	while(T--)work();
//	std :: cerr << clock() << " ms" << std :: endl;
	return 0;
}
