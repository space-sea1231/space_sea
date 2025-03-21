#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int M=1e7+10;
const int INF=0x7fffffff;
int n, m, cnt, root, num;
int to[N<<1], nxt[N<<1], edge[N<<1], head[N];
int dis[N], siz[N], mxsiz[N], tot[M], ask[N], ans[N];
bool vis[N];
int l, r, que[N];
// struct Stack{
//     int top;
//     int sum[N];
//     void Push(int x){
//         sum[++top]=x;
//     }
// }s;
int sum[N];
int top;
void Add(int u, int v, int w){
    to[++cnt]=v;
    edge[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs_Root(int u, int fa){
    siz[u]=1, mxsiz[u]=0;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa||vis[fa]){
            continue;
        }
        Dfs_Root(v, u);
        siz[u]+=siz[v];
        mxsiz[u]=max(mxsiz[u], siz[v]);
    }
    mxsiz[u]=max(mxsiz[u], n-mxsiz[u]);
    if (mxsiz[u]<mxsiz[root]){
        root=u;
    }
}
void Cala(int u, int fa){
    // s.Push(dis[u]);
    sum[++top]=dis[u];
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=edge[i];
        if (v==fa){
            continue;
        }
        dis[v]=dis[u]+w;
        Cala(v, u);
    }
}
void Dfs(int u, int fa){
    l=0, r=0;
    tot[0]=1, vis[u]=1;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=edge[i];
        if (v==fa||vis[v]){
            continue;
        }
        dis[v]=w;
        Cala(v, u);
        for (int j=1; j<=top; j++){
            for (int k=1; k<=m; k++){
                if (ask[k]>=sum[j]){
                    ans[k]|=tot[ask[k]-sum[j]];
                }
            }
        }
        for (int j=1; j<=top; j++){
            if (sum[j]<M){
                que[++r]=sum[j];
                tot[sum[j]]=1;
            }
        }
        top=0;
    }
    while (l<=r){
        tot[que[l++]]=0;
    }
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa||vis[v]){
            continue;
        }
        root=0;
        num=siz[v], mxsiz[root]=INF;
        Dfs_Root(v, u);
        Dfs_Root(root, 0);
        Dfs(root, u);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w);
        Add(v, u, w);
    }
    for (int i=1; i<=m; i++){
        cin >> ask[i];
    }
    mxsiz[root]=INF, num=n;
    Dfs_Root(1, 0);
    Dfs_Root(root, 0);
    Dfs(root, 0);
    for (int i=1; i<=m; i++){
        if (ans[i]){
            printf("AYE\n");
        }else{
            printf("NAY\n");
        }
    }

    return 0;
}