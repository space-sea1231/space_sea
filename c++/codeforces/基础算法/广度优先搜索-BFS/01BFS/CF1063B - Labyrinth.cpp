#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n, m, sx, sy, l_move, r_move, cnt;
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
char c[N][N];
bool vis[N][N];
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m&&c[x][y]=='.';
}
struct node{
	int x, y, l_move, r_move;
};
void bfs_01(){
	deque<node> q;
	q.push_front({sx, sy, l_move, r_move});
	int x, y, l, r, xx, yy;
	while (!q.empty()){
		x=q.front().x, y=q.front().y;
		l=q.front().l_move, r=q.front().r_move;
		q.pop_front();
		if (vis[x][y]){
			continue;
		}
		vis[x][y]=1;
		cnt++;
		for (int i=0; i<4; i++){
			xx=x+dx[i];
			yy=y+dy[i];
			if (!check(xx, yy)){
				// printf("%d %d\n", xx, yy);
				continue;
			}
			if (i==0||i==3){
				q.push_front({xx, yy, l, r});
			}
			if (i==1&&l){
				q.push_back({xx, yy, l-1, r});
			}
			if (i==2&&r){
				q.push_back({xx, yy, l, r-1});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> sx >> sy >> l_move >> r_move;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			cin >> c[i][j];
		}
	}
	bfs_01();
	printf("%d", cnt);

	return 0;
}