#include <bits/stdc++.h>
using namespace std;
const int N=2e2+10;
int n, m, k, cnt=0;
int vis[N<<1], match[N<<1];
int to[N<<2], nxt[N<<2], head[N<<1];
void init(){
    memset(match, 0, sizeof(match));
    memset(to, 0, sizeof(to));
    memset(nxt, 0, sizeof(nxt));
    memset(head, 0, sizeof(head));
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
    while (1){
        init();
        cin >> n;
        if (n==0){
            return 0;
        }
        cin >> m >> k;
        for (int i=1; i<=k; i++){
            int id, u, v;
            cin >> id >> u >> v;
            if (u==0||v==0){
                continue;
            }
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
        printf("%d\n", ans);
    }

    return 0;
}