#include<cstdio>
#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<utility>
#define RI register int
#define CI const int&
#define fi first
#define se second
using namespace std;
typedef pair <int,int> pi;
const int N=200005;
int t,n,q,a[N],pos[N],seq[N],dfn[N],dfnr[N],opt,x,y; vector <int> v[N];
#define TN CI now=1,CI l=1,CI r=n
#define LS now<<1,l,mid
#define RS now<<1|1,mid+1,r
class Segment_Tree1
{
	private:
		pi mxdfn[N<<2],mndfnr[N<<2],mxdfnr[N<<2];
        inline void pushup(CI now)
        {
            mxdfn[now]=max(mxdfn[now<<1],mxdfn[now<<1|1]);
            mndfnr[now]=min(mndfnr[now<<1],mndfnr[now<<1|1]);
            mxdfnr[now]=max(mxdfnr[now<<1],mxdfnr[now<<1|1]);
        }
	public:
		inline void build(TN)
		{
			if (l==r)
            {
                int x=pos[l]; mxdfn[now]={dfn[x],x};
                mndfnr[now]=mxdfnr[now]={dfnr[x],x};
                return;
            }
			int mid=l+r>>1; build(LS); build(RS); pushup(now);
		}
		inline void update(CI pos,CI ndfn,CI ndfnr,CI num,TN)
		{
			if (l==r)
            {
                mndfnr[now]=mxdfnr[now]={ndfnr,num};
                mxdfn[now]={ndfn,num}; return;
            }
            int mid=l+r>>1;
			if (pos<=mid) update(pos,ndfn,ndfnr,num,LS); else update(pos,ndfn,ndfnr,num,RS);
            pushup(now);
		}
		inline pi query_maxdfn(CI beg,CI end,TN)
		{
			if (beg<=l&&r<=end) return mxdfn[now]; int mid=l+r>>1;
            if (end<=mid) return query_maxdfn(beg,end,LS);
            if (beg>mid) return query_maxdfn(beg,end,RS);
            return max(query_maxdfn(beg,end,LS),query_maxdfn(beg,end,RS));
		}
		inline pi query_mindfnr(CI beg,CI end,TN)
		{
			if (beg<=l&&r<=end) return mndfnr[now]; int mid=l+r>>1;
            if (end<=mid) return query_mindfnr(beg,end,LS);
            if (beg>mid) return query_mindfnr(beg,end,RS);
            return min(query_mindfnr(beg,end,LS),query_mindfnr(beg,end,RS));
		}
		inline pi query_maxdfnr(CI beg,CI end,TN)
		{
			if (beg<=l&&r<=end) return mxdfnr[now]; int mid=l+r>>1;
            if (end<=mid) return query_maxdfnr(beg,end,LS);
            if (beg>mid) return query_maxdfnr(beg,end,RS);
            return max(query_maxdfnr(beg,end,LS),query_maxdfnr(beg,end,RS));
		}
}SEG1;
class Segment_Tree2
{
	private:
		int mn[N<<2],mx[N<<2];
        inline void pushup(CI now)
        {
            mn[now]=min(mn[now<<1],mn[now<<1|1]);
            mx[now]=max(mx[now<<1],mx[now<<1|1]);
        }
	public:
		inline void build(TN)
		{
			if (l==r) return (void)(mn[now]=mx[now]=a[seq[l]]);
			int mid=l+r>>1; build(LS); build(RS); pushup(now);
		}
		inline void update(CI pos,CI mv,TN)
		{
			if (l==r) return (void)(mn[now]=mx[now]=mv); int mid=l+r>>1;
			if (pos<=mid) update(pos,mv,LS); else update(pos,mv,RS);
            pushup(now);
		}
		inline int query_min(CI beg,CI end,TN)
		{
			if (beg<=l&&r<=end) return mn[now]; int mid=l+r>>1;
            if (end<=mid) return query_min(beg,end,LS);
            if (beg>mid) return query_min(beg,end,RS);
            return min(query_min(beg,end,LS),query_min(beg,end,RS));
		}
		inline int query_max(CI beg,CI end,TN)
		{
			if (beg<=l&&r<=end) return mx[now]; int mid=l+r>>1;
            if (end<=mid) return query_max(beg,end,LS);
            if (beg>mid) return query_max(beg,end,RS);
            return max(query_max(beg,end,LS),query_max(beg,end,RS));
		}
}SEG2;
#undef TN
#undef LS
#undef RS
namespace Heavy_Division
{
    int idx,idxr,top[N],dep[N],sz[N],anc[N],son[N];
    inline void DFS1(CI now=1,CI fa=0)
    {
        son[now]=0; sz[now]=1; dep[now]=dep[fa]+1; anc[now]=fa;
        for (int to:v[now]) if (to!=fa)
        {
            DFS1(to,now); sz[now]+=sz[to];
            if (sz[to]>sz[son[now]]) son[now]=to;
        }
    }
    inline void DFS2(CI now=1,CI tf=1)
    {
        seq[dfn[now]=++idx]=now; top[now]=tf;
        if (son[now]) DFS2(son[now],tf);
        for (int to:v[now]) if (to!=anc[now]&&to!=son[now]) DFS2(to,to);
        dfnr[now]=++idxr;
    }
    inline bool query_path(int x,int y,CI L,CI R)
    {
    	int ret=0;
    	while (top[x]!=top[y])
    	{
    		if (dep[top[x]]<dep[top[y]]) swap(x,y);
    		if (SEG2.query_min(dfn[top[x]],dfn[x])<L) return 0;
            if (SEG2.query_max(dfn[top[x]],dfn[x])>R) return 0;
    		x=anc[top[x]];
    	}
    	if (dep[x]<dep[y]) swap(x,y);
        if (SEG2.query_min(dfn[y],dfn[x])<L) return 0;
        if (SEG2.query_max(dfn[y],dfn[x])>R) return 0;
		return 1;
    }
    inline int LCA(int x,int y)
    {
    	while (top[x]!=top[y])
    	{
    		if (dep[top[x]]<dep[top[y]]) swap(x,y);
    		x=anc[top[x]];
    	}
    	if (dep[x]<dep[y]) swap(x,y);
		return y;
    }
    inline int getdis(CI x,CI y)
    {
        return dep[x]+dep[y]-2*dep[LCA(x,y)];
    }
};
using namespace Heavy_Division;
int main()
{
    int size(256<<20); //256M
    __asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
    ios::sync_with_stdio(0); cin.tie(0);
	for (cin>>t;t;--t)
	{
		RI i; for (cin>>n,i=1;i<=n;++i) cin>>a[i],pos[a[i]]=i;
		for (i=1;i<n;++i) cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
		DFS1(); DFS2(); SEG1.build(); SEG2.build();
		for (cin>>q;q;--q)
		{
            cin>>opt>>x>>y;
            if (opt==1)
            {
                int u=a[x],v=a[y];
                SEG1.update(a[x],dfn[y],dfnr[y],y);
                SEG1.update(a[y],dfn[x],dfnr[x],x);
                SEG2.update(dfn[x],a[y]);
                SEG2.update(dfn[y],a[x]);
                swap(a[x],a[y]); swap(pos[u],pos[v]);
            } else
            {
                int u=SEG1.query_maxdfn(x,y).se,v=SEG1.query_mindfnr(x,y).se;
                cerr<<u<<" " << v << endl;
                if (u==v) v=SEG1.query_maxdfnr(x,y).se;
                cout<<(getdis(u,v)==y-x&&query_path(u,v,x,y)?"Yes\n":"No\n");
            }
		}
		for (idx=idxr=0,i=1;i<=n;++i) v[i].clear();
	}
    exit(0);
	return 0;
}