#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
const int INF=0x7fffffff;
int n, m, s, t, ans;
struct Dinic{
    int cnt=1;
    int head[N], from[N<<1], to[N<<1], nxt[N<<1], edge[N<<1];
    int dis[N], now[N];
    void Add(int u, int v, int w){
        from[++cnt]=u;
        to[cnt]=v;
        edge[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Insert(int u, int v){
        Add(u, v, 1);
        Add(v, u, 0);
    }
    bool Bfs(){
        memset(dis, -1, sizeof(dis));
        memcpy(now, head, sizeof(now));
        queue<int> q;
        q.push(s);
        dis[s]=0;
        while (!q.empty()){
            int u=q.front();
            q.pop();
            for (int i=head[u]; i; i=nxt[i]){
                int v=to[i], w=edge[i];
                if (dis[v]==-1&&w>0){
                    q.push(v);
                    dis[v]=dis[u]+1;
                }
            }
        }
        if (dis[t]==-1){
            return 0;
        }
        return 1;
    }
    int Dfs(int u, int sum){
        if (u==t){
            return sum;
        }
        int val, res=0;
        for (int i=now[u]; i&&sum; i=nxt[i]){
            int v=to[i], w=edge[i];
            now[u]=i;
            if (dis[v]!=dis[u]+1||w<=0){
                continue;
            }
            val=Dfs(v, min(sum, w));
            if (val>0){
                edge[i]-=val;
                edge[i^1]+=val;
                dis[v]=INF;
            }
            res+=val, sum-=val;
        }
        return res;
    }
    void Out(){
        printf("%d\n", ans);
        for (int i=1; i<=cnt; i++){
            int u=from[i], v=to[i], w=edge[i];
            if (1<=u&&u<=n){
                if (n+1<=v&&v<=m){
                    if (w==0){
                        printf("%d %d\n", from[i], to[i]);
                    }
                }
            }
        }
    }
    void Init(){
        s=0, t=m+1;
        for (int i=1; i<=n; i++){
            Insert(s, i);
        }
        for (int i=n+1; i<=m; i++){
            Insert(i, t);
        }
    }
}graph;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    while (1){
        int u, v;
        cin >> u >> v;
        if (u==-1&&v==-1){
            break;
        }
        graph.Insert(u, v);
    }
    graph.Init();
    while (graph.Bfs()){
        ans+=graph.Dfs(s, INF);
    }
    graph.Out();

    return 0;
}