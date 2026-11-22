#include <bits/stdc++.h>
using namespace std;
namespace IO{
    const int BUF=1<<21;
    char buff[BUF],*p1=buff,*p2=buff;
    #define gc() (p1==p2&&(p2=((p1=buff)+fread(buff,1,BUF,stdin)),p1==p2)?EOF:*p1++)
    template<typename T>inline void read(T &x){
        char ch=gc();x=0;int f=1;
        while(!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
        while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=gc();
        x*=f;
    }
    char obuf[BUF],*p3=obuf;
    inline void pc(char ch){
        if(p3-obuf<BUF) *p3++=ch;
        else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
    }
    inline void put(const char *s){while(*s) pc(*s),++s;}
    char ch[64];int ctop;
    template<typename T>inline void print(T x){
    	if(x<0) x=~x+1,pc('-');
        if(!x) return pc(48);
        while(x) ch[++ctop]=x%10^48,x/=10;
        while(ctop) pc(ch[ctop--]);
    }
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);p3=obuf;}
}
using namespace IO;
const int N = 1e6+5;
int n,m,q,a[N],id[N],ans[N];
vector<pair<int,int>> vec[N];
namespace bit{
	int t[N];
	#define lowbit(x) (x&(-x))
	inline void add(int x,int v)
	{
		for(;x<=n;x+=lowbit(x))
			t[x]+=v;
	}
	inline int ask(int x)
	{
		int res = 0;
		for(;x;x-=lowbit(x))
			res+=t[x];
		return res; 
	}
}
struct node{
	int mx,tag;
}t[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
#define pushup(k) (t[k].mx = max(t[ls].mx,t[rs].mx))
inline void add(int k,int v){t[k].mx+=v,t[k].tag+=v;}
inline void down(int k)
{
	if(!t[k].tag) return;
	add(ls,t[k].tag),add(rs,t[k].tag);
	t[k].tag = 0;
}
void build(int k,int l,int r)
{
	t[k].mx = -2e9;
	if(l==r) return;
	int mid = (l+r)/2;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void del(int k,int l,int r)
{
	if(l==r) return t[k].mx = -2e9,bit::add(id[l],-1);
	int mid = (l+r)/2;
	down(k);
	if(t[ls].mx>=m) del(ls,l,mid);
	if(t[rs].mx>=m) del(rs,mid+1,r);
	pushup(k);
}
void change(int k,int l,int r,int x)
{
	if(l==r) return t[k].mx = 0,void();
	int mid = (l+r)/2; 
	down(k);
	if(mid>=x)
	{
		change(ls,l,mid,x),add(rs,1);
		if(t[rs].mx>=m) del(rs,mid+1,r);
	}
	else change(rs,mid+1,r,x);
	pushup(k); 
}
signed main()
{
	freopen("devil.in","r",stdin);
	freopen("devil.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	read(n),read(m),read(q);
	for(int i = 1;i<=n;i++)
		read(a[i]),id[a[i]] = i;
	for(int i = 1,l,r;i<=q;i++)
		read(l),read(r),vec[l].push_back({r,i});
	build(1,1,n);
	for(int i = n;i;i--)
	{
		bit::add(i,1);
		change(1,1,n,a[i]);
		for(auto _:vec[i])
		{
			int r = _.first,id = _.second;
			ans[id] = bit::ask(r);
		}
	}
	for(int i = 1;i<=q;i++) print(ans[i]),pc('\n');
	flush();
	return 0;
}

