#include <bits/stdc++.h>
using namespace std;
const int N=4e2+10;
int dis[N][N];
int dx[8]={-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8]={-1, 1, -2, 2, -2, 2, -1, 1};
int n, m, sx, sy;
struct node{
	int x, y, dis;
};
void init(){
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			dis[i][j]=-1;
		}
	}
}
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
void serch(){
	queue<node> q;
	q.push({sx, sy, 0});
	dis[sx][sy]=0;
	int x, y, w, xx, yy;
	while (!q.empty()){
		x=q.front().x;
		y=q.front().y;
		w=q.front().dis;
		q.pop();
		for (int i=0; i<8; i++){
			xx=x+dx[i], yy=y+dy[i];
			if (check(xx, yy)&&dis[xx][yy]==-1){
				dis[xx][yy]=w+1;
				q.push({xx, yy, w+1});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> sx >> sy;
	init(), serch();
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			printf("%d ", dis[i][j]);
		}
		printf("\n");
	}
	return 0;
}