#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
const int M=3e4+10;
const int INF=0x7fffffff;
int n, m, s, t;
int ans, sum;
struct Dinic{
    int cnt=1;
    int head[N], to[M<<1], nxt[M<<1], flow[M<<1];
    int dis[N], now[N];
    void Add(int u, int v, int w){
        to[++cnt]=v;
        flow[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Insert(int u, int v, int w){
        Add(u, v, w);
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
                int v=to[i], w=flow[i];
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
            int v=to[i], w=flow[i];
            now[u]=i;
            if (dis[v]==dis[u]+1&&w>0){
                val=Dfs(v, min(sum, w));
                if (val==0){
                    dis[v]=-1;
                }
                flow[i]-=val;
                flow[i^1]+=val;
                res+=val, sum-=val;
            }
        }
        return res;
    }
    void Out(){
        if (ans==sum){
            for (int u=1; u<=n; u++){
                printf("%d: ", u);
                for (int j=head[u]; j; j=nxt[j]){
                    int v=to[j], f=flow[j];
                    if (!f&&v!=s){
                        printf("%d ", v-n);
                    }
                }
                printf("\n");
            }
        }else{
            printf("No Solution!\n");
        }
    }
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    s=0, t=n+m+1;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        graph.Insert(s, i, x);
        sum+=x;
    }
    for (int i=1; i<=m; i++){
        int x;
        cin >> x;
        for (int j=1; j<=x; j++){
            int y;
            cin >> y;
            graph.Insert(y, i+n, 1);
        }
        graph.Insert(i+n, t, 1);
    }
    while (graph.Bfs()){
        ans+=graph.Dfs(s, INF);
    }
    graph.Out();

    return 0;
}