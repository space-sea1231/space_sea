#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
const int Mod=1e9+7;
int n, m;
int a[N][N], sum[N][N], tmp[N][N];
void init(){
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			tmp[i][j]=0;
		}
	}
}
void pow_1(){
	init();
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			for (int k=1; k<=n; k++){
				tmp[i][j]=(tmp[i][j]+sum[i][k]*a[k][j])%Mod;
			}
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			sum[i][j]=tmp[i][j];
		}
	}
}
void pow_2(){
	init();
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			for (int k=1; k<=n; k++){
				tmp[i][j]=(tmp[i][j]+a[i][k]*a[k][j])%Mod;
			}
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			a[i][j]=tmp[i][j];
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			cin >> a[i][j];
		}
	}
	for (int i=1; i<=n; i++){
		sum[i][i]=1;
	}
	while (m){
		if (m&1){
			pow_1();
		}
		pow_2();
		m>>=1;
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			printf("%lld ", sum[i][j]);
		}
		printf("\n");
	}

	return 0;
}