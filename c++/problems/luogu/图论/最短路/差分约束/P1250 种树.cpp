#include <bits/stdc++.h>
using namespace std;
const int N=3e4+10;
const int M=1e5+10;
const int INF=1e9;
int m, n, cnt, head[N], to[M], nxt[M], edge[M], dis[N];
bool vis[N];
void add(int u, int v, int w){
    to[++cnt]=v;
    edge[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void spfa(int s){
    queue<int> q;
    for (int i=1; i<=n; i++){
        dis[i]=INF;
    }
    vis[s]=1, dis[s]=0;
    q.push(s);
    while (!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=edge[i];
            if (dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if (!vis[v]){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int s=n+1;
    for (int i=0; i<=n; i++){
        add(s, i, 0);
    }
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        add(v, u-1, -w);
    }
    for (int i=1; i<=n; i++){
        add(i-1, i, 1);
        add(i, i-1, 0);
    }
    spfa(s);
    int minn=INF;
    for (int i=0; i<=n; i++){
        minn=min(minn, dis[i]);
    }
    printf("%d", dis[n]);

    return 0;
}