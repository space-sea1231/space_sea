#include <bits/stdc++.h>
using namespace std;
const int N=20;
int n;
char c[N][N], f[N][N];
char tmp[N][N], tmp_tmp[N][N];
bool check(char a[][N], char b[][N]){
	bool flag=1;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			flag=flag&(a[i][j]==b[i][j]);
		}
	}
	return flag;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			cin >> c[i][j];
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			cin >> f[i][j];
		}
	}
/*----------------------情况1-----------------------*/
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp[j][n-i+1]=c[i][j];
		}
	}
	// printf("-------------Debug--------------\n");
	// for (int i=1; i<=n; i++){
	// 	for (int j=1; j<=n; j++){
	// 		printf("%c", tmp[i][j]);
	// 	}
	// 	printf("\n");
	// }
	if (check(tmp, f)){
		printf("1");
		return 0;
	}
/*----------------------情况2-----------------------*/
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp[n-i+1][n-j+1]=c[i][j];
		}
	}
	if (check(tmp, f)){
		printf("2");
		return 0;
	}
/*----------------------情况3-----------------------*/
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp[n-j+1][i]=c[i][j];
		}
	}
	if (check(tmp, f)){
		printf("3");
		return 0;
	}
/*----------------------情况4-----------------------*/
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp[i][n-j+1]=c[i][j];
		}
	}
	if (check(tmp, f)){
		printf("4");
		return 0;
	}
/*----------------------情况5.1-----------------------*/
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp_tmp[j][n-i+1]=tmp[i][j];
		}
	}
	if (check(tmp_tmp, f)){
		printf("5");
		return 0;
	}
/*----------------------情况5.2-----------------------*/
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp_tmp[n-i+1][n-j+1]=tmp[i][j];
		}
	}
	if (check(tmp_tmp, f)){
		printf("5");
		return 0;
	}
/*----------------------情况5.3-----------------------*/
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp_tmp[n-j+1][i]=tmp[i][j];
		}
	}
	if (check(tmp_tmp, f)){
		printf("5");
		return 0;
	}
/*----------------------情况6-----------------------*/
	if (check(c, f)){
		printf("6");
		return 0;
	}
/*----------------------情况7-----------------------*/
	printf("7");

	return 0;
}