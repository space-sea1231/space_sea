#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
const int Mod=4;
int dx[4]={0, 1, 0, -1};
int dy[4]={1, 0, -1, 0};
int t, n, m, k, x, y, d, cnt;
char c[N][N];
bool vis[N][N];
void init(){
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            vis[i][j]=0;
        }
    }
    vis[x][y]=1;
    cnt=1;
}
bool check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=m&&c[x][y]=='.';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--){
        cin >> n >> m >> k;
        cin >> x >> y >> d;
        init();
        for (int i=1; i<=n; i++){
            for (int j=1; j<=m; j++){
                cin >> c[i][j];
            }
        }
        for (int i=1; i<=k; i++){
            if (check(x+dx[d], y+dy[d])){//判断是否能走
                x+=dx[d], y+=dy[d];
                if (!vis[x][y]){
                    vis[x][y]=1;
                    cnt++;
                }
            }else{//否则就转向
                d=(d+1)%Mod;
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}