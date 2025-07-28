#include <bits/stdc++.h>
using namespace std;
const int N=6e3+10;
const int INF_MAX=1061109567;
const int INF_MIN=-1044266559;
int n, m, s, t, tot;
struct Successive_Shortest_Path{
    int cnt=1;
    int head[N], dist[N], ans[N], pre[N];
    int to[N<<1], nxt[N<<1], flow[N<<1], dis[N<<1];
    bool vis[N];
    void Add(int u, int v, int f, int d){
        to[++cnt]=v;
        flow[cnt]=f;
        dis[cnt]=d;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Insert(int u, int v, int d){
        Add(u, v, 1, d);
        Add(v, u, 0, -d);
    }
    bool SPFA_Max(){
        queue<int> q;
        memset(dist, -0x3f, sizeof(dist));
        q.push(s);
        dist[s]=0, ans[s]=INF_MAX;
        while (!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], d=dis[i], f=flow[i];
                if (f>0&&dist[v]<dist[u]+d){
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
        if (dist[t]==INF_MIN){
            return 0;
        }
        return 1;
    }
    bool SPFA_Min(){
        queue<int> q;
        memset(dist, 0x3f, sizeof(dist));
        q.push(s);
        dist[s]=0, ans[s]=INF_MAX;
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
        if (dist[t]==INF_MAX){
            return 0;
        }
        return 1;
    }
    void Update(){
        tot+=dist[t]*ans[t];
        int x=t;
        while (x!=s){
            int last=pre[x];
            flow[last]-=ans[t];
            flow[last^1]+=ans[t];
            x=to[last^1];
        }
    }
    void Init(){
        tot=0;
        for (int i=2; i<=cnt; i+=2){
            flow[i]+=flow[i^1];
            flow[i^1]=0;
        }
    }
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    s=0, t=(n<<1)+1;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            int x;
            cin >> x;
            graph.Insert(i, j+n, x);
        }
        graph.Insert(s, i, 0);
        graph.Insert(i+n, t, 0);
    }
    while (graph.SPFA_Min()){
        graph.Update();
    }
    printf("%d\n", tot);
    graph.Init();
    while (graph.SPFA_Max()){
        graph.Update();
    }
    printf("%d\n", tot);

    return 0;
}