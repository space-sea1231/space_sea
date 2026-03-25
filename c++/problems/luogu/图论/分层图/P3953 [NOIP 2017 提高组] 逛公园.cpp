#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=4e5+10;
const int K=1e2;
int T, n, m, k, p, s, t;
int cnt, ans;
int head[N], to[M<<1], val[M<<1], nxt[M<<1];
int dis[N], dp[N][K];
bool flag;
bool vis1[N], vis2[N][K];
void Add(int u, int v, int w){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
struct Node{
    int u, w;
    bool operator<(const Node &a)const{
        return w>a.w;
    }
};
void Dijkstra(int s){
    priority_queue<Node> q;
    dis[s]=0, q.push({s, 0});
    while (!q.empty()){
        int u=q.top().u;
        q.pop();
        if (vis1[u]) continue;
        vis1[u]=1;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=val[i];
            if (dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push({v, dis[v]});
            }
        }
    }
}
int Dfs(int u, int x){
    if (vis2[u][x]){
        flag=1;
        return 0;
    }
    if (~dp[u][x]) return dp[u][x];
    vis2[u][x]=1, dp[u][x]=0;
    for (int i=head[u+n]; i; i=nxt[i]){
        int v=to[i]-n, w=val[i], y=dis[u]-dis[v]+x-w;
        if (y<0||y>k) continue;
        dp[u][x]=(dp[u][x]+Dfs(v, y))%p;
        if (flag){
            vis2[u][x]=0;
            return 0;
        }
    }
    if (u==1&&x==0) dp[u][x]=1;
    vis2[u][x]=0;
    return dp[u][x];
}
inline void Init(){
    flag=0, ans=0, cnt=0;
    memset(head, 0, sizeof(head));
    memset(dp, -1, sizeof(dp));
    memset(vis1, 0, sizeof(vis1));
    memset(dis, 0x3f, sizeof(dis));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> T;
    while (T--){
        Init();
        cin >> n >> m >> k >> p;
        s=1, t=n;
        for (int i=1; i<=m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            Add(u, v, w);
            Add(v+n, u+n, w);
        }
        Dijkstra(s);
        for (int i=0; i<=k; i++){
            ans=(ans+Dfs(t, i))%p;
            if (flag) break;
        }
        if (flag) printf("-1\n");
        else printf("%d\n", ans);
    }

    return 0;
}