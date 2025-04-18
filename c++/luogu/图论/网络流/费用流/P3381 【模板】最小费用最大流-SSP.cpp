#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
const int M=5e4+10;
const int INF=1061109567;
int n, m, s, t, maxn, minn;
struct Successive_Shortest_Path{
    int cnt=1;
    int head[N], dist[N], ans[N], pre[N];
    int to[M<<1], nxt[M<<1], flow[M<<1], dis[M<<1];
    bool vis[N];
    void Add(int u, int v, int f, int d){
        to[++cnt]=v;
        flow[cnt]=f;
        dis[cnt]=d;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Insert(int u, int v, int f, int d){
        Add(u, v, f, d);
        Add(v, u, 0, -d);
    }
    bool SPFA(){
        queue<int> q;
        memset(dist, 0x3f, sizeof(dist));
        q.push(s);
        dist[s]=0, ans[s]=INF;
        while (!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], d=dis[i], f=flow[i];
                if (f>0&&dist[v]>dist[u]+d){
                    dist[v]=dist[u]+d;
                    ans[v]=min(ans[u], f);
                    pre[v]=i;
                    if (!vis[v]){
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
        if (dist[t]==INF){
            return 0;
        }
        return 1;
    }
    void Update(){
        maxn+=ans[t];
        minn+=dist[t]*ans[t];
        int x=t;
        while (x!=s){
            int last=pre[x];
            flow[last]-=ans[t];
            flow[last^1]+=ans[t];
            x=to[last^1];
        }
    }
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> s >> t;
    for (int i=1; i<=m; i++){
        int u, v, f, d;
        cin >> u >> v >> f >> d;
        graph.Insert(u, v, f, d);
    }
    while (graph.SPFA()){
        graph.Update();
    }
    printf("%d %d\n", maxn, minn);

    return 0;
}