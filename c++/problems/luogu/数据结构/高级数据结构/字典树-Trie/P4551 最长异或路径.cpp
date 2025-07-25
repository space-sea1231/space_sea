#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e5+10;

int n;
int ans;
int f[N];

namespace Trie{
    int root=1, tot=1;

    struct Node{
        int son[2];
    }node[N<<5];

    int Search(int x){
        int now=root, sum=0;
        for (int i=30; i>=0; i--){
            bool flag=(x>=(1<<i));
            x=(x<(1<<i)?x:x-(1<<i));
            if (node[now].son[flag^1]){
                now=node[now].son[flag^1];
                sum=sum+(1<<i);
            }
            else if (node[now].son[flag]){
                now=node[now].son[flag];
            }
            else{
                return sum;
            }
        }
        return sum;
    }
    void Add(int x){
        int now=root;
        for (int i=30; i>=0; i--){
            bool flag=(x>=(1<<i));
            x=(x<(1<<i)?x:x-(1<<i));
            if (node[now].son[flag]){
                now=node[now].son[flag];
            }
            else{
                node[now].son[flag]=++tot;
                now=tot;
            }
        }
        return;
    }
}
namespace Graph{
    int cnt;
    int head[N], to[N<<1], nxt[N<<1], val[N<<1];
    
    void Add(int u, int v, int w){
        to[++cnt]=v;
        val[cnt]=w;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs(int u, int fa){
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=val[i];
            if (v==fa) continue;
            f[v]=f[u]^w;
            Dfs(v, u);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Graph::Add(u, v, w);
        Graph::Add(v, u, w);
    }
    Graph::Dfs(1, 0);
    for (int i=1; i<=n; i++){
        ans=max(ans, Trie::Search(f[i]));
        Trie::Add(f[i]);
    }
    printf("%d\n", ans);

    return 0;
}