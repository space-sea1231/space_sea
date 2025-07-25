#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
int n, m, cnt=0;
int vis[N][N], id[N][N];
int vis_1[N*N], match[N*N];
int head[N*N], to[N*N], nxt[N*N];
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
bool check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=n&&!vis[x][y];
}
void add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
bool dfs(int u){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (!vis_1[v]){
            vis_1[v]=1;
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
    for (int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        vis[x][y]=1;
    }
    int tot=0;
    for (int x=1; x<=n; x++){
        for (int y=1; y<=n; y++){
                id[x][y]=++tot;
        }
    }
    for (int x=1; x<=n; x++){
        for (int y=1; y<=n; y++){
            if(!vis[x][y]){
                for (int i=0; i<4; i++){
                    int xx=x+dx[i];
                    int yy=y+dy[i];
                    if (check(xx, yy)){
                        add(id[x][y], id[xx][yy]);
                    }
                }
            }
        }
    }
    int ans=0;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            if (vis[i][j]||(i+j)%2==0){
                continue;
            }
            memset(vis_1, 0, sizeof(vis_1));
            if (dfs(id[i][j])){
                ans++;
            }
        }
    }
    printf("%d", ans);

    return 0;
}