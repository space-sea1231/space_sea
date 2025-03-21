#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int INF=1<<30;
char c[N][N];
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
int vis[N][N];
int n, m;
struct node{
    int x, y, sum;
}s, f;
queue<node> q;
void init(){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            vis[i][j]=INF;
        }
    }
}
bool check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=m&&c[x][y]!='*';
}
void dfs(int d, node u){
    int x=u.x, y=u.y, sum=u.sum;
    if (!check(x, y)){
        return ;
    }
    if (vis[x][y]<sum){
        return ;
    }
    vis[x][y]=sum;
    q.push({x, y, sum});
    dfs(d, (node){x+dx[d], y+dy[d], sum});
}
void bfs(){
    while (!q.empty()){
        node u=q.front(), v=q.front();
        q.pop();
        v.sum++;
        for (int i=0; i<4; i++){
            v.x=u.x+dx[i];
            v.y=u.y+dy[i];
            dfs(i, v);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    init();
    cin >> m >> n;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> c[i][j];
            if (c[i][j]=='C'){
                if (s.x==0){
                    s.x=i, s.y=j;
                }else{
                    f.x=i, f.y=j;
                }
            }
        }
    }
    q.push(s);
    bfs();
    printf("%d", vis[f.x][f.y]-1);

    return 0;
}