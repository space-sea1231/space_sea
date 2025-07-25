#include <bits/stdc++.h>
using namespace std;
const int N=3e3+10;
const int INF=0x3f3f3f3f;
int n;
int cnt, ans;
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
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
    void Dfs(int u, int fa){
        dfn[u]=++num;
        father[u]=fa;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa){
                continue;
            }
            if (dfn[v]){
                if (dfn[v]>dfn[u]){
                    while (v!=u){
                        vis[v]=1;
                        v=father[v];
                    }
                    vis[v]=1;
                }
            }else{
                Dfs(v, u);
            }
        }
    }
}
using namespace Pseudotree;

void Dfs1(int u, int fa, int dep){
    if (dep>=ans){
        return ;
    }
    if (vis[u]){
        ans=min(ans, dep);
        return ;
    }
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa){
            continue;
        }
        Dfs1(v, u, dep+1);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Dfs(1, 0);
    for (int i=1; i<=n; i++){
        ans=INF;
        Dfs1(i, 0, 0);
        printf("%d ", ans);
    }

    return 0;
}