#include <bits/stdc++.h>
using namespace std;
int n,k,w[500010],fa[500010],dep[500010],to[500010],a,b,c,d,e,x,qc;
pair<int,int> f[500010],v[500010][3];
inline int lca(int u,int v) {
    if (dep[u]<dep[v]) swap(u,v);
    while (dep[u]>dep[v]) u=dep[to[u]]>=dep[v]?to[u]:fa[u];
    while (u!=v) if (to[u]==to[v]) u=fa[u],v=fa[v];
    else u=to[u],v=to[v];
    return u;
}
inline int near(int u,int v) {
    while (dep[u]>dep[v]+1) u=dep[to[u]]>dep[v]?to[u]:fa[u];
    return u;
}
inline int query(int u,int v) {
    pair<int,int> ans={2147483647,0};
    while (dep[u]>=dep[v]) u=dep[to[u]]>=dep[v]-1?ans=min(ans,f[u]),to[u]:(ans=min(ans,(pair<int,int>){w[u],u}),fa[u]);
    return ans.second;
}
struct T {
    int w,l,r;
    inline bool operator<(const T &o) const {
        return w>o.w;
    }
} t,q[2500010];
int main() {
    freopen("mooncake.in","r",stdin);
    freopen("mooncake.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    for (int i=1;i<=n;++i) cin>>w[i];
    f[1]={w[1],1};
    dep[0]=-1;
    for (int i=2;i<=n;++i) {
        cin>>fa[i];
        dep[i]=dep[fa[i]]+1;
        a=fa[i];
        b=to[a];
        c=to[b];
        if (b&&dep[a]-dep[b]==dep[b]-dep[c]) to[i]=c,f[i]=min({{w[i],i},f[a],f[b]});
        else to[i]=a,f[i]={w[i],i};
    }
    for (int i=1;i<=n;++i) {
        cin>>a>>b>>c;
        d=lca(a,b);
        e=lca(c,d);
        if (d==e) {
            d=lca(a,c);
            if (d==e) swap(a,b),d=lca(a,c);
            swap(b,c);
        }
        v[i][0]={e,a};
        if (c!=e) v[i][1]={near(c,e),c};
        if (b!=d) v[i][2]={near(b,d),b};
    }
    for (int i=1;i<=n;++i) q[i]={w[i],i,i};
    qc=n;
    make_heap(q+1,q+n+1);
    for (int i=1;i<=k;++i) {
        t=q[1];
        pop_heap(q+1,q+qc+1);
        --qc;
        cout<<t.w<<'\n';
        x=query(t.r,t.l);
        if (t.l!=x) {
            a=t.l;
            b=fa[x];
            c=query(b,a);
            q[++qc]={t.w-w[x]+w[c],a,b};
            push_heap(q+1,q+qc+1);
        }
        if (x!=t.r) {
            a=near(t.r,x);
            b=t.r;
            c=query(b,a);
            q[++qc]={t.w-w[x]+w[c],a,b};
            push_heap(q+1,q+qc+1);
        }
        for (auto j:v[x]) if (j.first) {
            a=j.first;
            b=j.second;
            c=query(b,a);
            q[++qc]={t.w+w[c],a,b};
            push_heap(q+1,q+qc+1);
        }
    }
}