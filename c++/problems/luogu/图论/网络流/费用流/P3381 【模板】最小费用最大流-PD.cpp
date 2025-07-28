#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
const int M=6e4+10;
const int INF=0x3f3f3f3f;
int n, m, s, t;
int ans1, ans2;
struct Primal_Dual{
    int cnt=1;
    int head[N], dis[N], dist[N], pre[N];
    int to[M<<1], nxt[M<<1], flow[M<<1], cost[M<<1];
    bool vis[N];
    struct Node{
        int u, dis;
        bool operator<(const Node &a)const{
            return dis>a.dis;
        }
    };
    void Add(int u, int v, int f, int c){
        to[++cnt]=v;
        flow[cnt]=f;
        cost[cnt]=c;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Insert(int u, int v, int f, int c){
        Add(u, v, f, c);
        Add(v, u, 0, -c);
    }
    void SPFA(){
        queue<int> q;
        memset(dist, 0x3f, sizeof(dist));
        q.push(s);
        dist[s]=0;
        while (!q.empty()){
            int u=q.front();
            q.pop(), vis[u]=0;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], f=flow[i], c=cost[i];
                if (f&&dist[v]>dist[u]+c){
                    dist[v]=dist[u]+c;
                    if (!vis[v]){
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
    }
    bool Dijkstra(){
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
                int v=to[i], f=flow[i], c=cost[i]+dist[u]-dist[v];
                if (f&&dis[v]>dis[u]+c){
                    dis[v]=dis[u]+c;
                    pre[v]=i;
                    if (!vis[v]){
                        q.push({v, dis[v]});
                    }
                }
            }
        }
        if (dis[t]==INF){
            return 0;
        }
        return 1;
    }
    void Update(){
        for (int i=1; i<=n; i++){
            dist[i]+=dis[i];
        }
        int x=t, minn=INF;
        while (x!=s){
            int last=pre[x];
            minn=min(minn, flow[last]);
            x=to[last^1];
        }
        x=t;
        while (x!=s){
            int last=pre[x];
            flow[last]-=minn;
            flow[last^1]+=minn;
            x=to[last^1];
        }
        ans1+=minn;
        ans2+=minn*dist[t];
    }
}Graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> s >> t;
    for (int i=1; i<=m; i++){
        int u, v, f, c;
        cin >> u >> v >> f >> c;
        Graph.Insert(u, v, f, c);
    }
    Graph.SPFA();
    while (Graph.Dijkstra()){
        Graph.Update();
    }
    printf("%d %d\n", ans1, ans2);

    return 0;
}