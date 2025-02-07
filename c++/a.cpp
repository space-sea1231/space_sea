#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
const int M=2e5+10;
int head[N], cnt, sum, n, m;//基础系列
int dis[N];//长度数组
bool vis[N];//标记数组
struct node{
    int to, next, w;
}e[M*2];
struct node_1{
    int now, dis;
};
bool operator<(const node_1 &a, const node_1 &b){
return a.dis>b.dis;
}
void add(int u, int v, int w){//链式前向星
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
priority_queue<node_1> q;
void prim(){
    cnt=0;
    dis[1]=0;
    int u, v, w;
    while (!q.empty()){
    u=q.top().now, w=q.top().dis;
        q.pop();
        if (vis[u]){
            continue;
        }
        vis[u]=1;
        cnt++;
        sum+=w;
        for (int i=head[u]; i; i=e[i].next){
            v=e[i].to, w=e[i].w;
            if (dis[v]>w){
                dis[v]=w;
                q.push({v, dis[v]});
            }
        }
    }
}
int main(){
    memset(dis, 0x3f, sizeof(dis));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v, w;
    for (int i=1; i<=m; i++){
        cin >> u >> v >> w;
        add(u, v, w);//建双向边
        add(v, u, w);
    }
    q.push({1, 0});
    prim();//最小生成树-prim
    if (cnt==n){
        printf("%d", sum);
    }else{
        printf("orz");
    }

    return 0;
}