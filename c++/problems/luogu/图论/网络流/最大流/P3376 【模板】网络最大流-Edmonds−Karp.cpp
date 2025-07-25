#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
const int M=5e4+10;
const int INF=0x7fffffff;
int n, m, s, t, ans;
struct Edmonds_Karp{
    int head[N], to[M], nxt[M], edge[M];
    int idx[N][N], pre[N], dis[N], cnt=1;
    bool vis[N];
    void Add(int u, int v, int w){
        to[++cnt]=v;
        edge[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
        idx[u][v]=cnt;
    }
    void Insert(int u, int v, int w){
        if (!idx[u][v]){
            Add(u, v, w);
            Add(v, u, w);
            edge[idx[v][u]]=0;
        }else{
            edge[idx[u][v]]+=w;
        }
    }
    bool Bfs(){
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);
        vis[s]=1, dis[s]=INF;
        while (!q.empty()){
            int u=q.front();
            q.pop();
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=edge[i];
                if (vis[v]||w<=0){
                    continue;
                }
                vis[v]=1, pre[v]=i;
                dis[v]=min(dis[u], w);
                q.push(v);
                if (v==t){
                    return 1;
                }
            }
        }
        return 0;
    }
    void Update(){
        int x=t;
        while (x!=s){
            int last=pre[x];
            edge[last]-=dis[t];
            edge[last^1]+=dis[t];
            x=to[last^1];
        }
        ans+=dis[t];
    }
}graph;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> s >> t;
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph.Insert(u, v, w);
    }
    while (graph.Bfs()){
        graph.Update();
    }
    printf("%lld\n", ans);

    return 0;
}