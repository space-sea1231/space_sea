#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int M=4e6+10;
const int INF=1061109567;
int n, m, s;
struct SPFA{
    int cnt;
    int dis[M];
    bool vis[M];
    struct Node{
        int w;
        int b1, b2, f1, f2;
    }e[N<<1];
    void Add(int t, string b, string f){
        e[++cnt].w=t;
        for (int i=0; i<n; i++){
            if (b[i]=='+'){
                e[cnt ].b1|=(1<<(i+1));
            }else if (b[i]=='-'){
                e[cnt].b2|=(1<<(i+1));
            }
            if (f[i]=='+'){
                e[cnt].f2|=(1<<(i+1));
            }else if (f[i]=='-'){
                e[cnt].f1|=(1<<(i+1));
            }
        }
    }
    bool Spfa(){
        priority_queue<pair<int, int> > q;
        memset(dis, 0x3f, sizeof(dis));
        q.push(make_pair(0, s));
        dis[s]=0;
        while (!q.empty()){
            int u=q.top().second;
            q.pop();
            if (vis[u]){
                continue;
            }
            vis[u]=1;
            for (int i=1; i<=m; i++){
                if ((e[i].b1&u)==e[i].b1&&!(e[i].b2&u)){
                    int v=((e[i].f1|u)^e[i].f1)|e[i].f2, w=e[i].w;
                    if (dis[v]>dis[u]+w){
                        dis[v]=dis[u]+w;
                        q.push(make_pair(-dis[v], v));
                    }
                }
            }
        }
        if (dis[0]==INF){
            return 0;
        }
        return 1;
    }
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    s=(1<<(n+1))-2;
    string b, f;
    for (int i=1; i<=m; i++){
        int t;
        cin >> t >> b >> f;
        graph.Add(t, b, f);
    }
    if (graph.Spfa()){
        printf("%d\n", graph.dis[0]);
    }else{
        printf("0\n");
    }

    return 0;
}