#include <bits/stdc++.h>
using namespace std;
const int N=20;
const int M=15;
int n, m, p, k;
int cnt[N][N], key[N][N];
int gate[N][N][N][N];
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
bool vis[N][N][1<<M];
struct Node{
    int x, y, dis, key;
};
bool Check(int x, int y, int key, int opt){
    return x>=1&&x<=n&&y>=1&&y<=m&&opt>=0&&(!opt||key&(1<<(opt-1)));
}
int Bfs_01(int sx, int sy){
    queue<Node> q;
    int sk=key[sx][sy];
    q.push({sx, sy, 0, sk});
    vis[sx][sy][sk]=1;
    while (!q.empty()){
        Node u=q.front();
        q.pop();
        int ux=u.x, uy=u.y, ud=u.dis, uk=u.key;
        if (ux==n&&uy==m){
            return ud;
        }
        for (int i=0; i<4; i++){
            int vx=ux+dx[i];
            int vy=uy+dy[i];
            int opt=gate[ux][uy][vx][vy];
            if (Check(vx, vy, uk, opt)){
                int vk=uk|key[vx][vy];
                int vd=ud+1;
                if (!vis[vx][vy][vk]){
                    vis[vx][vy][vk]=1;
                    q.push({vx, vy, vd, vk});
                }
            }
        }
    }
    return -1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> p >> k;
    for (int i=1; i<=k; i++){
        int ux, uy, vx, vy, opt;
        cin >> ux >> uy >> vx >> vy >> opt;
        if (opt==0){
            gate[ux][uy][vx][vy]=-1;
            gate[vx][vy][ux][uy]=-1;
        }else{
            gate[ux][uy][vx][vy]=opt;
            gate[vx][vy][ux][uy]=opt;
        }
    }
    int s;
    cin >> s;
    for (int i=1; i<=s; i++){
        int x, y, opt;
        cin >> x >> y >> opt;
        key[x][y]|=(1<<(opt-1));
    }
    printf("%d\n", Bfs_01(1, 1));

    return 0;
}