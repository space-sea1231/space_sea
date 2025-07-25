#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=610;
int n, m, k, cnt;
int to[N*N], nxt[N*N], head[N*N];
int id_1[N][N], id_2[N][N], match[N*N];
char c[N][N];
bool vis[N*N];
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
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> c[i][j];
        }
    }
    int tot=0;
    for (int i=1; i<=n; i++){
        bool flag=0;
        for (int j=1; j<=m; j++){
            if (c[i][j]=='.'){
                if (!flag){
                    flag=1;
                    tot++;
                }
                id_1[i][j]=tot;
            }else{
                flag=0;
            }
        }
    }
    k=tot;
    for (int j=1; j<=m; j++){
        bool flag=0;
        for (int i=1; i<=n; i++){
            if (c[i][j]=='.'){
                if (!flag){
                    flag=1;
                    tot++;
                }
                id_2[i][j]=tot;
            }else{
                flag=0;
            }
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            if (c[i][j]=='.'){
                add(id_1[i][j], id_2[i][j]);
                add(id_2[i][j], id_1[i][j]);
            }
        }
    }
    int ans=0;
    for (int i=1; i<=k; i++){
        memset(vis, 0, sizeof(vis));
        if (dfs(i)){
            ans++;
        }
    }
    printf("%lld", ans);

    return 0;
}