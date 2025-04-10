#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int n;
int cnt, ans, root;
int f[N][2];
int father[N];
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
bool vis[N];
void Add(int u, int v, int w=1){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
int Dfs(int u, bool d){
    f[u][0]=f[u][1]=0;
    vis[u]=1;
    int c=INF;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==root) continue;
        int res=Dfs(v, d);
        f[u][0]+=res;
        c=min(c, res-f[v][0]);
    }
    f[u][1]=f[u][0]-c+1;
    if (d&&father[root]==u) f[u][1]+=c;
    return max(f[u][0], f[u][1]);
}
int Solve(int x){
    for (root=x; !vis[father[root]]; vis[root]=1){
        root=father[root];
    }
    int tmp=Dfs(root, 0);
    Dfs(root, 1);
    return max(tmp, f[root][0]);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> father[i];
        Add(father[i], i);
    }
    for (int i=1; i<=n; i++){
        if (!vis[i]){
            ans+=Solve(i);
        }
    }
    printf("%d\n", ans);

    return 0;
}