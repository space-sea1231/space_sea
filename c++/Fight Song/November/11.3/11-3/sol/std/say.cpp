#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5,inf = 2e9;
int n,q,f[N],rt1[N],rt2[N],a[N],ans[N],suf[N],stk[N],top;
pair<int,int> st[20][N];
inline pair<int,int> ask(int l,int r)
{
	int lg = __lg(r-l+1);
	return min(st[lg][l],st[lg][r-(1<<lg)+1]);
}
vector<pair<int,int>> vecq[N];
struct node{
	int sz;
	pair<int,int> res,tmp;
	int tag1,tag2;
}t[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
inline void pushup(int k)
{
	t[k].sz = t[ls].sz+t[rs].sz;
	t[k].res = min(t[ls].res,t[rs].res);
}
inline void cover1(int k,int l,int r,int v){t[k].res = t[k].tmp,t[k].res.first+=v,t[k].sz = r-l+1,t[k].tag1 = v,t[k].tag2 = 0;}
inline void cover2(int k,int l,int r){t[k].res = {inf,l},t[k].sz = 0,t[k].tag1 = 0,t[k].tag2 = 1;}
inline void down(int k,int l,int r,int mid)
{
	if(t[k].tag1)
	{
		cover1(ls,l,mid,t[k].tag1),cover1(rs,mid+1,r,t[k].tag1);
		t[k].tag1 = 0;
	}
	if(t[k].tag2)
	{
		cover2(ls,l,mid),cover2(rs,mid+1,r);
		t[k].tag2 = 0;
	}
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		t[k].res.first = (rt1[l+1]>=rt2[l]?inf:rt1[l+1]-(l+1));
		t[k].res.second = l;
		t[k].sz = 1;
		t[k].tmp = t[k].res;
		return;
	}
	int mid = (l+r)/2;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
	t[k].tmp = t[k].res;
}
void change(int k,int l,int r,int x,int v)
{
	if(l==r) return t[k].res.first = v,void();
	int mid = (l+r)/2;
	down(k,l,r,mid);
	if(mid>=x) change(ls,l,mid,x,v);
	else change(rs,mid+1,r,x,v);
	pushup(k);
}
void change1(int k,int l,int r,int x,int y,int v)
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return cover1(k,l,r,v);
	int mid = (l+r)/2;
	down(k,l,r,mid);
	change1(ls,l,mid,x,y,v),change1(rs,mid+1,r,x,y,v);
	pushup(k);
}
void change2(int k,int l,int r,int x,int y)
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return cover2(k,l,r);
	int mid = (l+r)/2;
	down(k,l,r,mid);
	change2(ls,l,mid,x,y),change2(rs,mid+1,r,x,y);
	pushup(k);
}
int ask(int k,int l,int r,int x)
{
	if(l>x) return 0;
	if(r<=x) return t[k].sz;
	int mid = (l+r)/2;
	down(k,l,r,mid);
	return ask(ls,l,mid,x)+ask(rs,mid+1,r,x);
}
int askp(int k,int l,int r,int x)
{
	if(l==r) return l;
	int mid = (l+r)/2;
	down(k,l,r,mid);
	if(t[ls].sz>=x) return askp(ls,l,mid,x);
	else return askp(rs,mid+1,r,x-t[ls].sz);
}
signed main()
{
	freopen("say.in","r",stdin);
	freopen("say.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i = 1;i<=n;i++)
		cin>>a[i],f[i] = i+1,st[0][i] = {a[i],i};
	for(int j = 1;j<20;j++)
		for(int i = 1;i+(1<<j)-1<=n;i++)
			st[j][i] = min(st[j-1][i],st[j-1][i+(1<<j-1)]);
	for(int i = n;i;i--)
	{
		if(i<n) suf[i] = suf[i+1];
		suf[i] = max(suf[i],a[i]);
	}
	stk[top = 0] = rt1[n+1] = inf;
	for(int i = n;i;i--)
	{
		while(top&&a[stk[top]]>a[i]) top--;
		rt1[i] = stk[top],stk[++top] = i;
	}
	stk[top = 0] = inf;
	for(int i = n;i;i--)
	{
		while(top&&a[stk[top]]<a[i]) top--;
		rt2[i] = stk[top],stk[++top] = i;
	}
	for(int i = 1,x,y;i<=q;i++)
		cin>>x>>y,vecq[x].push_back({y,i});
	build(1,1,n);
	int tag = 0;
	for(int i = n;i;i--)
	{
		if(i!=n)
		{
			tag++;
			if(t[1].res.first==tag)
			{
				int p = t[1].res.second;
				int sz = ask(1,1,n,p-1)+1;
				int f = rt1[ask(p+1,n-i+sz).second];
				if(f<=n&&rt1[f]<rt2[p]&&rt1[f]<=n) change(1,1,n,p,rt1[f]-(n-i+sz+1)+tag);
				else change(1,1,n,p,inf);
				change1(1,1,n,f,n,tag);
				change2(1,1,n,p+1,f-1);
			}
		}
		for(auto _:vecq[i])
		{
			int y = _.first,id = _.second;
			if(y!=i) ans[id] = a[askp(1,1,n,y)];
			else
			{
				if(i==1) ans[id] = suf[1];
				else ans[id] = suf[min(n,rt2[askp(1,1,n,y-1)])];
			}
		}
	}
	for(int i = 1;i<=q;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
