#include <bits/stdc++.h>
using namespace std;
const int N=10;
int n, m, k, cnt;
int sx, sy, fx, fy;
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
int vis[N][N];
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
void serch(int x, int y){
	if (x==fx&&y==fy){
		cnt++;
		return ;
	}
	vis[x][y]++;
	int xx, yy;
	for (int i=0; i<4; i++){
		xx=x+dx[i], yy=y+dy[i];
		if (check(xx, yy)&&!vis[xx][yy]){
			serch(xx, yy);
		}
	}
	vis[x][y]--;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	cin >> sx >> sy >> fx >> fy;
	int x, y;
	for (int i=1; i<=k; i++){
		cin >> x >> y;
		vis[x][y]=1;
	}
	serch(sx, sy);
	printf("%d", cnt);

	return 0;
}