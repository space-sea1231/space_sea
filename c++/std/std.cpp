#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N=4e4+10;
const int INF=0x3f3f3f3f;

int n, m;
int cnt, root, minn;
int siz[N], top[N], dep[N];
int head[N], to[N<<1], val[N<<1], nxt[N<<1];

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
        Dfs(v, u);
        siz[u]+=siz[v];
        tmp=max(tmp, siz[v]);
    }
    tmp=max(tmp, n-siz[u]);
    if (tmp<minn){
        minn=tmp;
        root=u;
    }
}
void Dfs2(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa) continue;
        top[v]=v;
        dep[v]=w;
        Dfs3(v, u);
    }

}
void Dfs3(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa) continue;
        top[v]=top[u];
        dep[v]=dep[u]+w;
        Dfs3(v, u);
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
    Dfs2(root, 0);
    return 0;
}