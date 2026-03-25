#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e4+10;
const int M=4e5+10;
const int INF=4557430888798830399;
int n, s, t;
int nw, fd, fm, sd, sm;
int ans;
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
            flow[last^1LL]+=ans[t];
            x=to[last^1LL];
        }
        return dist[t]*ans[t];
    }
}Graph;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    s=0, t=(n<<1)+1;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        Graph.Insert(s, i, x, 0);
        Graph.Insert(i+n, t, x, 0);
    }
    cin >> nw >> fd >> fm >> sd >> sm;
    for (int i=1; i<=n; i++){
        Graph.Insert(s, i+n, INF, nw);
        if (i+1<=n){
            Graph.Insert(i, i+1, INF, 0);
        }
        if (i+fd<=n){
            Graph.Insert(i, i+fd+n, INF, fm);
        }
        if (i+sd<=n){
            Graph.Insert(i, i+sd+n, INF, sm);
        }
    }
    while (Graph.SPFA()){
        ans+=Graph.Update();
    }
    printf("%lld\n", ans);

    return 0;
}