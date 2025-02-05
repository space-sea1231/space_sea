#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int INF=0x7fffffff;
int n, m, s, t=N-10;
int nxtt[N], flag[N];
bool vis[N];
struct Dinic{
    int cnt=1;
    int head[N], to[N<<1], nxt[N<<1], edge[N<<1];
    int dis[N], now[N];
    void Add(int u, int v, int w){
        to[++cnt]=v;
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
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=edge[i];
            now[u]=i;
            if (dis[v]==dis[u]+1&&w>0){
                int val=Dfs(v, min(sum, w));
                if (val==0){
                    dis[v]=-1;
                    continue;
                }
                edge[i]-=val;
                edge[i^1]+=val;
                if (v!=t){
                    nxtt[u>>1]=v>>1;
                }
                return val;
            }
        }
        return 0;
    }
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    int tot=0, num=0;
    while (tot<=n){
        num++;
        graph.Insert(s, num<<1);
        graph.Insert(num<<1|1, t);
        for (int i=sqrt(num)+1; i*i<(num<<1); i++){
            graph.Insert((i*i-num)<<1, num<<1|1);
        }
        int sum=0;
        while (graph.Bfs()){
            sum+=graph.Dfs(s, INF);
        }
        if (!sum){
            flag[++tot]=num;
        }
    }
    printf("%d\n", num-1);
    for (int i=1; i<=n; i++){
        int x=flag[i];
        if (!vis[x]){
            vis[x]=1;
            while (x){
                printf("%d ", x);
                x=nxtt[x];
                vis[x]=1;
            }
            printf("\n");
        }
    }
    return 0;
}