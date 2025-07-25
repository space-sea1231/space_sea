#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
const int M=2e5+10;
int n, m;
int ans, sum;
struct Prim{
    int cnt;
    int head[N], dist[N];
    int to[M<<1], nxt[M<<1], val[M<<1];
    bool vis[N];
    struct Queue{
        int u, dis;
        bool operator<(const Queue &a)const{
            return dis>a.dis;
        }
    };
    void Add(int u, int v, int w){
        to[++cnt]=v;
        val[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Insert(int u, int v, int w){
        Add(u, v, w);
        Add(v, u, w);
    }
    void prim(int s){
        memset(dist, 0x3f, sizeof(dist));
        priority_queue<Queue> q;
        q.push({s, 0});
        dist[s]=0;
        while (!q.empty()){
            int u=q.top().u, dis=q.top().dis;
            q.pop();
            if (vis[u]){
                continue;
            }
            vis[u]=1;
            sum++;
            ans+=dis;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=val[i];
                if (dist[v]>w){
                    dist[v]=w;
                    q.push({v, dist[v]});
                }  
            }
        }
    }
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph.Insert(u, v, w);
    }
    graph.prim(1);
    if (sum==n){
        printf("%d\n", ans);
    }else{
        printf("orz\n");
    }

    return 0;
}