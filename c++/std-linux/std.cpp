#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=8e6+10;
const int INF=1061109567;
int n, k, a, b, c, d, s, t;
int sum;
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
int Change(int x, int y){
    return (x-1)*n+y;
}
bool Check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=n;
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
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> k >> a >> b >> c;
    d=n*n, s=0, t=d*(k+1)+1;
    graph.Insert(s, Change(1, 1), 1, 0);
    for (int i=0; i<=k; i++){
        graph.Insert(Change(n, n)+i*d, t, 1, 0);
    }
    for (int x=1; x<=n; x++){
        for (int y=1; y<=n; y++){
            bool opt;
            cin >> opt;
            if (opt){
                for (int i=1; i<=k; i++){
                    graph.Insert(Change(x, y)+i*d, Change(x, y), INF, a);
                }
            }
            for (int i=0; i<k; i++){
                if (opt&&i){
                    break;
                }
                for (int j=0; j<4; j++){
                    int vx=x+dx[i];
                    int vy=y+dy[i];
                    if (Check(vx, vy)){
                        if (j<2){
                            graph.Insert(Change(x, y)+i*d, Change(vx, vy)+(i+1)*d, INF, b);
                        }else{
                            graph.Insert(Change(x, y)+i*d, Change(vx, vy)+(i+1)*d, INF, 0);
                        }
                    }
                }
            }
            graph.Insert(Change(x, y)+k*d, Change(x, y), INF, a+c);
        }
    }
    while (graph.SPFA()){
        sum+=graph.Update();
    }
    printf("%d\n", sum);

    return 0;
}