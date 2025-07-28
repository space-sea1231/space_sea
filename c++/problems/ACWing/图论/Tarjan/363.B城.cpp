#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int M=5e5+10;
int head[N], cnt, n, m;//建边系列
int dfn[N], low[N], ans[N], siz[N], tot, num;//Tarjan系列
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
    siz[u]=1;
    int v, child=0, sum=0;
    for (int i=head[u]; i; i=e[i].next){
        v=e[i].to;
        if (!dfn[v]){
            Tarjan(v, root);
            low[u]=min(low[u], low[v]);
            siz[u]+=siz[v];
            if (low[v]>=dfn[u]){
                child++;
                ans[u]+=siz[v]*(n-siz[v]);
                sum+=siz[v];
                if (child>1||u!=root){
                    cut[u]=1;
                }
            }
        }
        low[u]=min(low[u], dfn[v]);
    }
    if (cut[u]){
        ans[u]+=(n-sum-1)*(sum+1)+(n-1); 
    }else{
        ans[u]=2*(n-1);
    }
}
signed main(){
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
    for (int i=1; i<=n; i++){
        printf("%lld\n", ans[i]);
    }
    return 0;
}