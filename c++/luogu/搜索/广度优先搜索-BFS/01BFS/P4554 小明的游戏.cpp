#include <bits/stdc++.h>
using namespace std;
const int N=5e2+10;
int n, m, sx, sy, fx, fy;
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
char c[N][N];
bool vis[N][N];
void init(){
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			c[i][j]=' ', vis[i][j]=0;
		}
	}
}
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
struct node{
	int x, y, dis;
};
void bfs_01(){
	deque<node> q;
	q.push_front({sx, sy, 0});
	int x, y, dis, xx, yy;
	while (!q.empty()){
		x=q.front().x, y=q.front().y, dis=q.front().dis;
		q.pop_front();
		if (x==fx&&y==fy){
			printf("%d\n", dis);
			return ;
		}
		if (vis[x][y]){
			continue;
		}
		vis[x][y]=1;
		for (int i=0; i<4; i++){
			xx=x+dx[i];
			yy=y+dy[i];
			if (!check(xx, yy)){
				continue;
			}
			if (c[xx][yy]==c[x][y]){
				q.push_front({xx, yy, dis});
			}
			if (c[xx][yy]!=c[x][y]){
				q.push_back({xx, yy, dis+1});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (1){
		init();
		cin >> n >> m;
		if (!n&&!m){
			return 0;
		}
		for (int i=1; i<=n; i++){
			for (int j=1; j<=m; j++){
				cin >> c[i][j];
			}
		}
		cin >> sx >> sy >> fx >> fy;
		sx++, sy++, fx++, fy++;
		bfs_01();
	}
	return 0;
}