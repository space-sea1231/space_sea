#include <bits/stdc++.h>
using namespace std;
const int N=2e2+10;
const int M=4e4+10;
const int K=1e4+10;
const int INF=0x7fffffff;
int n, m, s, t;
int sum, ans;
char c[K];
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
        for (int i=1; i<=n; i++){
            if (dis[i]!=-1){
                printf("%d ", i);
            }
        }
        printf("\n");
        for (int i=n+1; i<=n+m; i++){
            if (dis[i]!=-1){
                printf("%d ", i-n);
            }
        }
        printf("\n");
        printf("%d\n", sum-ans);
    }
}Graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    s=0, t=n+m+1;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        sum+=x;
        Graph.Insert(s, i, x);
        memset(c, 0, sizeof(c));
        cin.getline(c, K-1);
        int len=0, num;
        while (sscanf(c+len, "%d", &num)==1){
            Graph.Insert(i, num+n, INF);
            if (num==0){
                len++;
            }else{
                while (num){
                    num/=10;
                    len++;
                }
            }
            len++;
        }
    }
    for (int i=1; i<=m; i++){
        int x;
        cin >> x;
        Graph.Insert(i+n, t, x);
    }
    while (Graph.Bfs()){
        ans+=Graph.Dfs(s, INF);
    }
    Graph.Out();

    return 0;
}