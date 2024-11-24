#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=2e4+10;
const int K=1e3+10;
const int INF=1e9;
int n, m, k, cnt;
int head[N], dis[N][K];
bool vis[N][K];
struct node{
    int to, next, w;
}e[M];
void add(int u, int v, int w){
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void init(){
    for (int i=1; i<=n; i++){
        for (int j=0; j<k; j++){
            dis[i][j]=INF;
        }
    }
    dis[1][0]=0;
}
void dijkstra(){
    init();
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, 1));
    int u, v, w, now, tim;
    while(!q.empty()){
        now=-q.top().first, u=q.top().second;
        q.pop();
        if (vis[u][now%k]){
            continue;
        }
        vis[u][now%k]=1;
        for (int i=head[u]; i; i=e[i].next){
            v=e[i].to, w=e[i].w;
            if (now<w){
                tim=((w-now+k-1)/k)*k+now;
            }else{
                tim=now;
            }
            if (dis[v][(tim+1)%k]>tim+1){
                dis[v][(tim+1)%k]=tim+1;
                q.push(make_pair(-dis[v][(tim+1)%k], v));//1 3  2 5
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    int u, v, w;
    for (int i=1; i<=m; i++){
        cin >> u >> v >> w;
        add(u, v, w);
    }
    dijkstra();
    if (dis[n][0]==INF){
        printf("-1");
    }else{
        printf("%d", dis[n][0]);
    }

    return 0;
}