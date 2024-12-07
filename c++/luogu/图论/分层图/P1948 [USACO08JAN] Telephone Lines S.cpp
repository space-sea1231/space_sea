#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
const int M=1e4+10;
const int INF=2e9;
int n,m,k,w,cnt,head[N];//建边系列
int dis[N][N];
bool vis[N][N];
struct node{
    int to,next,w;
}e[M*2];
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
struct node_1{
    int x,dis,k;
};
bool operator<(const node_1 a,const node_1 b){
    return a.dis>b.dis;
}
void dijkstra(){
    priority_queue<node_1>q;
    q.push({1,0,0});
    dis[1][0]=0;
    int u,v,now;
    while(!q.empty()){
        u=q.top().x,now=q.top().k;
        q.pop();
        if (vis[u][now]){
            continue;
        }
        vis[u][now]=1;
        for (int i=head[u]; i; i=e[i].next){
            v=e[i].to,w=e[i].w;
            if (!vis[v][now]&&dis[v][now]>max(dis[u][now],w)){
                dis[v][now]=max(dis[u][now],w);
                q.push({v,dis[v][now],now});
            }
            if (!vis[v][now+1]&&now+1<=k&&dis[v][now+1]>dis[u][now]){
                dis[v][now+1]=dis[u][now];
                q.push({v,dis[v][now+1],now+1});
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i=1; i<=n; i++){
        for (int j=0; j<=k; j++){
            dis[i][j]=INF;
        }
    }
    int u,v,w;
    for (int i=1; i<=m; i++){
        cin >> u >> v >> w;
        add(u,v,w);
        add(v,u,w);
    }
    dijkstra();
    int minn=INF;
    for (int i=0; i<=k; i++){
        minn=min(minn, dis[n][i]);
    }
    if (minn==INF){
        printf("-1");
        return 0;
    }
    printf("%d", minn);

    return 0;
}