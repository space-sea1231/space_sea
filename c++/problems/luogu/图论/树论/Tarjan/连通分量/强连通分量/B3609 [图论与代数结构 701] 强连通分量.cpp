#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, m, cnt, head[N];//建边系列
int dfn[N], low[N], sum[N], c[N], tot, top, num;//tarjan系列
bool vis[N], vis_1[N];
vector<int> q[N];
/*
dfn[u] 节点u的时间戳（访问顺序）
low[u] 节点u的回溯值（最多通过一条非树边所能到达时间戳最小的节点时间戳）
c[u] 节点u所属强连通分量的编号
vis[u] 节点u是否在栈中
vis_1[u] 节点u的强连通分量是否被访问过
sum[] 手写栈 
vector[i] 第i个强连通分量中的点编号
tot 强连通分量的个数
num 时间戳编号
top 栈顶编号
*/
struct node{
    int to, next;
}e[N];
void add(int u, int v){
    e[++cnt].to=v;
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
            vis[now]=0;
            q[tot].push_back(now);
        }while(u!=now);
    }
}
int main(){//私信
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v;
    for (int i=1; i<=m; i++){
        cin >> u  >> v;
        add(u, v);
    }
    for (int i=1; i<=n; i++){
        if (dfn[i]){
            continue;
        }
        Tarjan(i);
    }
    printf("%d\n", tot);
    for(int i=1; i<=tot; i++){
		sort(q[i].begin(), q[i].end());
	}
	for (int i=1; i<=n; i++){
        if (vis_1[c[i]]){
            continue;
        }
        vis_1[c[i]]=1;
        for (int j=0; j<q[c[i]].size(); j++){
            printf("%d ", q[c[i]][j]);
        }
        printf("\n");
	}
    return 0;
}