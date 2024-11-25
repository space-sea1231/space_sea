#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int M=5e5+10;
const int K=30;
const int INF=1e9;
int n, m, k, cnt;
int head[N*K], dis[N*K];
struct node{
    int to, next, w;
}e[M*K*2];
void add(int u, int v, int w){
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void init(){
    for (int i=1; i<=n*(k+1); i++){
        dis[i]=INF;
    }
    dis[1]=0;
}
void dijkstra(){
    init();
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, 1));
    int u, v, w;
    while(!q.empty()){
        u=q.top().second;
        q.pop();
        for (int i=head[u]; i; i=e[i].next){
            v=e[i].to, w=e[i].w;
            if (dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push(make_pair(-dis[v], v));
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
        add(v, u, w);
        for (int j=1; j<=k; j++){
            add(n*j+u, n*j+v, w);
            add(n*j+v, n*j+u, w);
			add(n*(j-1)+u, n*j+v, 0);
            add(n*(j-1)+v, n*j+u, 0);
        }
    }
    dijkstra();
    int ans=INF;
    for (int i=1; i<=k+1; i++){
        ans=min(ans, dis[i*n]);
    }
    printf("%d", ans);

    return 0;
}