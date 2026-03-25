#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
const int INF=(1<<30);
int n, m, cnt, num=1;
int summ, maxx;
int maxn[N], sum[N], a[N];
int head[N], to[N<<1], nxt[N<<1];
int father[N], dep[N], size[N], son[N];
int top[N], dfn[N], rev[N];
struct Sigment_Tree{
    void build(int x, int l, int r){
        int mid=(l+r)>>1;
        if (l==r){
            maxn[x]=a[rev[l]];
            sum[x]=a[rev[l]];
            return ;
        }
        build(x<<1, l, mid);
        build(x<<1|1, mid+1, r);
        sum[x]=sum[x<<1]+sum[x<<1|1];
        maxn[x]=max(maxn[x<<1], maxn[x<<1|1]);
    }
    void change(int x, int l, int r, int pos, int val){
        if (l==r&&l==pos){
            sum[x]=val;
            maxn[x]=val;
            return ;
        }
        int mid=(l+r)>>1;
        if (mid>=pos){
            change(x<<1, l, mid, pos, val);
        }
        if (mid+1<=pos){
            change(x<<1|1, mid+1, r, pos, val);
        }
        sum[x]=sum[x<<1]+sum[x<<1|1];
        maxn[x]=max(maxn[x<<1], maxn[x<<1|1]);
    }
    void query(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R){
            summ+=sum[x];
            maxx=max(maxx, maxn[x]);
            return ;
        }
        int mid=(l+r)>>1;
        if (mid>=L){
            query(x<<1, l, mid, L, R);
        }
        if (mid+1<=R){
            query(x<<1|1, mid+1, r, L, R);
        }
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
                rev[num]=v;
                top[v]=v;
                dfs2(v, u);
            }
        }
    }
    void ask(int x, int y){
        int fx=top[x], fy=top[y];
        while (fx!=fy){
            if (dep[fx]<dep[fy]){
                swap(x, y);
                swap(fx, fy);
            }
            seg.query(1, 1, num, dfn[fx], dfn[x]);
            x=father[fx];
            fx=top[x];
        }
        if (dep[x]>dep[y]){
            swap(x, y);
        }
        seg.query(1, 1, num, dfn[x], dfn[y]);
    }
    void init(){
        dfn[1]=top[1]=rev[1]=1;
        dfs1(1, 0);
        dfs2(1, 0);
        seg.build(1, 1, num);
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        tree.add(u, v);
        tree.add(v, u);
    }
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    tree.init();
    cin >> m;
    string s;
    for (int i=1; i<=m; i++){
        int u, v;
        cin >> s >> u >> v;
        if (s=="CHANGE"){
            seg.change(1, 1, num, dfn[u], v);
        }else{
            summ=0;
            maxx=-INF;
            tree.ask(u, v);
            if (s=="QMAX"){
                printf("%d\n", maxx);
            }
            if (s=="QSUM"){
                printf("%d\n", summ);
            }
        }
    }

    return 0;
}