#include <bits/stdc++.h>
using namespace std;
const int N=500;
int n, m, k, cnt;
int to[N<<2], nxt[N<<2], head[N<<1];
int id_1[N][N], id_2[N][N], match[N<<1];
char c[N][N];
bool vis[N<<1];
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
            if (c[i][j]=='*'){
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
            if (c[i][j]=='*'){
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
            if (c[i][j]=='*'){
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
    printf("%d", ans);

    return 0;
}