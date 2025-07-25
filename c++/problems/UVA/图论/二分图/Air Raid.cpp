#include <bits/stdc++.h>
using namespace std;
const int N=100000;
int t, n, m, cnt;
int to[N], nxt[N], head[N];
int match[N];
bool vis[N];
void init(){
    memset(head, 0, sizeof(head));
    memset(to, 0, sizeof(to));
    memset(nxt, 0, sizeof(nxt));
    memset(match, 0, sizeof(match));
    cnt=0;
}
void add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
bool dfs(int u){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (!vis[v]){
            vis[v]=1;
            if (!match[v]||dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        init();
        cin >> n >> m;
        for (int i=1; i<=m; i++){
            int u, v;
            cin >> u >> v;
            add(u, v+n);
            add(v+n, u);
        }
        int ans=0;
        for (int i=1; i<=n; i++){
            memset(vis, 0, sizeof(vis));
            if (dfs(i)){
                ans++;
            }
        }
        printf("%d\n", n-ans);
    }
    return 0;
}