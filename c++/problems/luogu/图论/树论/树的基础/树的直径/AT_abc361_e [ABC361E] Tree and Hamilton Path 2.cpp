#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n, s;
int cnt, ans;
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
int dep[N];
void Add(int u, int v, int w){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs1(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa) continue;
        dep[v]=dep[u]+w;
        Dfs1(v, u);
        if (dep[s]<dep[v]) s=v;
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
        ans+=w;
    }
    Dfs1(1, 0);
    dep[s]=0;
    Dfs1(s, 0);
    printf("%lld\n", (ans<<1)-dep[s]);

    return 0;
}