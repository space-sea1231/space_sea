#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=1e5+10;
const int INF=1e9;
int n, m, cnt, cntt, head[N], a[N], ru[N], dp[N];//建边系列
int dfn[N], low[N], sum[N], b[N], c[N], tot, top, num;//tarjan系列
bool vis[N], vis_1[N];
vector<int> q[N];
vector<int> p[N];
/*
P3387 【模板】缩点
所需算法：
图论->链式前向星->Tarjan:强连通分量
图论->拓扑排序
动态规划->线性dp
------------------------建边系列------------------------------------
-------基本-------
n, m 基本输入
a[u] 点u的点权
cnt，head[u] 链式前向星建边
-------拓扑-------
cntt 拓扑排序节点遍历顺序
ru[u] 点u的入边 
-------dp-------
dp[u] 遍历到节点u时的最到权值和
------------------------Tarjan系列----------------------------------
dfn[u] 节点u的时间戳（访问顺序）
low[u] 节点u的回溯值（最多通过一条非树边所能到达时间戳最小的节点时间戳）
b[i] 编号为i的强连通分量的权值和
c[u] 节点u所属强连通分量的编号
vis[u] 节点u是否在栈中
vis_1[u] 节点u的强连通分量是否被访问过
sum[] 手写栈 
p[u] 节点u的出边
p[v] 节点v的出边
tot 强连通分量的个数
num 时间戳编号
top 栈顶编号
*/
struct node{
    int to, next, from;
}e[M];
void add(int u, int v){
    e[++cnt].from=u;
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void Tarjan(int u){
    dfn[u]=low[u]=++num;
    sum[++top]=u, vis[u]=1;
    int v;
    for (int i=head[u]; i; i=e[i].next){
        v=e[i].to;
        if (!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u], low[v]);
        }else if (vis[v]){
            low[u]=min(low[u], dfn[v]);
        }  
    }
    if (low[u]==dfn[u]){
        tot++;
        int now;
        do{
            now=sum[top--];
            c[now]=tot;
            b[tot]+=a[now];
            vis[now]=0;
        }while(u!=now);
    }
}
void topu(){
    queue<int> qwq;
    for (int i=1; i<=tot; i++){
        dp[i]=b[i];
        if (ru[i]){
            continue;
        }
        qwq.push(i);
    }
    int u, v, siz;
    while(!qwq.empty()){
        u=qwq.front();
        qwq.pop();
        siz=q[u].size();
        for (int i=0; i<siz; i++){
            v=q[u][i];
            dp[v]=max(dp[v], dp[u]+b[v]);
            ru[v]--;
            if (ru[v]){
                continue;
            }
            qwq.push(v);
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    for (int i=1; i<=m; i++){
        cin >> u  >> v;
        if (u==v){
            continue;
        }
        add(u, v);
    }
    for (int i=1; i<=n; i++){
        if (dfn[i]){
            continue;
        }
        Tarjan(i);
    }
    int x, y;
    for (int i=1; i<=cnt; i++){
        x=c[e[i].from], y=c[e[i].to];
        if (x==y){
            continue;
        }
        q[x].push_back(y);
        p[y].push_back(x);
        ru[y]++;
    }
    topu();
    int maxn=-INF;
    for (int i=1; i<=tot; i++){
        maxn=max(maxn, dp[i]);
    }
    printf("%d", maxn);

    return 0;
}