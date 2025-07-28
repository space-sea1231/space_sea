#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e4+10;
const int M=6e4+10;
const int INF1=0x3f3f3f3f3f3f3f3f;
const int INF2=1e9;
int n, m;
struct Johnson{
    int cnt;
    int head[N], to[M], nxt[M], val[M];
    int dist[N], dis[N], tot[N];
    bool vis[N];
    struct Node{
        int u, dis;
        bool operator<(const Node &a)const{
            return dis>a.dis;
        }
    };
    void Add(int u, int v, int w){
        to[++cnt]=v;
        val[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    bool SPFA(int s){
        queue<int> q;
        memset(dist, 0x3f, sizeof(dist));
        q.push(s);
        dist[s]=0;
        while (!q.empty()){
            int u=q.front();
            q.pop(), vis[u]=0;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=val[i];
                if (dist[v]>dist[u]+w){
                    dist[v]=dist[u]+w;
                    if (!vis[v]){
                        vis[v]=1;
                        q.push(v);
                        if (++tot[v]>n){
                            return 0;
                        }
                    }
                }
            }
        }
        return 1;
    }
    void Dijkstra(int s){
        priority_queue<Node> q;
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        q.push({s, 0});
        dis[s]=0;
        while (!q.empty()){
            int u=q.top().u;
            q.pop();
            if (vis[u]){
                continue;
            }
            vis[u]=1;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=val[i];
                if (dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    q.push({v, dis[v]});
                }
            }
        }
    }
    void Init(){
        for (int u=1; u<=n; u++){
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i];
                val[i]+=dist[u]-dist[v];
            }
        }
    }
    void Out(){
        for (int u=1; u<=n; u++){
            int ans=0;
            Dijkstra(u);
            for (int v=1; v<=n; v++){
                if (dis[v]==INF1){
                    ans+=v*INF2;
                }else{
                    ans+=v*(dis[v]+dist[v]-dist[u]);
                }
            }
            printf("%lld\n", ans);
        }
    }
}Graph;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Graph.Add(u, v, w); 
    }
    for (int i=1; i<=n; i++){
        Graph.Add(0, i, 0);
    }
    if (!Graph.SPFA(0)){
        printf("-1\n");
        return 0;
    }
    Graph.Init();
    Graph.Out();

    return 0;
}