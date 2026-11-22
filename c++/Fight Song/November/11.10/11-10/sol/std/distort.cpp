#include<iostream>
#include<vector>

using namespace std;

const int inf=1e9;

int n,m;
int a[400005];
vector<int>vec[400005];

bool vis[400005];
int siz[400005];
static inline void dfs(int u,int fa){
    siz[u]=1;
    for(auto v:vec[u]){
        if(vis[v]||v==fa)
            continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
}
static inline int dfs(int u,int fa,int rt){
    int mx=siz[rt]-siz[u];
    for(auto v:vec[u]){
        if(vis[v]||v==fa)
            continue;
        int x=dfs(v,u,rt);
        if(x)
            return x;
        mx=max(mx,siz[v]);
    }
    if(2*mx<=siz[rt])
        return u;
    return 0;
}

int dep[400005];
int g[400005];
int h[400005];
int mxd[400005];
static inline void dfs2(int u,int fa){
    mxd[u]=dep[u];
    g[u]=min(g[fa],a[u]-dep[u]);
    h[u]=min(h[fa],a[u]+dep[u]);
    for(auto v:vec[u]){
        if(vis[v]||v==fa)
            continue;
        dep[v]=dep[u]+1;
        dfs2(v,u);
        mxd[u]=max(mxd[u],mxd[v]);
    }
}
vector<int>vt;
static inline void dfs3(int u,int fa){
    vt.push_back(u);
    for(auto v:vec[u]){
        if(vis[v]||v==fa)
            continue;
        dfs3(v,u);
    }
}
int d[400005];
int d1[400005];
int d2[400005];
int d3[400005];
int ans[400005];
static inline void dfs4(int u,int fa){
    if(h[u]>dep[u])
        ans[u]+=d[dep[u]];
    else
        ans[u]+=d1[dep[u]];
    for(auto v:vec[u]){
        if(vis[v]||v==fa)
            continue;
        dfs4(v,u);
    }
}

static inline void solve(int u){
    dfs(u,0);
    int rt=dfs(u,0,u);
    dep[rt]=0;
    dfs2(rt,0);
    for(int i=0;i<=mxd[rt];++i)
        d2[i]=d3[i]=0;
    for(auto v:vec[rt]){
        if(vis[v])
            continue;
        vt.clear();
        dfs3(v,rt);
        for(int i=0;i<=mxd[v];++i)
            d[i]=d1[i]=0;
        for(auto x:vt){
            int l=max(g[x],1),r=m-dep[x];
            if(l<=r){
                --d[l],++d[r+1];
                ++d2[l],--d2[r+1];
            }
            if(dep[x]<=m){
                --d1[1],++d1[m-dep[x]+1];
                ++d3[1],--d3[m-dep[x]+1];
                if(g[x]<=0)
                    ++ans[rt];
                if(h[x]<=dep[x])
                    ++ans[x];
            }
        }
        for(int i=1;i<=mxd[v];++i){
            d[i]+=d[i-1];
            d1[i]+=d1[i-1];
        }
        dfs4(v,rt);
    }
    for(int i=0;i<=mxd[rt];++i){
        d[i]=d2[i];
        d1[i]=d3[i];
    }
    for(int i=1;i<=mxd[rt];++i){
        d[i]+=d[i-1];
        d1[i]+=d1[i-1];
    }
    for(auto v:vec[rt])
        if(!vis[v])
            dfs4(v,rt);
    vis[rt]=true;
    for(auto v:vec[rt])
        if(!vis[v])
            solve(v);
}

signed main(){
    freopen("distort.in","r",stdin);
    freopen("distort.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    g[0]=h[0]=inf;
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(!a[i])
            ++ans[i];
    }
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    solve(1);
    for(int i=1;i<=n;++i)
        cout<<ans[i]<<'\n';
    return 0;
}
