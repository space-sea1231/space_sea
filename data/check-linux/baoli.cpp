#include<bits/stdc++.h>
#define PII pair<int,int>
#define fi first
#define se second
#define int long long
using namespace std;
int n,m,x,y,z,t,dep[100001],dis[100001],dfn[100001],f[100001][21],sum,ans;
char op;
bool vis[100001];
vector<PII>G[100001];
set<PII>st;
void dfs(int u,int fa,int w){
    dep[u]=dep[fa]+1;
    dis[u]=dis[fa]+w;
    dfn[u]=++sum;
    f[u][0]=fa;
    for(int i=1;i<=20;i++) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i].se,w=G[u][i].fi;
        if(v==fa) continue;
        dfs(v,u,w);
    }
}
int lca(int x,int y){
    if(x==y) return x;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--){
        if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    }
    if(x==y) return x;
    for(int i=20;i>=0;i--){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
int getdis(int x,int y){
    return dis[x]+dis[y]-2*dis[lca(x,y)];
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>x>>y>>z;
        G[x].push_back({z,y});
        G[y].push_back({z,x});
    }
    dfs(1,0,0);
    cin>>m;
    while(m--){
        cin>>op;
        if(op=='+'||op=='-'){
            cin>>t;
            vis[t]=!vis[t];
            if(vis[t]) st.insert({dfn[t],t});
            auto it1=st.lower_bound({dfn[t],t}),it2=st.upper_bound({dfn[t],t});
            int a=(it1==st.begin()? (*--st.end()).se:(*--it1).se);
            int b=(it2==st.end()? (*st.begin()).se:(*it2).se);
            swap(a,b);
            if(!vis[t]) st.erase({dfn[t],t});
            int d=getdis(t,a)+getdis(t,b)-getdis(a,b);
            if(vis[t]) ans+=d;
            else ans-=d;
        }
        else cout<<ans/2<<endl;
    }
}