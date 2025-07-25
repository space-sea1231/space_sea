#include <bits/stdc++.h>
using namespace std;
const int N=5e4+10;
const int INF=1061109567;
int n, s, t=N-10;
int sum, tot;
int a[N];
struct Primal_Dual{
    int cnt=1;
    int head[N], to[N], nxt[N], flow[N], dis[N];
    int dist[N], ans[N], pre[N];
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
        memset(vis, 0, sizeof(vis));
        q.push(s);
        dist[s]=0, vis[s]=1, ans[s]=INF;
        while (!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], f=flow[i], d=dis[i];
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
        tot+=dist[t]*ans[t];
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
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        sum+=a[i];
    }
    sum/=n;
    for (int i=1; i<=n; i++){
        a[i]-=sum;
        if (a[i]>0){
            graph.Insert(s, i, a[i], 0);
        }
        if (a[i]<0){
            graph.Insert(i, t, -a[i], 0);
        }
    }
    for (int i=1; i<=n; i++){
        if (i!=1){
            graph.Insert(i, i-1, INF, 1);
        }
        if (i!=n){
            graph.Insert(i, i+1, INF, 1);
        }
    }
    graph.Insert(1, n, INF, 1);
    graph.Insert(n, 1, INF, 1);
    while (graph.SPFA()){
        graph.Update();
    }
    printf("%d\n", tot);

    return 0;
}