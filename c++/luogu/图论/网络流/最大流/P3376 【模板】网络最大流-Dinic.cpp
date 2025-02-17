#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e2+10;
const int M=5e4+10;
const int INF=0x7fffffff;
int n, m, s, t, ans;
struct Dinic{
    int cnt=1;
    int head[N], to[M], nxt[M], edge[M];
    int dis[N], now[N];
    void Add(int u, int v, int w){
        to[++cnt]=v;
        edge[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Insert(int u, int v, int w){
        Add(u, v, w);
        Add(v, u, 0);
    }
    bool Bfs(){
        queue<int> q;
        memset(dis, -1, sizeof(dis));
        memcpy(now, head, sizeof(now));
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
            if (dis[v]==dis[u]+1&&w>0){
                val=Dfs(v, min(sum, w));
                if (val==0){
                    dis[v]=-1;
                }
                edge[i]-=val;
                edge[i^1]+=val;
                res+=val, sum-=val;
            }
        }
        return res;
    }
}graph;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    s=0, t=(n<<1)+1;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            int x;
            cin >> x;
            graph.Insert(i, j+n, x);
        }
        graph.Insert(s, i, 0);
        graph.Insert(i+n, t, 0);
    }
    while (graph.Bfs()){
        ans+=graph.Dfs(s, INF);
    }
    printf("%lld", ans);

    return 0;
}