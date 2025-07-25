#include <bits/stdc++.h>
using namespace std;
const int N=2e2+10;
const int M=4e5+10;
int dx[4]={-2, -2, -1, -1};
int dy[4]={-1, 1, -2, 2};
int head[N*N], to[M], nxt[M];
int n, cnt, sum;
int match[N*N], id[N][N];
bool vis[N*N], a[N][N];
void add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
bool check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=n&&!a[x][y];
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
    cin >> n;
    int num=0;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            char c;
            cin >> c;
            a[i][j]=c-'0';
            id[i][j]=++num;
            sum+=(!a[i][j]);
        }
    }
    for (int x=1; x<=n; x++){
        for (int y=1; y<=n; y++){
            if (!a[x][y]){
                for (int i=0; i<4; i++){
                    int xx=x+dx[i];
                    int yy=y+dy[i];
                    if (check(xx, yy)){
                        add(id[x][y], id[xx][yy]);
                        add(id[xx][yy], id[x][y]);
                    }
                }
            }
        }
    }
    int ans=0;
    for (int x=1; x<=n; x++){
        for (int y=1; y<=n; y++){
            if (!a[x][y]&&(x+y)%2==0){
                memset(vis, 0, sizeof(vis));
                if (dfs(id[x][y])){
                    ans++;
                }
            }
        }
    }
    printf("%d\n", sum-ans);

    return 0;
}