#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=30;
int n, m, horse_x, horse_y;
int dp[N][N];
int dx[8]={-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8]={-1, 1, -2, 2, -2, 2, -1, 1};
bool vis[N][N];
bool check(int x, int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
void init(){
	vis[horse_x][horse_y]=1;
	for (int i=0; i<8; i++){
		int xx=horse_x+dx[i];
		int yy=horse_y+dy[i];
		if (check(xx, yy)){
			vis[xx][yy]=1;
		}
	}
	dp[1][0]=1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m >> horse_x >> horse_y;
	n++, m++, horse_x++, horse_y++;
	init();
	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++){
			if (!vis[i][j]){
				dp[i][j]=dp[i-1][j]+dp[i][j-1];
			}
		}
	}
	printf("%lld", dp[n][m]);

	return 0;
}