#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
int n, m, cnt, a[N][N];
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
bool vis[N][N];
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
void serch(int x, int y){
	int xx, yy;
	vis[x][y]=1;
	for (int i=0; i<4; i++){
		xx=x+dx[i], yy=y+dy[i];
		if (check(xx, yy)&&!vis[xx][yy]&&a[xx][yy]>0){
			serch(xx, yy);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	char c;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			cin >> c;
			a[i][j]=c-'0';
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			if (a[i][j]>0&&!vis[i][j]){
				serch(i, j), cnt++;
			}
		}
	}
	printf("%d", cnt);
	
	return 0;
}