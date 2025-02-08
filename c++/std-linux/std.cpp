#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=1e5+10;
const int INF=1061109567;
int n, m, l, s, t, d;
bool vis[N];
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
        memset(dist, 0x3f, sizeof(dist));
        queue<int> q;
        q.push(s);
        dist[s]=0, ans[s]=INF;
        while (!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=dis[i], f=flow[i];
                if (f>0&&dist[v]>dist[u]+w){
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
        if (dist[t]==INF){
            return 0;
        }
        return 1;
    }
    void Update(){
        int x=t;
        while (x!=s){
            int last=pre[x];
            flow[last]-=ans[t];
            flow[last^1]+=ans[t];
            x=to[last^1];
        }
    }
    void New(){
        for (int u=d+1; u<=(d<<1); u++){
            if (vis[u]){
                continue;
            }
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=flow[i];
                if (v+d!=u&&w!=INF&&v!=t){
                    Insert(u+d, v+(d<<1), INF-w, 0);
                }
            }
        }
    }
    void Out(int u, int id){
        int realu=u-(d<<1);
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=flow[i];
            int realv=v-(d<<1);
            if (!w){
                continue;
            }
            if (realu+1==realv){
                printf("%d 1\n", id);
            }else{
                printf("%d 0\n", id);
            }
            flow[i]--;
            Out(v, id);
            return ;
        }
    }
}Graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> l >> n >> m;
    d=n*m, s=0, t=d*3+1;
    Graph.Insert(s, Change(1, 1), l, 0);
    Graph.Insert(Change(n, m)<<1, t, l, 0);
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            int opt;
            cin >> opt;
            if (i==opt){
                Graph.Insert(Change(i, j), Change(i, j)+d, 1, -1);
            }
            if (i!=1){
                Graph.Insert(Change(i, j), Change(i, j)+d, INF, 0);
            }else{
                vis[Change(i, j)]=1;
            }
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<m; j++){
            if (i+1<=n){
                Graph.Insert(Change(i, j)+d, Change(i+1, j), INF, 0);
            }
            if (j+1<=m){
                Graph.Insert(Change(i, j)+d, Change(i, j+1), INF, 0);
            }
        }
    }
    while (Graph.SPFA()){
        Graph.Update();
    }
    Graph.New();
    for (int i=1; i<=l; i++){
        Graph.Out(1+(d<<1), 1);
    }
    return 0;
}