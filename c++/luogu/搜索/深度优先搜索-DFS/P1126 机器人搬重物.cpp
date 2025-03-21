#include <bits/stdc++.h>
using namespace std;
const int N=60;
const int INF=1<<30;
int dx[4]={0, 1, 0, -1};
int dy[4]={1, 0, -1, 0};
int n, m, d, ans=INF;
int sx, sy, fx, fy;
int dis[N][N][4];
bool a[N][N];
void init(){
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			for (int d=0; d<4; d++){
				dis[i][j][d]=INF;
			}
		}
	}
}
bool check(int x, int y){
	return x>=1&&x<n&&y>=1&&y<m&&!a[x][y];
}
void serch(int x, int y, int d){
	if (dis[x][y][d]>=ans){
		return ;
	}
	if (x==fx&&y==fy){
		ans=min(ans, dis[x][y][d]);
		return ;
	}
	if (dis[x][y][d]+1<dis[x][y][(d+3)%4]){//左转
		dis[x][y][(d+3)%4]=dis[x][y][d]+1;
		serch(x, y, (d+3)%4);
	}
	if (dis[x][y][d]+1<dis[x][y][(d+1)%4]){//右转
		dis[x][y][(d+1)%4]=dis[x][y][d]+1;
		serch(x, y, (d+1)%4);
	}
	for (int i=1; i<=3; i++){//走路
		int xx=x+i*dx[d];
		int yy=y+i*dy[d];
		if (check(xx, yy)){
			if (dis[x][y][d]+1<dis[xx][yy][d]){
				dis[xx][yy][d]=dis[x][y][d]+1;
				serch(xx, yy, d);
			}
		}else{
			return ;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	init();
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			bool tmp;
			cin >> tmp;
			if (tmp){
				a[i][j]=1;
				a[i-1][j]=1;
				a[i][j-1]=1;
				a[i-1][j-1]=1;
			}
		}
	}
	char c;
	cin >> sx >> sy >> fx >> fy >> c;
	if (c=='E'){
		d=0;
	}
	if (c=='S'){
		d=1;
	}
	if (c=='W'){
		d=2;
	}
	if (c=='N'){
		d=3;
	}
	// printf("Debug: %d\n", d);
	dis[sx][sy][d]=0;
	serch(sx, sy, d);
	if (ans==INF){
		printf("-1");
	}else{
		printf("%d", ans);
	}
	// for (int i=1; i<=n; i++){
	// 	for (int j=1; j<=m; j++){
	// 		printf("%d ", a[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// for (int k=0; k<4; k++){
	// 	for (int i=1; i<=n; i++){
	// 		for (int j=1; j<=m; j++){
	// 			if (dis[i][j][k]==INF){
	// 				printf("# ");
	// 			}else{
	// 				printf("%d ", dis[i][j][k]);
	// 			}
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
	// }
	return 0;
}