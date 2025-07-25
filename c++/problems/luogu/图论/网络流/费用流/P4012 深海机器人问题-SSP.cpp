#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=1e5+10;
const int INF=1044266559;
int S, T;
int n, m, s, t;
int ans;
int Change(int x, int y){
    return (x-1)*m+y;
}
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
        memset(dist, -0x3f, sizeof(dist));
        queue<int> q;
        q.push(s);
        dist[s]=0, ans[s]=INF;
        while (!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=dis[i], f=flow[i];
                if (f>0&&dist[v]<dist[u]+w){
                    dist[v]=dist[u]+w;
                    ans[v]=min(ans[u], f);
                    pre[v]=i;
                    if (!vis[v]){
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
        if (dist[t]==-INF){
            return 0;
        }
        return 1;
    }
    int Update(){
        int x=t;
        while (x!=s){
            int last=pre[x];
            flow[last]-=ans[t];
            flow[last^1]+=ans[t];
            x=to[last^1];
        }
        return dist[t]*ans[t];
    }
}Graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> S >> T >> n >> m;
    n++, m++;
    s=0, t=((n*m)<<2)+2;
    for (int i=1; i<=n; i++){
        for (int j=1; j<m; j++){
            int x;
            cin >> x;
            Graph.Insert(Change(i, j), Change(i, j+1), 1, x);
            Graph.Insert(Change(i, j), Change(i, j+1), INF, 0);
        }
    }
    for (int j=1; j<=m; j++){
        for (int i=1; i<n; i++){
            int x;
            cin >> x;
            Graph.Insert(Change(i, j), Change(i+1, j), 1, x);
            Graph.Insert(Change(i, j), Change(i+1, j), INF, 0);
        }
    }
    for (int i=1; i<=S; i++){
        int z, x, y;
        cin >> z >> x >> y;
        x++, y++;
        Graph.Insert(s, Change(x, y), z, 0);
    }
    for (int i=1; i<=T; i++){
        int z, x, y;
        cin >> z >> x >> y;
        x++, y++;
        Graph.Insert(Change(x, y), t, z, 0);
    }
    while (Graph.SPFA()){
        ans+=Graph.Update();
    }
    printf("%d\n", ans);

    return 0;
}