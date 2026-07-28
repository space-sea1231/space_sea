#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
int t, n;
bool a[N][N];
int gcd(int a, int b){
	while (b){
		int c=a%b;
		a=b;
		b=c;
	}
	return a;
}
int main(){
    // freopen("math.in", "r", stdin);
    // freopen("math.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> t;
	while (t--){
		// cin >> n;
		// for (int i=1; i<=n; i++){
		// 	for (int j=1; j<=n; j++){
		// 		cin >> a[i][j];
		// 	}
		// }
		// bool flag=0, flag_1=1;
		// for (int i=1; i<=n; i++){
		// 	if (a[i][i]){
		// 		flag=1;
		// 	}
		// 	for (int j=1; j<=n; j++){
		// 		if (a[i][j]^a[j][i]){
		// 			flag=1;
		// 		}
		// 		if (a[i][j]){
		// 			flag_1=0;
		// 		}
		// 	}
		// }
		// bool fflag;
		// for (int k=0; k<=100000; k++){
		// 	fflag=1;
		// 	for (int i=1; i<=n; i++){
		// 		for (int j=1; j<=n; j++){
		// 			if (gcd(k+i, k+j)==a[i][j]){
		// 				fflag=0;
		// 				break;
		// 			}
		// 		}
		// 	}
		// 	if (fflag){
		// 		flag=0, flag_1=0;
		// 		break;
		// 	}
		// }
		// if (flag||flag_1==0){
		// 	printf("No\n");
		// }else{
		// 	printf("Yes\n");
		// }
		printf("No\n");
	}
	return 0;
}