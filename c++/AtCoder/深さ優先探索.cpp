#include <bits/stdc++.h>
using namespace std;
const int N=5e2+10;
int n, m, sx, sy, fx, fy;
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
char c[N][N];
bool vis[N][N];
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
void serch(int x, int y){
	int xx, yy;
	vis[x][y]=1;
	for (int i=0; i<4; i++){
		xx=x+dx[i], yy=y+dy[i];
		if (check(xx, yy)&&!vis[xx][yy]&&c[xx][yy]!='#'){
			serch(xx, yy);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			cin >> c[i][j];
			if (c[i][j]=='s') sx=i, sy=j;
			if (c[i][j]=='g') fx=i, fy=j;
		}
	}
	serch(sx, sy);
	if (vis[fx][fy]) printf("Yes");
	else printf("No");
	
	return 0;
}