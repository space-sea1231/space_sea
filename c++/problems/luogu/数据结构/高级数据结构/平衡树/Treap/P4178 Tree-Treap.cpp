
#include <iostream>
#include <stdio.h>
#include <random>
#include <vector>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=4e4+10;
const int INF=0x3f3f3f3f;

int n, m;
int ans;
#ifdef __Debug
    bool flagg;
    int cntt;
#endif
struct Treap{
    int num=0, root=0;
    struct Node{
        int l, r;
        int vis, val;
        int cnt, size;
    }e[N];
    void Update(int x){
        e[x].size=e[e[x].l].size+e[e[x].r].size+e[x].cnt;
    }
    void Zig(int &x){
        int y=e[x].l;
        e[x].l=e[y].r;
        e[y].r=x, x=y;
        Update(e[x].r);
        Update(x);
    }
    void Zag(int &x){
        int y=e[x].r;
        e[x].r=e[y].l;
        e[y].l=x, x=y;
        Update(e[x].l);
        Update(x);
    }
    int New(int val){
        num++;
        e[num].l=0, e[num].r=0;
        e[num].val=val;
        e[num].vis=rand();
        e[num].size=1;
        e[num].cnt=1;
        return num;
    }
    void Insert(int &x, int val){
        if (x==0){
            x=New(val);
            Update(x);
            return;
        }
        if (val==e[x].val){
            e[x].cnt++;
            Update(x);
        }
        else if (val<e[x].val){
            Insert(e[x].l, val);
            if (e[x].vis<e[e[x].l].vis){
                Zig(x);
            }
        }
        else if (val>e[x].val){
            Insert(e[x].r, val);
            if (e[x].vis<e[e[x].r].vis){
                Zag(x);
                #ifdef __Debug
                    if (val==6){
                        for (int i=1; i<=num; i++){
                            printf("IIOI: x=%d val=%d, l=%d r=%d\n", i, e[i].val, e[i].l, e[i].r);
                        }
                    }
                #endif
            }
        }
        Update(x);
    }
    int ValRank(int x, int val){
        if (x==0){
            return 0;
        }
        if (val==e[x].val){
            #ifdef __Debug
                if (flagg==true){
                    printf("d1:\n");
                    printf("d1: %d\n", e[e[x].l].size+e[x].cnt);
                }
            #endif
            return e[e[x].l].size+e[x].cnt;
        }
        else if (val<e[x].val){
            #ifdef __Debug
                if (flagg==true){
                    printf("d2:\n");
                }
                int tmp=ValRank(e[x].l, val);
                if (flagg==true){
                    printf("d2: %d x=%d val=%d e[x].val=%d\n", tmp, x, val, e[x].val);
                }
            #endif
            return ValRank(e[x].l, val);
        }
        else{
            #ifdef __Debug
                if (flagg==true){
                    printf("d3:\n");
                }    
                int tmp=ValRank(e[x].r, val);
                if (flagg==true){
                    printf("d3: %d\n", tmp+e[e[x].l].size+e[x].cnt);
                }
            #endif
            return ValRank(e[x].r, val)+e[e[x].l].size+e[x].cnt;
        }
    }
    void Init(){
        root=num=0;
    }
}treap;
namespace Tree{
    int cnt, root, minn=INF;
    int siz[N], dep[N];
    int head[N], to[N<<1], val[N<<1], nxt[N<<1];
    vector<int> node;
    
    void Add(int u, int v, int w){
        to[++cnt]=v;
        val[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs1(int u, int fa){
        siz[u]=1;
        int tmp=0;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa) continue;
            Dfs1(v, u);
            siz[u]+=siz[v];
            tmp=max(tmp, siz[v]);
        }
        tmp=max(tmp, n-siz[u]);
        if (minn>tmp){
            minn=tmp;
            root=u;
        }
    }
    void Dfs3(int u, int fa){
        node.push_back(u);
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=val[i];
            if (v==fa) continue;
            dep[v]=dep[u]+w;
            Dfs3(v, u);
        }
    }
    void Dfs2(int u, int fa){//1 0
        dep[u]=0;
        treap.Init();
        treap.Insert(treap.root, 0);
        #ifdef __Debug
            printf("u=%d fa=%d\n", u, fa);
            // cerr << "u=" << u << " fa=" << fa << "\n";
        #endif
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=val[i];
            if (v==fa) continue;
            node.clear();
            dep[v]=w;
            Dfs3(v, u);
            #ifdef __Debug
                for (auto idx:node){
                    printf("%d:dep[%d]=%d\n", u, idx, dep[idx]);
                }
                printf("\n");
            #endif
            for (int idx:node){
                #ifdef __Debug
                    if (dep[3]==5&&cntt==0){
                        flagg=true;
                        cntt++;
                        for (int i=1; i<=treap.num; i++){
                            printf("IAKIOI: x=%d val=%d, l=%d r=%d\n", i, treap.e[i].val, treap.e[i].l, treap.e[i].r);
                        }
                        printf("III:root=%d %d\n", treap.root, m-dep[idx]);
                    }
                #endif
                ans+=treap.ValRank(treap.root, m-dep[idx]);
                #ifdef __Debug
                    flagg=false;
                    printf("Debug1: %d\n", treap.ValRank(treap.root, m-dep[idx]));
                #endif
            }
            for (auto idx:node){
                treap.Insert(treap.root, dep[idx]);
                #ifdef __Debug
                    if (idx==4){
                        for (int i=1; i<=treap.num; i++){
                            printf("IOIAKI: x=%d val=%d, l=%d r=%d\n", i, treap.e[i].val, treap.e[i].l, treap.e[i].r);
                        }
                    }
                #endif

            }
        }
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa) continue;
            Dfs2(v, u);
        }
    }
}
using namespace Tree;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i=1; i<n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w);
        Add(v, u, w);
    }
    cin >> m;
    Dfs1(1, 0);
    #ifdef __Debug
        printf("root=%d\n", root);
        // cerr << root << "\n";
    #endif
    Dfs2(root, 0);
    printf("%d\n", ans);

    return 0;
}