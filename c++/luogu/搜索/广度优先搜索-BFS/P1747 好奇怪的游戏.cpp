#include <bits/stdc++.h>
using namespace std;
const int N=30;
int dx[12]={-2, -2, -1, -1, 1, 1, 2, 2, -2, -2, 2, 2};
int dy[12]={-1, 1, -2, 2, -2, 2, -1, 1, -2, 2, -2, 2};
int x_1, y_1, x_2, y_2;
bool vis[N][N];
struct node{
	int x, y, dis;
};
bool check(int x, int y){
	return x>=1&&x<=20&&y>=1&&y<=20;
}
void init(){
	for (int i=1; i<=20; i++){
		for (int j=1; j<=20; j++){
			vis[i][j]=0;
		}
	}
}
void serch(int sx, int sy){
	init();
	queue<node> q;
	q.push({sx, sy, 0});
	int x, y, w, xx, yy;
	while (!q.empty()){
		x=q.front().x;
		y=q.front().y;
		w=q.front().dis;
		q.pop();
		if (vis[x][y]) continue;
		vis[x][y]=1;
		if (x==1&&y==1){
			printf("%d\n", w);
			return ;
		}
		for (int i=0; i<12; i++){
			xx=x+dx[i], yy=y+dy[i];
			if (check(xx, yy)){
				q.push({xx, yy, w+1});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> x_1 >> y_1 >> x_2 >> y_2;
	serch(x_1, y_1), serch(x_2, y_2);

	return 0;
}