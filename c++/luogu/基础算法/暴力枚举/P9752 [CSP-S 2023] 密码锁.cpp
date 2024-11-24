#include <bits/stdc++.h>
using namespace std;
const int N=10;
int a[N][N], sum[N], now[N], n, cnt;
void check(){
	int tot;
	for (int i=1; i<=n; i++){
		tot=0;
		for (int j=1; j<=5; j++){
			if (a[i][j]!=sum[j]){
				now[++tot]=j;
			}
		}
		if (tot==1){
			continue;
		}
		if (tot==2&&abs(now[1]-now[2])==1){
			bool flag=0;
			int x=sum[now[1]], y=sum[now[2]];
			for (int j=1; j<=10; j++){
				x++, y++;
				if (x>9){
					x=0;
				}
				if (y>9){
					y=0;
				}
				if (x==a[i][now[1]]&&y==a[i][now[2]]){
					flag=1;
					break;
				}
			}
			if (!flag){
				return ;
			}
			continue;
		}
		return ;
	}
	cnt++;
}
void serch(int dep){
	if (dep==6){
		check();
		return ;
	}
	for (int i=0; i<=9; i++){
		sum[dep]=i;
		serch(dep+1);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=5; j++){
			cin >> a[i][j];
		}
	}
	serch(1);
	printf("%d", cnt);

	return 0;
}