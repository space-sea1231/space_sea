#include <bits/stdc++.h>//你教教我怎么封装呗
using namespace std;//还有，帮忙再开一个Terminal,我要编译代码
const int N=1e5+10;
int n, m, r, p;
int cnt, num=1;
int head[N], to[N<<1], nxt[N<<1];
int father[N], dep[N], size[N], son[N];
int top[N], dfn[N], rev[N], a[N];
struct Segment_Tree{
    struct Node{
        int sum, vis;
    }e[N<<2];
    void build(int x, int l, int r){
        if (l==r){
            e[x].sum=a[rev[l]];
            return ;
        }
        int mid=(l+r)>>1;
        build(x<<1, l, mid);
        build(x<<1|1, mid+1, r);
        e[x].sum=(e[x<<1].sum+e[x<<1|1].sum)%p;
    }
    void down(int x, int l, int r){
        e[x<<1].vis=(e[x<<1].vis+e[x].vis)%p;
        e[x<<1|1].vis=(e[x<<1|1].vis+e[x].vis)%p;
        int mid=(l+r)>>1;
        e[x<<1].sum=(e[x<<1].sum+(mid-l+1)*e[x].vis)%p;
        e[x<<1|1].sum=(e[x<<1|1].sum+(r-mid)*e[x].vis)%p;
        e[x].vis=0;
    }
    void add(int x, int l, int r, int L, int R, int w){// 7 5 5 5 5 2
        cerr<<dfn[4];
        if (L<=l&&r<=R){
            e[x].vis=(e[x].vis+w)%p;
            e[x].sum=(e[x].sum+(r-l+1)*w)%p;
            return ;
        }
        down(x, l, r);
        int mid=(l+r)>>1;
        if (mid>=L){
            add(x<<1, l, mid, L, R, w);
        }
        if (mid+1<=R){
            add(x<<1|1, mid+1, r, L, R, w);
        }
        e[x].sum=(e[x<<1].sum+e[x<<1|1].sum)%p;
    }
    int sum(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R){
            return e[x].sum;
        }
        down(x, l, r);
        int mid=(l+r)>>1, ans=0;
        if (L<=mid){
            ans=(ans+sum(x<<1, l, mid, L, R))%p;
        }
        if (mid+1<=R){
            ans=(ans+sum(x<<1|1, mid+1, r, L, R))%p;
        }
        return ans;
    }
}seg;
struct Chain_Tree{
    void add(int u, int v){
        to[++cnt]=v;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void dfs1(int u, int fa){
        father[u]=fa;
        size[u]=1;
        dep[u]=dep[fa]+1;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v!=fa){
                dfs1(v, u);
                size[u]+=size[v];
                if (size[v]>size[son[u]]){
                    son[u]=v;
                }
            }
        }
    }
    void dfs2(int u, int fa){
        if (son[u]){
            dfn[son[u]]=++num;
            top[son[u]]=top[u];
            rev[num]=son[u];
            dfs2(son[u], u);
        }
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (!dfn[v]){
                dfn[v]=++num;
                top[v]=v;
                rev[num]=v;
                dfs2(v, u);
            }
        }
    }
    void add_line(int x, int y, int z){
        int fx=top[x], fy=top[y];
        while (fx!=fy){
            if (dep[fx]<dep[fy]){
                swap(x, y);
                swap(fx, fy);
            }
            seg.add(1, 1, n, dfn[fx], dfn[x], z);
            x=father[fx];
            fx=top[x];
        }
        if (dep[x]>dep[y]){
            swap(x, y);
        }
        seg.add(1, 1, n, dfn[x], dfn[y], z);
    }
    int sum_line(int x, int y){
        int fx=top[x], fy=top[y], ans=0;
        while (fx!=fy){
            if (dep[fx]<dep[fy]){
                swap(x, y);
                swap(fx, fy);
            }
            ans=(ans+seg.sum(1, 1, n, dfn[fx], dfn[x]))%p;
            x=father[fx];
            fx=top[x];
        }
        if (dep[x]>dep[y]){
            swap(x, y);
        }
        ans=(ans+seg.sum(1, 1, n, dfn[x], dfn[y]))%p;
        return ans;
    }
    void add_tree(int x, int z){
        seg.add(1, 1, n, dfn[x], dfn[x]+size[x]-1, z);
    }
    int sum_tree(int x){
        int ans=0;
        ans=seg.sum(1, 1, n, dfn[x], dfn[x]+size[x]-1)%p;
        return ans;
    }
    void init(){
        dfn[1]=top[1]=rev[1]=1;
        dfs1(r, 0);
        dfs2(r, 0);
        seg.build(1, 1, n);
    }
}tree;
int main(){
    // freopen("std.in", "r", stdin);
    // freopen("std.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> r >> p;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        a[i]%=p;
    }
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        tree.add(u, v);
        tree.add(v, u);
    }
    tree.init();
    for (int i=1; i<=m; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int u, v, w;
            cin >> u >> v >> w;
            tree.add_line(u, v, w);
        }
        if (opt==2){
            int u, v;
            cin >> u >> v;
            printf("%d\n", tree.sum_line(u, v));
        }
        if (opt==3){
            int u, w;
            cin >> u >> w;
            tree.add_tree(u, w);
        }
        if (opt==4){
            int u;
            cin >> u;
            printf("%d\n", tree.sum_tree(u));
        }
    }
    cerr<<dfn[4];

    return 0;
}