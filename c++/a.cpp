#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n;
int cnt;
int dis[N];
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
vector<int> q;
void Add(int u, int v, int w=1){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}

namespace Pseudotree{
    int num;
    int dfn[N], father[N];
    bool vis[N];
    void Dfs1(int u, int fa){
        dfn[u]=++num;
        father[u]=fa;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v!=fa) continue;
            if (dfn[v]){
                if (dfn[v]>dfn[u]){
                    while (v!=u){
                        q.push(v);
                        vis[v]=1;
                        v=father[v];
                    }
                    q.push(v);
                    vis[v]=1;
                }
            }else{
                Dfs1(v, u);
            }
        }
    }
}using namespace Pseudotree;

int Dfs2(int u, int fa){
    int maxn=0;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa) continue;
        maxn=max(maxn, Dfs(v, u)+w);
    }
    return maxn;
}
void Dfs4(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){

    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        int u=i, v, w;
        cin >> v >> w;
        Add(u, v, w);
        Add(v, u, w);
    }
    for (int i=1; i<=n; i++){
        if (!dfn[i]){
            q.clear();
            Dfs1(i, 0);
            for (auto u:q){
                for (int i=head[u]; i; i=nxt[i]){
                    int v=to[i];
                    if (vis[v]) continue;
                    dis[u]=Dfs2(v, u);
                }
            }
            Dfs4(i, 0);
        }
    }
    return 0;
}