#include <bits/stdc++.h>
using namespace std;
const int N=2e2+10;
int dx[4]={-1, 0, 1, 0};
int dy[4]={0, -1, 0, 1};
int n, m, k, c;
bool vis[N][N], live[N];
char mp[N][N];
struct node{
    int x, y;
};
struct snake{
    int len, id;
    bool operator<(const snake &a){
        if (len==a.len){
            return id<a.id;
        }
        return len>a.len;
    }
}e[N];
deque <node> q[N];
string s[N];
void find(int x, int y){
    vis[x][y]=1;
    q[c].push_back({x, y});
    for (int i=0; i<4; i++){
        int xx=x+dx[i];
        int yy=y+dy[i];
        if (!vis[xx][yy]){
            if (mp[xx][yy]=='#'){
                find(xx, yy);
                return ;
            }
        }
    }
}
void food(int id){
    live[id]=0;
    while (!q[id].empty()){
        int x=q[id].front().x;
        int y=q[id].front().y;
        mp[x][y]='&';
        q[id].pop_front();
    }
}
int change(char c){
    if (c=='W'){
        return 0;
    }
    if (c=='A'){
        return 1;
    }
    if (c=='S'){
        return 2;
    }
    if (c=='D'){
        return 3;
    }
    return 4;
}
bool check(int x, int y){
    return x>=1&&x<=n&&y>=1&&y<=m&&!vis[x][y];
}
void walk(int id, char c){
    int x=q[id].front().x+dx[change(c)];
    int y=q[id].front().y+dy[change(c)];
    if (!check(x, y)){//死因：撞墙
        food(id);
        return ;
    }
    if (mp[x][y]=='#'||mp[x][y]=='@'){//死因：撞人
        food(id);
        return ;
    }
    int head_x=q[id].front().x;
    int head_y=q[id].front().y;
    int tail_x=q[id].back().x;
    int tail_y=q[id].back().y;
    if (mp[x][y]=='&'){//好吃的
        mp[x][y]='@';
        mp[head_x][head_y]='#';
        q[id].push_front({x, y});
        return ;
    }
    if (mp[x][y]=='.'){//无事发生
        mp[x][y]='@';
        mp[head_x][head_y]='#';
        mp[tail_x][tail_y]='.';
        q[id].pop_back();
        q[id].push_front({x, y});
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> k;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> mp[i][j];
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            if (mp[i][j]=='@'){
                live[++c]=1;
                find(i, j);
            }
        }
    }
    for (int i=1; i<=c; i++){
        cin >> s[i];
    }
    memset(vis, 0, sizeof(vis));
    for (int cnt=0; cnt<k; cnt++){
        for (int i=1; i<=c; i++){
            if (live[i]){
                walk(i, s[i][cnt]);
            }
        }
    }
    int sum=0;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            if (mp[i][j]=='&'){
                sum++;
            }
        }
    }
    for (int i=1; i<=c; i++){
        e[i].id=i;
        while (!q[i].empty()){
            e[i].len++;
            q[i].pop_back();
        }
    }
    sort(e+1, e+c+1);
    for (int i=1; i<=c; i++){
        printf("%d %d\n", e[i].len, e[i].id);
    }
    printf("%d\n", sum);

    return 0;
}