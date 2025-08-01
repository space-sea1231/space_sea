#include<iostream>
#define lc now<<1
#define rc now<<1|1
#define int long long
using namespace std;
const int N=5e5+5;
struct node
{
	int sum,d;
};
node tree[N<<2];
int cf[N],a[N];
int n,m;
inline int read()
{
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9')
	{  if(ch=='-')  w=-1;  ch=getchar();}
	while(ch>='0'&&ch<='9')
	{  s=s*10+ch-'0'; ch=getchar();}
	return s*w;
}
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
void push_up(int now)
{
	tree[now].sum=tree[lc].sum+tree[rc].sum;
	tree[now].d=gcd(tree[lc].d,tree[rc].d);
}
void build(int now,int l,int r)
{
	if(l==r)
	{
		tree[now].sum=tree[now].d=cf[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	push_up(now);
}
void update(int now,int l,int r,int pos,int v)
{
	if(l==r)
	{
		tree[now].sum+=v;
		tree[now].d+=v;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)  update(lc,l,mid,pos,v);
	else update(rc,mid+1,r,pos,v);
	push_up(now);
}
node merga(node a,node b)
{
	node res;
	res.sum=a.sum+b.sum;
	res.d=gcd(a.d,b.d);
	return res;
}
node query(int now,int l,int r,int L,int R)
{
	if(l>=L&&r<=R)
		return tree[now];
	int mid=(l+r)>>1;
	if(R<=mid)  return query(lc,l,mid,L,R);
	if(L>mid)   return query(rc,mid+1,r,L,R);
	return merga(query(lc,l,mid,L,R),query(rc,mid+1,r,L,R));
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),cf[i]=a[i]-a[i-1];
	build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		char ch;
		cin>>ch;
		if(ch=='C')
		{
			int l=read(),r=read(),d=read();
			update(1,1,n,l,d);
			if(r<n)  update(1,1,n,r+1,-d);
		}
		if(ch=='Q')
		{
			int l=read(),r=read();
			node Lres=query(1,1,n,1,l);
			node Rres=(node){0,0};
			if(l+1<=r)  Rres=query(1,1,n,l+1,r);
			cout<<abs(gcd(Lres.sum, Rres.d)) <<endl;
		}
	}
	return 0;
}