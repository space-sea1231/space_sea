#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int INF=1e9;
int n, m, dis[N*3];
bool vis[N*3];
vector<pair<int, int> > q[N*3];
void add(int u, int v){
    q[u].push_back(make_pair(v, 0));
    q[u+n].push_back(make_pair(v+n,0));
    q[u+n*2].push_back(make_pair(v+n*2, 0));
    return ;
}
void SPFA(){
    for (int i=1; i<=n*3; i++){
        dis[i]=-INF;
    }
    dis[1]=0;
    queue<int> p;
    p.push(1);
    vis[1]=1;
    int u, v, w;
    while(!p.empty()){
        u=p.front();
        p.pop();
        vis[u]=0;
        for (auto x:q[u]){
            v=x.first, w=x.second;
            if (dis[v]<dis[u]+w){
                dis[v]=dis[u]+w;
                if (!vis[v]){
                    p.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v, w;
    for (int i=1; i<=n; i++){
        cin >> w;
        q[i].push_back(make_pair(i+n, -w));
        q[i+n].push_back(make_pair(i+n*2, w));
    }
    for (int i=1; i<=m; i++){
        cin >> u >> v >> w;
        add(u, v);
        if (w==2){
            add(v, u);
        }
    }
    SPFA();
    printf("%d", dis[n*3]);

    return 0;
}