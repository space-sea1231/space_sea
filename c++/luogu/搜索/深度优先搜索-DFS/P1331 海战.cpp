#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n, m, cnt;
int dx[4]={-1, 0, 0, 1};
int dy[4]={0, -1, 1, 0};
int vis[N][N];
char c[N][N];
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
void serch(int x, int y){
	int xx, yy;
	vis[x][y]=cnt;
	for (int i=0; i<4; i++){
		xx=x+dx[i], yy=y+dy[i];
		if (check(xx, yy)&&!vis[xx][yy]&&c[xx][yy]=='#'){
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
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			if (c[i][j]=='#'&&!vis[i][j]){
				cnt++, serch(i, j);
			}
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			if (c[i][j]=='#'){
				continue;
			}
			if (c[i-1][j]=='#'&&c[i][j+1]=='#'&&c[i-1][j+1]=='#'){
				cout << "Bad placement.";
				return 0;
			}
			if (c[i-1][j]=='#'&&c[i][j-1]=='#'&&c[i-1][j-1]=='#'){
				cout << "Bad placement.";
				return 0;
			}
			if (c[i+1][j]=='#'&&c[i][j+1]=='#'&&c[i+1][j+1]=='#'){
				cout << "Bad placement.";
				return 0;
			}
			if (c[i+1][j]=='#'&&c[i][j-1]=='#'&&c[i-1][j-1]=='#'){
				cout << "Bad placement.";
				return 0;
			}
		}
    }
	printf("There are %d ships.", cnt);
	
	return 0;
}