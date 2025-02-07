#include <bits/stdc++.h>
using namespace std;
const int NN=1e3+10;
const int N=1e5+10;
const int M=4e6+10;
const int INF=0x7fffffff;
int n, m, s, t;
int ans;
int dx[8]={-1, -2, 2, 1, -1, -2, 2, 1};
int dy[8]={-2, -1, -1, -2, 2, 1, 1, 2};
bool vis[NN][NN];
int Change(int x, int y){
    return (x-1)*n+y;
}
bool Check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=n&&!vis[x][y];
}
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
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    s=0, t=n*n+1;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            char c;
            cin >> c;
            vis[i][j]=c-'0';
            m+=c-'0';
        }
    }
    for (int x=1; x<=n; x++){
        for (int y=1; y<=n; y++){
            if ((x+y)&1){
                for (int i=0; i<8; i++){
                    int vx=x+dx[i];
                    int vy=y+dy[i];
                    if (Check(vx, vy)){
                        graph.Insert(Change(x, y), Change(vx, vy), INF);
                    }
                }
            }
            if (!vis[x][y]){
                if ((x+y)&1){
                    graph.Insert(s, Change(x, y), 1);
                }else{
                    graph.Insert(Change(x, y), t, 1); 
                }
            }
        }
    }
    while (graph.Bfs()){
        ans+=graph.Dfs(s, INF);
    }
    printf("%d\n", n*n-m-ans);
    
    return 0;
}