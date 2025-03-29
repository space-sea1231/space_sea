#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int M=2e6+10;
int n, m, head[N], cnt=1;//建边系列(边的编号从1开始，切记切记！！！)
int dfn[N], low[N], c[N], tot, num;//Tarjan系列
bool bridge[M*2];
/*
dfn[u] 节点u的时间戳（访问顺序）
low[u] 节点u的回溯值（最多通过一条非树边所能到达时间戳最小的节点时间戳）
bridge[i] 边i是否为桥 1是 0不是
c[u] u在的边双连通分量的编号
tot 点双连通分量的个数
num 时间戳编号
*/
vector<int> q[N];
struct node{
    int to, next;
}e[M*2];
void add(int u, int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void Tarjan(int u, int fa){
    dfn[u]=low[u]=++num;
    int v;
    for (int i=head[u]; i; i=e[i].next){
        v=e[i].to;
        if (!dfn[v]){//目标节点未被访问过
            Tarjan(v, u);
            low[u]=min(low[u], low[v]);//更新时间戳
            if (low[v]>dfn[u]){//子树无法访问到u和u的祖先节点
                bridge[i]=bridge[i^1]=1;//i^1==i%2?i-1:i+1
                //(双向边是一起建的，一条单边对应着一条双边)
            }
        }
        if (v == fa){//反祖边（来时的路）不处理
            continue;
        }
        low[u]=min(low[u], dfn[v]);
    }
}
void dfs(int u){
    c[u]=tot;
    q[tot].push_back(u);
    int v;
    for (int i=head[u]; i; i=e[i].next){
        v=e[i].to;
        if (c[v]||bridge[i]){//如果当前边已经在一个边双联同分量中或者当前边是桥
            continue;//（是桥的话桥两边的点可能在同一个边双连通分量中吗？）
        }
        dfs(v);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);//读入优化
    cin >> n >> m;
    int u, v;
    for (int i=1; i<=m; i++){
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i=1; i<=n; i++){
        if (dfn[i]){//访问过了
            continue;
        }
        Tarjan(i, 0);
    }
    for (int i=1; i<=n; i++){
        if (c[i]){//当前节点已经在一个边双连通分量中了
            continue;
        }
        tot++;
        dfs(i);
    }
    printf("%d\n", tot);
    int siz;
    for (int i=1; i<=tot; i++){
        siz=q[i].size();
        printf("%d ", siz);
        for (int j=0; j<siz; j++){
            printf("%d ", q[i][j]);
        }
        printf("\n");
    }

    return 0;
}