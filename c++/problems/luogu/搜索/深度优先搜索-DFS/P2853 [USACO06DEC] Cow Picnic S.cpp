#include <bits/stdc++.h>
using namespace std;
const int K=1e2+10;
const int N=1e3+10;
const int M=1e4+10;
int n, m, k, cnt, ans;
int head[N], to[M], nxt[M];
int a[K], tot[N];
bool vis[N];
void add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void search(int u){
    vis[u]=1;
    tot[u]++;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (vis[v]){
            continue;
        }
        search(v);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> k >> n >> m;
    for (int i=1; i<=k; i++){
        cin >> a[i];
    }
    for (int i=1; i<=m; i++){
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    for (int i=1; i<=k; i++){
        memset(vis, 0, sizeof(vis));
        search(a[i]);
    }
    for (int i=1; i<=n; i++){
        if (tot[i]==k){
            ans++;
        }
    }
    printf("%d", ans);

    return 0;
}