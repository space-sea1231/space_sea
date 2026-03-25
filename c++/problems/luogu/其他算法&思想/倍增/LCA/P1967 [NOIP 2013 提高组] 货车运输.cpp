#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=5e4+10;
const int K=40;
const int INF=0x7fffffff;
int n, m;
bool vis[N];
struct Least_Common_Ancestors{
    int cnt;
    int head[N], dep[N], father[N][K], dp[N][K];
    int to[M<<1], nxt[M<<1], val[M<<1];
    void Add(int u, int v, int w){
        to[++cnt]=v;
        val[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs(int u, int fa){
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=val[i];
            if (v==fa){
                continue;
            }
            dep[v]=dep[u]+1;
            father[v][0]=u;
            dp[v][0]=w;
            for (int j=1; j<=30; j++){
                father[v][j]=father[father[v][j-1]][j-1];
                dp[v][j]=min(dp[v][j-1], dp[father[v][j-1]][j-1]);
            }
            Dfs(v, u);
        }
    }
    int lca(int x, int y){
        int ans=INF;
        if (dep[x]<dep[y]){
            swap(x, y);
        }
        for (int i=30; i>=0; i--){
            if (dep[father[x][i]]>=dep[y]){
                ans=min(ans, dp[x][i]);
                x=father[x][i];
            }
        }
        if (x==y){
            return ans;
        }
        for (int i=30; i>=0; i--){
            if (father[x][i]!=father[y][i]){
                ans=min(ans, dp[x][i]);
                ans=min(ans, dp[y][i]);
                x=father[x][i], y=father[y][i];
            }
        }
        ans=min(ans, dp[x][0]);
        ans=min(ans, dp[y][0]);
        return ans;
    }
    Least_Common_Ancestors(){
        memset(dp, 0x3f, sizeof(dp));
    }
}Lca;
struct Union_Find{
    int fa[N];
    int Find(int x){
        if (x==fa[x]){
            return x;
        }
        return fa[x]=Find(fa[x]);
    }
    Union_Find(){
        for (int i=1; i<N; i++){
            fa[i]=i;
        }
    }
}Uf;
struct Kruskal{
    bool vis[N];
    int cnt;
    struct Node{
        int u, v, w;
        bool operator<(const Node &a)const{
            return w>a.w;
        }
    }e[M<<1];
    void Add(int u, int v, int w){
        e[++cnt].u=u;
        e[cnt].v=v;
        e[cnt].w=w;
    }
    void kruskal(){
        sort(e+1, e+cnt+1);
        for (int i=1; i<=cnt; i++){
            int u=e[i].u, v=e[i].v, w=e[i].w;
            int fu=Uf.Find(u), fv=Uf.Find(v);
            if (fu!=fv){
                Uf.fa[fu]=fv;
                Lca.Add(u, v, w);
                Lca.Add(v, u, w);
            }
        }
    }
}Kru;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Kru.Add(u, v, w);
        Kru.Add(v, u, w);
    }
    Kru.kruskal();
    for (int i=1; i<=n; i++){
        int fi=Uf.Find(i);
        if (!vis[fi]){
            Lca.Dfs(i, 0);
            vis[fi]=1;
        }
    }
    int q;
    cin >> q;
    for (int i=1; i<=q; i++){
        int x, y;
        cin >> x >> y;
        if (Uf.Find(x)==Uf.Find(y)){
            printf("%d\n", Lca.lca(x, y));
        }else{
            printf("-1\n");
        }
    }

    return 0;
}