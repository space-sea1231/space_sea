#include <bits/stdc++.h>
using namespace std;
const int N=2e4+10;
const int M=1e5+10;
int head[N], cnt, n, m;//建边系列
int dfn[N], low[N], tot, num;//Tarjan系列
bool cut[N];
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
    int v, child=0;
    for (int i=head[u]; i; i=e[i].next){
        v=e[i].to;
        if (!dfn[v]){
            Tarjan(v, root);
            low[u]=min(low[u], low[v]);
            if (low[v]>=dfn[u]){
                child++;
                if (child>1||u!=root){
                    cut[u]=1;
                }
            }
        }
        low[u]=min(low[u], dfn[v]);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v;
    for (int i=1; i<=m; i++){
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i=1; i<=n; i++){
        if (dfn[i]){
            continue;
        }
        Tarjan(i, i);
    }
    int cntt=0;
    for (int i=1; i<=n; i++){
        if (cut[i]){
            cntt++;
        }   
    }
    printf("%d\n", cntt);
    for (int i=1; i<=n; i++){
        if (cut[i]){
            printf("%d ", i);
        }
    }
    return 0;
}