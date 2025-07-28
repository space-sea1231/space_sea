#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=1e5+10;
const int K=50;
const int INF=1044266559;
int n, m, d;
int s1, s2, s3;
int t1, t2, t3;
int ans1, ans2, ans3;
int num;
int val[K][K], id[K][K];
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
    bool SPFA(int s, int t){
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
    int Update(int s, int t){
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
    cin >> m >> n;
    d=n*(n+m-1);
    s1=(d<<2)+1, s2=(d<<2)+2, s3=(d<<2)+3;
    t1=(d<<2)+4, t2=(d<<2)+5, t3=(d<<2)+6;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m+i-1; j++){
            cin >> val[i][j];
            id[i][j]=++num;
            // printf("%d %d %d %d\n", i, j, val[i][j], id[i][j]);
        }
    }
    for (int i=1; i<=m; i++){
        Graph.Insert(s1, id[1][i], 1, 0);
        Graph.Insert(s2, id[1][i]+(d<<1), 1, 0);
        Graph.Insert(s3, id[1][i]+d*3, 1, 0);
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m+i-1; j++){
            Graph.Insert(id[i][j], id[i][j]+d, 1, val[i][j]);
            if (i<n){
                Graph.Insert(id[i][j]+d, id[i+1][j], 1, 0);
                Graph.Insert(id[i][j]+d, id[i+1][j+1], 1, 0);

                Graph.Insert(id[i][j]+(d<<1), id[i+1][j]+(d<<1), 1, val[i][j]);
                Graph.Insert(id[i][j]+(d<<1), id[i+1][j+1]+(d<<1), 1, val[i][j]);

                Graph.Insert(id[i][j]+d*3, id[i+1][j]+d*3, INF, val[i][j]);
                Graph.Insert(id[i][j]+d*3, id[i+1][j+1]+d*3, INF, val[i][j]);
            }
        }
    }
    for (int i=1; i<=m+n-1; i++){
        Graph.Insert(id[n][i]+d, t1, 1, 0);
        Graph.Insert(id[n][i]+(d<<1), t2, INF, val[n][i]);
        Graph.Insert(id[n][i]+d*3, t3, INF, val[n][i]);
    }
    while (Graph.SPFA(s1, t1)){
        ans1+=Graph.Update(s1, t1);
    }
    while (Graph.SPFA(s2, t2)){
        ans2+=Graph.Update(s2, t2);
    }
    while (Graph.SPFA(s3, t3)){
        ans3+=Graph.Update(s3, t3);
    }
    printf("%d\n%d\n%d\n", ans1, ans2, ans3);

    return 0;
}