#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const ll INF=4e18;

struct Edge{
    int v;
    ll w;
};

struct DP{
    ll f0=0;
    vector<ll>d;
};

int n,K;
vector<int>a,b,p,fa;
vector<ll>sub,pw;
vector<vector<Edge>>g;

vector<ll> merge_dp(const vector<ll>&a,const vector<ll>&b){
    vector<ll>c;
    int i=0,j=0;
    c.reserve(min(K,(int)a.size()+(int)b.size()));
    while((int)c.size()<K&&(i<(int)a.size()||j<(int)b.size())){
        if(j==(int)b.size()||(i<(int)a.size()&&a[i]<=b[j])) c.push_back(a[i++]);
        else c.push_back(b[j++]);
    }
    return c;
}

void dfs1(int u,int f,ll w){
    fa[u]=f; pw[u]=w; sub[u]=a[u];
    for(auto [v,c]:g[u]){
        if(v==f)continue;
        dfs1(v,u,c);
        sub[u]+=sub[v];
    }
}

DP dfs2(int u,bool root=false){
    int v=p[u]; DP f;
    for(auto [x,w]:g[u]){
        if(fa[x]!=u)continue;
        DP t=dfs2(x);
        f.f0+=t.f0;
        f.d=merge_dp(f.d,t.d);
    }

    int cap=min(b[u],b[v]);
    f.d=merge_dp(f.d,vector<ll>(min(K,cap),0));

    if(root)return f;
    f.f0+=pw[u]*sub[u]+pw[v]*sub[v];
    for(int i=0;i<(int)f.d.size();i++){
        int s=i+1;
        f.d[i]+=(s<=sub[u]?-pw[u]:pw[u]);
        f.d[i]+=(s<=sub[v]?-pw[v]:pw[v]);
    }
    return f;
}

ll get(DP f,int x){
    if(x>(int)f.d.size())return INF;
    for(int i=0;i<x;i++) f.f0+=f.d[i];
    return f.f0;
}

ll solve(){
    cin>>n; a.resize(n+1); b.resize(n+1); p.resize(n+1);
    ll W=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        W+=a[i];
    }
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++)cin>>p[i];
    g.assign(n+1,{});
    vector<tuple<int,int,ll>>edges;
    for(int i=1,u,v;i<n;i++){
        ll w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
        edges.push_back({u,v,w});
    }

    int center=0,x=0,y=0;
    ll center_w=0;

    for(int i=1;i<=n;i++) if(p[i]==i) center=i;

    if(!center){
        if(W&1)return -1;
        for(auto [u,v,w]:edges){
            if(p[u]==v){
                x=u; y=v;
                center_w=w;
                break;
            }
        }
    }

    fa.assign(n+1,0);
    pw.assign(n+1,0);
    sub.assign(n+1,0);

    K=W/2;

    if(center){
        dfs1(center,0,0);
        DP f;
        for(auto [u,w]:g[center]){
            if(u>p[u])continue;
            DP t=dfs2(u);
            f.f0+=t.f0;
            f.d=merge_dp(f.d,t.d);
        }

        int L=max(0,(int)((W-b[center]+1)/2));
        ll ans=INF;
        ll cur=f.f0;
        if(L==0)ans=cur;
        for(int s=1;s<=(int)f.d.size();s++){
            cur+=f.d[s-1];
            if(s>=L) ans=min(ans,cur);
        }
        return ans==INF?-1:ans;
    }

    dfs1(x,y,0);
    dfs1(y,x,0);
    fa[x]=fa[y]=0;
    DP f=dfs2(x,true);
    ll ans=get(f,K);
    if(ans==INF)return -1;
    return ans+center_w*llabs(sub[x]-K);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T;cin>>T;
    while(T--) cout<<solve()<<'\n';
}