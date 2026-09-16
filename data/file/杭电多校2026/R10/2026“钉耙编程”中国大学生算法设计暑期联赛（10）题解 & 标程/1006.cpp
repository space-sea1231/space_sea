#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define int ll
#define F(i,a,b) for(int (i)=(a);(i)<=(b);++(i))
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int N=200005;
struct Seg
{
	int lv,rv,cnt;
	int set,rev;
}tr[N<<2];
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
il void pushup(int rt)
{
	tr[rt].lv=tr[ls].lv;
	tr[rt].rv=tr[rs].rv;
	tr[rt].cnt=tr[ls].cnt+tr[rs].cnt+(tr[ls].rv!=tr[rs].lv);
}
il void apply_set(int rt,int x)
{
	tr[rt].lv=tr[rt].rv=x;
	tr[rt].cnt=0;
	tr[rt].set=x;
	tr[rt].rev=0;
}
il void apply_rev(int rt)
{
	tr[rt].lv^=1;
	tr[rt].rv^=1;
	if(tr[rt].set!=-1) tr[rt].set^=1;
	else tr[rt].rev^=1;
}
il void pushdown(int rt)
{
	if(tr[rt].set!=-1)
	{
		apply_set(ls,tr[rt].set);
		apply_set(rs,tr[rt].set);
		tr[rt].set=-1;
	}
	if(tr[rt].rev)
	{
		apply_rev(ls);
		apply_rev(rs);
		tr[rt].rev=0;
	}
}
void build(int rt,int l,int r,int a[])
{
	tr[rt].set=-1;
	tr[rt].rev=0;
	if(l==r)
	{
		tr[rt].lv=tr[rt].rv=a[l];
		tr[rt].cnt=0;
		return;
	}
	build(ls,l,mid,a);
	build(rs,mid+1,r,a);
	pushup(rt);
}
void update_set(int rt,int l,int r,int L,int R,int x)
{
	if(L<=l&&r<=R){apply_set(rt,x);return;}
	pushdown(rt);
	if(L<=mid) update_set(ls,l,mid,L,R,x);
	if(R>mid) update_set(rs,mid+1,r,L,R,x);
	pushup(rt);
}
void update_rev(int rt,int l,int r,int L,int R)
{
	if(L<=l&&r<=R){apply_rev(rt);return;}
	pushdown(rt);
	if(L<=mid) update_rev(ls,l,mid,L,R);
	if(R>mid) update_rev(rs,mid+1,r,L,R);
	pushup(rt);
}
Seg query(int rt,int l,int r,int L,int R)
{
	if(L<=l&&r<=R) return tr[rt];
	pushdown(rt);
	if(R<=mid) return query(ls,l,mid,L,R);
	if(L>mid) return query(rs,mid+1,r,L,R);
	Seg left=query(ls,l,mid,L,R);
	Seg right=query(rs,mid+1,r,L,R);
	Seg res;
	res.lv=left.lv;
	res.rv=right.rv;
	res.cnt=left.cnt+right.cnt+(left.rv!=right.lv);
	return res;
}
int a[N];
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read(),m=read();
		F(i,1,n) a[i]=read();
		build(1,1,n,a);
		while(m--)
		{
			int op=read(),l=read(),r=read();
			if(op==1)
			{
				int x=read();
				update_set(1,1,n,l,r,x);
			}
			else if(op==2)
			{
				update_rev(1,1,n,l,r);
			}
			else
			{
				Seg ans=query(1,1,n,l,r);
				printf("%lld\n",ans.cnt);
			}
		}
	}
	return 0;
}
