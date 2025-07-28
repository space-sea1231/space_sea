#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <algorithm>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=5e2+10;
const int INF=0x3f3f3f3f;

int n, m;
int sx, sy, fx, fy;
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
int dist[N][N], tmp[N][N], to[N][N];
bool vis[N][N];
char c[N][N];

struct Node{
    int x, y;
};
vector<Node> vec;

bool cmp1(Node srca, Node srcb){//左上
    return srca.x+srca.y<srcb.x+srcb.y;
}
bool cmp2(Node srca, Node srcb){//右上
    return srca.x-srca.y<srcb.x-srcb.y;
}
bool cmp3(Node srca, Node srcb){//右下
    return -srca.x-srca.y<-srcb.x-srcb.y;
}
bool cmp4(Node srca, Node srcb){//左下
    return -srca.x+srca.y<-srcb.x+srcb.y;
}
void Init(){
    sort(vec.begin(), vec.end(), cmp1);
    memset(tmp, 0x3f, sizeof(tmp));
    for (auto &idx:vec){
        for (int i=idx.x; i>=1; i--){
            for (int j=idx.y; j>=1; j--){
                if (tmp[i][j]!=INF){
                    break;
                }
                tmp[i][j]=abs(i-idx.x)+abs(j-idx.y);
            }
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            dist[i][j]=min(dist[i][j], tmp[i][j]);
        }
    }
    sort(vec.begin(), vec.end(), cmp2);
    memset(tmp, 0x3f, sizeof(tmp));
    for (auto &idx:vec){
        for (int i=idx.x; i>=1; i--){
            for (int j=idx.y; j<=m; j++){
                if (tmp[i][j]!=INF){
                    break;
                }
                tmp[i][j]=abs(i-idx.x)+abs(j-idx.y);
            }
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            dist[i][j]=min(dist[i][j], tmp[i][j]);
        }
    }
    sort(vec.begin(), vec.end(), cmp3);
    memset(tmp, 0x3f, sizeof(tmp));
    for (auto &idx:vec){
        for (int i=idx.x; i<=n; i++){
            for (int j=idx.y; j<=m; j++){
                if (tmp[i][j]!=INF){
                    break;
                }
                tmp[i][j]=abs(i-idx.x)+abs(j-idx.y);
            }
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            dist[i][j]=min(dist[i][j], tmp[i][j]);
        }
    }
    sort(vec.begin(), vec.end(), cmp4);
    memset(tmp, 0x3f, sizeof(tmp));
    for (auto &idx:vec){
        for (int i=idx.x; i<=n; i++){
            for (int j=idx.y; j>=1; j--){
                if (tmp[i][j]!=INF){
                    break;
                }
                tmp[i][j]=abs(i-idx.x)+abs(j-idx.y);
            }
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            dist[i][j]=min(dist[i][j], tmp[i][j]);
            #ifdef __Debug
                printf("%d", dist[i][j]);
            #endif
        }
        #ifdef __Debug
            printf("\n");
        #endif
    }
}
bool Check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=m;
}
void Search(int x, int y){
    if (x==fx&&y==fy){
        return;
    }
    for (int i=0; i<4; i++){
        int xx=x+dx[i];
        int yy=y+dy[i];
        #ifdef __Debug
            cerr << xx << " " << yy << endl;
        #endif
        if (Check(xx, yy)&&min(to[x][y], dist[xx][yy])>to[xx][yy]){
            to[xx][yy]=min(to[x][y], dist[xx][yy]);
            Search(xx, yy);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    memset(dist, 0x3f, sizeof(dist));
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> c[i][j];
            if (c[i][j]=='V'){
                sx=i, sy=j;
            }
            if (c[i][j]=='J'){
                fx=i, fy=j;
            }
            if (c[i][j]=='+'){
                vec.push_back((Node){i, j});
                dist[i][j]=0;
            }
        }
    }
    Init();
    #ifdef __Debug
        printf("sx=%d sy=%d fx=%d fy=%d\n", sx, sy, fx, fy);
    #endif
    to[sx][sy]=dist[sx][sy];
    Search(sx, sy);
    printf("%d\n", to[fx][fy]);

    return 0;
}