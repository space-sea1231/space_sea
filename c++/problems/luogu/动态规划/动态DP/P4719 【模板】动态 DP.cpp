#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int INF=0x3f3f3f3f;
int n, m;
int a[N];
struct Node{
    int g[2][2];
    Node operator*(const Node &a)const{
        Node b;
        for (int i=0; i<2; i++){
            for (int j=0; j<2; j++){
                for (int k=0; k<2; k++){
                    b.g[i][j]=max(b.g[i][j], g[i][k]+a.g[k][j]);
                }
            }
        }
        return b;
    }
    Node(){
        memset(g, 0, sizeof(g));
    }
}e[N], tree[N];
struct Segment_Tree{
    int *rev;
    void Push_up(int x){
        tree[x]=tree[x<<1]*tree[x<<1|1];
    }
    void Build(int x, int l, int r){
        if (l==r){
            tree[x]=e[rev[l]];
            return ;
        }
        int mid=(l+r)>>1;
        Build(x<<1, l, mid);
        Build(x<<1|1, mid+1, r);
        Push_up(x);
    }
    void Change(int x, int l, int r, int pos){
        if (l==r){
            tree[x]=e[rev[l]];
            return ;
        }
        int mid=(l+r)>>1;
        if (pos<=mid) Change(x<<1, l, mid, pos);
        else Change(x<<1|1, mid+1, r, pos);
        Push_up(x);
    }
    Node Query(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R) return tree[x];
        int mid=(l+r)>>1;
        if (R<=mid) return Query(x<<1, l, mid, L, R);
        if (mid<L) return Query(x<<1|1, mid+1, r, L, R);
        return Query(x<<1, l, mid, L, R)*Query(x<<1|1, mid+1, r, L, R);
    }
}Seg;
struct Chain_tree{
    int cnt, num;
    int head[N], nxt[N<<1], to[N<<1];
    int dep[N], size[N], son[N], fa[N];
    int seg[N], rev[N], top[N], End[N];
    int dp[N][2];
    void Add(int u, int v){
        to[++cnt]=v;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs1(int u){
        size[u]=1;
        dp[u][1]=a[u];
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa[u]) continue;
            dep[v]=dep[u]+1;
            fa[v]=u;
            Dfs1(v);
            size[u]+=size[v];
            if (size[v]>size[son[u]]) son[u]=v;
            dp[u][1]+=dp[v][0];
            dp[u][0]+=max(dp[v][0], dp[v][1]);
        }
    }
    void Dfs2(int u, int tp){
        top[u]=tp;
        seg[u]=++num;
        rev[num]=u;
        End[tp]=num;
        e[u].g[1][0]=a[u];
        e[u].g[1][1]=-INF;
        if (!son[u]) return ;
        Dfs2(son[u], tp);
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa[u]||v==son[u]) continue;
            Dfs2(v, v);
            e[u].g[0][0]+=max(dp[v][0], dp[v][1]);
            e[u].g[1][0]+=dp[v][0];
        }
        e[u].g[0][1]=e[u].g[0][0];
    }
    void Update(int x, int val){
        e[x].g[1][0]+=val-a[x];
        a[x]=val;
        while (x){
            Node last=Seg.Query(1, 1, n, seg[top[x]], End[top[x]]);
            Seg.Change(1, 1, n, seg[x]);
            Node now=Seg.Query(1, 1, n, seg[top[x]], End[top[x]]);
            x=fa[top[x]];
            e[x].g[0][0]+=max(now.g[0][0], now.g[1][0])-max(last.g[0][0], last.g[1][0]);
            e[x].g[0][1]=e[x].g[0][0];
            e[x].g[1][0]+=now.g[0][0]-last.g[0][0];
        }
    }
    void Init(){
        Dfs1(1);
        Dfs2(1, 1);
        Seg.Build(1, 1, n); 
    }
    Chain_tree(){
        Seg.rev=rev;
        dep[1]=1;
    }
}Tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i=1; i<=n; i++) cin >> a[i];
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        Tree.Add(u, v), Tree.Add(v, u);
    }
    Tree.Init();
    for (int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        Tree.Update(x, y);
        Node ans=Seg.Query(1, 1, n, 1, Tree.End[1]);
        printf("%d\n", max(ans.g[0][0], ans.g[1][0]));
    }

    return 0;
}