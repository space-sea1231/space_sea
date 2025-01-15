#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int M=2e6+10;
int n, m, head[N], cnt;//建边系列
int dfn[N], low[N], sum[N], tot, num, top;
/*
dfn[u] 节点u的时间戳（访问顺序）
low[u] 节点u的回溯值（最多通过一条非树边所能到达时间戳最小的节点时间戳）
sum[] 手写栈 
tot 点双连通分量的个数
num 时间戳编号
top 栈顶编号
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
void Tarjan(int u, int root){
    dfn[u]=low[u]=++num;
    sum[++top]=u;
    if (u==root&&head[u]==0){//判断孤立点
        q[++tot].push_back(u);
        return;
    }
    int v;
    for (int i=head[u]; i; i=e[i].next){
        v=e[i].to;
        if (!dfn[v]){//目标节点未被访问过
            Tarjan(v, root);
            low[u]=min(low[u], low[v]);//更新时间戳
            if (low[v]>=dfn[u]){//子树无法访问到u的祖先节点
                tot++;
                int now;
                do{//保证弹出当前节点
                    now=sum[top--];
                    q[tot].push_back(now);
                }while(now!=v);
                q[tot].push_back(u);//将当前节点一起弹进去
            }
        }
        low[u]=min(low[u], dfn[v]);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);//读入优化
    cin >> n >> m;
    int u, v;
    for (int i=1; i<=m; i++){
        cin >> u >> v;
        if (u==v){//判断自环
            continue;
        }
        add(u, v);
        add(v, u);
    }
    for (int i=1; i<=n; i++){
        if (dfn[i]){//访问过了
            continue;
        }
        Tarjan(i, i);
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