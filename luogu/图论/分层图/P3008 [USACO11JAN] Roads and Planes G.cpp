#include <bits/stdc++.h>
using namespace std;
const int N=25010;
const int M=6e5+10;
const int INF=1e9;
int n, m, k, s, cnt;
int head[N], dis[N];
bool vis[N];
struct node{
    int to, next, w;
}e[M*2];
void add(int u, int v, int w){
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void init(){
    for (int i=1; i<=n; i++){
        dis[i]=INF;
    }
    dis[s]=0;
    vis[s]=1;
}
void SPFA(){
    init();
    deque<int> q;
    q.push_front(s);
    int u, v, w;
    while(!q.empty()){
        u=q.front();
        q.pop_front();
        vis[u]=0;
        for (int i=head[u]; i; i=e[i].next){
            v=e[i].to, w=e[i].w;
            if (dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if (!vis[v]){
                    if (q.empty()||dis[v]>=dis[q.front()]){
                        q.push_back(v);
                    }else{
                        q.push_front(v);
                    }
                    vis[v]=1;
                }
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k >> s;
    int u, v, w;
    for (int i=1; i<=m; i++){
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    for (int i=1; i<=k; i++){
        cin >> u >> v >> w;
        add(u, v, w);
    }
    SPFA();
    for (int i=1; i<=n; i++){
        if (dis[i]==INF){
            printf("NO PATH\n");
        }else{
            printf("%d\n", dis[i]);
        }
    }

    return 0;
}