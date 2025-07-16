#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,m;
int a[N][N];
int dp[N][N];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
struct id{
    int x,y;
}cnt[5];
queue<id> q;
char c[N][N];
bool cmp(id x,id y){
    return a[x.x][x.y]>a[y.x][y.y];
}
queue<id>qu[N*2];
void bfs(int curx,int cury){
    qu[a[curx][cury]].push({curx,cury});
    dp[curx][cury]=a[curx][cury];
    for(int i=a[curx][cury];i>=0;i--){
        while(!qu[i].empty()){
            id now=qu[i].front();
            qu[i].pop();
            // cerr<<now.x<<" "<<now.y<<"\n";
            for(int j=0;j<4;j++){
                int nx=now.x+dx[j];
                int ny=now.y+dy[j];
                if(nx<=0||ny<=0||nx>n||ny>m)continue;
                if(dp[nx][ny]!=-1&&dp[nx][ny]>=min(i,a[nx][ny]))continue;
                // cerr<<nx<<" "<<ny<<"\n";
                dp[nx][ny]=min(i,a[nx][ny]);
                qu[min(i,a[nx][ny])].push({nx,ny});
            }
        }
    }
    return ;
}
int main(){
    cin >> n >> m;
    memset(a,-1,sizeof a);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> c[i][j];
            if(c[i][j]=='+'){
                q.push({i,j});
                a[i][j]=0;
            }
        }
    }
    while(!q.empty()){
        id cur=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];
            if(a[nx][ny]!=-1)continue;
            a[nx][ny]=a[cur.x][cur.y]+1;
            q.push({nx,ny});
        }
    }
    memset(dp,-1,sizeof dp);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            // cout << a[i][j]<<" ";
            if(c[i][j]=='V'){
                bfs(i,j);
                // cerr<<1;
            }
        }
        // cout << "\n";
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            // cout << dp[i][j] << " ";
            if(c[i][j]=='J'){
                cout << dp[i][j];
                return 0;
            }
        }
        // cout << "\n";
    }
    return 0;
}