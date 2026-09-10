#include<bits/stdc++.h>
#define N 300005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,now,to,cnt,rt[N];
struct tree
{
	int ls,rs,fa,dep;
}tr[N*20];
inline int build(int l,int r)
{
	int to=++cnt;
	if(l==r)
	{
		tr[to].fa=l;
		return to;
	}
	int mid=(l+r)>>1;
	tr[to].ls=build(l,mid);
	tr[to].rs=build(mid+1,r);
	return to;
}
inline int que(int now,int l,int r,int x)
{
	if(l==r)return now;
	int mid=(l+r)>>1;
	if(mid>=x)return que(tr[now].ls,l,mid,x);
	else return que(tr[now].rs,mid+1,r,x);
}
inline int find(int now,int a)
{
	int fa=que(rt[now],1,n,a);
	if(tr[fa].fa==a)return fa;
	return find(now,tr[fa].fa);
}
inline int news(int now)
{
	int to=++cnt;
	tr[to]=tr[now];
	return to;
}
inline int hb(int now,int l,int r,int x,int f)
{
	int to=news(now);
	if(l==r)
	{
		tr[to].fa=f;
		return to;
	}
	int mid=(l+r)>>1;
	if(mid>=x)tr[to].ls=hb(tr[now].ls,l,mid,x,f);
	else tr[to].rs=hb(tr[now].rs,mid+1,r,x,f);
	return to;
}
inline int add(int now,int l,int r,int x)
{
	int to=news(now); 
	if(l==r)
	{
		tr[to].dep++;
		return to;
	}
	int mid=(l+r)>>1;
	if(mid>=x)tr[to].ls=add(tr[now].ls,l,mid,x);
	else tr[to].rs=add(tr[now].rs,mid+1,r,x);
	return to;
}
inline void merge(int now,int a,int b)
{
	rt[now]=rt[now-1];
	a=find(now,a);b=find(now,b);
	if(tr[a].fa!=tr[b].fa)
	{
		if(tr[a].dep>tr[b].dep)swap(a,b);
		rt[now]=hb(rt[now-1],1,n,tr[a].fa,tr[b].fa);
		if(tr[a].dep==tr[b].dep)rt[now]=add(rt[now],1,n,tr[b].fa);
	} 
}
inline bool pan(int now,int a,int b)
{
	a=find(now,a),b=find(now,b);
	if(tr[a].fa==tr[b].fa)return 1;
	else return 0;
}
int main()
{
	n=read();m=read();
	rt[0]=build(1,n);
	int op,a,b;
	for(int i=1;i<=m;i++)
	{
		op=read();a=read();
		if(op==1)
		{
			b=read();
			merge(i,a,b);
		}
		if(op==2)rt[i]=rt[a];
		if(op==3)
		{
			b=read();
			if(pan(i-1,a,b))cout<<1<<"\n";
			else cout<<0<<"\n";
			rt[i]=rt[i-1];
		}
	}
	return 0;
}
