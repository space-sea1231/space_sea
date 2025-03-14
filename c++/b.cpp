struct Chain_Tree{
    Segment_Tree Seg;
    int cnt, num=1, root;
    int father[N], son[N], top[N];
    int size[N], dep[N];
    int seg[N], rev[N];
    int head[N], to[N<<1], nxt[N<<1];
    void Add(int u, int v){
        to[++cnt]=v;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs1(int u, int fa){
        father[u]=fa;
        dep[u]=dep[fa]+1;
        size[u]=1;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa){
                continue;
            }
            Dfs1(v, u);
            size[u]+=size[v];
            if (size[v]>size[son[u]]){
                son[u]=v;
            }
        }
    }
    void Dfs2(int u, int fa){
        if (son[u]){
            int v=son[u];
            top[v]=top[u];
            seg[v]=++num;
            rev[num]=v;
            Dfs2(v, u);
        }
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa||v==son[u]){
                continue;
            }
            top[v]=v;
            seg[v]=++num;
            rev[num]=v;
            Dfs2(v, u);
        }
    }
    void Add_Line(int x, int y, int z){
        int fx=top[x], fy=top[y];
        while (fx!=fy){
            if (dep[fx]<dep[fy]){
                swap(fx, fy);
                swap(x, y);
            }
            Seg.Add(1, 1, n, seg[fx], seg[x], z);
            x=father[top[x]], fx=top[x];
        }
        if (dep[x]>dep[y]){
            swap(x, y);
        }
        Seg.Add(1, 1, n, seg[x], seg[y], z);
    }
    void Add_Tree(int x, int z){
        Seg.Add(1, 1, n, seg[x], seg[x]+size[x]-1, z);
    }
    int Query_Tree(int x){
        return Seg.Query(1, 1, n, seg[x], seg[x]+size[x]-1);
    }
    int Query_Line(int x, int y){
        int fx=top[x], fy=top[y], ans=0;
        while (fx!=fy){
            if (dep[fx]<dep[fy]){
                swap(fx, fy);
                swap(x, y);
            }
            ans=(ans+Seg.Query(1, 1, n, seg[fx], seg[x]))%q;
            x=father[top[x]], fx=top[x];
        }
        if (dep[x]>dep[y]){
            swap(x, y);
        }
        ans=(ans+Seg.Query(1, 1, n, seg[x], seg[y]))%q;
        return ans;
    }
    void Init(){
        root=r;
        seg[root]=1;
        top[root]=root;
        rev[1]=root;
        Dfs1(root, 0);
        Dfs2(root, 0);
        Seg.Build(1, 1, n, rev);
    }
}