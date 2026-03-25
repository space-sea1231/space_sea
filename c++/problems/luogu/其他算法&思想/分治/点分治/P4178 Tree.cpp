#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=4e4+10;
const int INF=0x3f3f3f3f;

int n, m;
int cnt, ans, root, minn;
int siz[N], top[N], dep[N], tot[N];
int head[N], to[N<<1], val[N<<1], nxt[N<<1];
vector<int> node;

bool cmp(int srcx, int srcy){
    return dep[srcx]<dep[srcy];
}
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
    if (tmp<minn){
        minn=tmp;
        root=u;
    }
}
void Dfs3(int u, int fa){
    node.push_back(u);
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa) continue;
        top[v]=top[u];
        tot[top[v]]++;
        dep[v]=dep[u]+w;
        Dfs3(v, u);
    }
}
void Dfs2(int u, int fa){
    node.clear();
    node.push_back(u);
    top[u]=u;
    dep[u]=0;
    tot[top[u]]=1;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa) continue;
        top[v]=v;
        tot[top[v]]++;
        dep[v]=w;
        // #ifdef __Debug
        //     printf("Debug6: dep[%d]=%d\n", v, dep[v]);
        // #endif
        Dfs3(v, u);
    }
    #ifdef __Debug
        queue<pair<int, int> >q;
        printf("root=%d\n", u);
        q.push(make_pair(u, fa));
        while (q.empty()==false){
            int qu=q.front().first;
            int qfa=q.front().second;
            q.pop();
            for (int i=head[qu]; i; i=nxt[i]){
                int v=to[i];
                if (v==qfa) continue;
                printf("u=%d top=%d dep=%d\n", v, top[v], dep[v]);
                q.push(make_pair(v, qu));
            }
        }
        printf("\n");
    #endif
    sort(node.begin(), node.end(), cmp);
    #ifdef __Debug
        printf("Debug4:\n");
        for (auto idx:node){
            printf("%d ", idx);
        }
        printf("\n");
    #endif
    // #ifdef __Debug
    //     for (int i=1; i<=n; i++){
    //         printf("Debug7: dep[%d]=%d", i, dep[i]);
    //     }
    // #endif
    int l=0, r=node.size()-1;
    while (l<r){
        tot[top[node[l]]]--;
        while (l<r&&dep[node[l]]+dep[node[r]]>m){
            tot[top[node[r]]]--;
            r--;
        }
        if (dep[node[l]]+dep[node[r]]>m||l==r) break;
        #ifdef __Debug
            printf("Debug5: r=%d l=%d %d\n", r, l, tot[top[node[l]]]);
            printf("Debug5: depl=%d depr=%d\n", dep[node[l]], dep[node[r]]);
        #endif
        ans+=r-l-tot[top[node[l]]];
        l++;
    }
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa) continue;
        Dfs2(v, u);
    }
}
void Init(){
    minn=INF;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Init();
    cin >> n;
    for (int i=1; i<n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w);
        Add(v, u, w);
    }
    cin >> m;
    Dfs1(1, 0);
    // #ifdef __Debug
    //     printf("root=%d\n", root);
    // #endif
    Dfs2(root, 0);
    printf("%d\n", ans);

    return 0;
}