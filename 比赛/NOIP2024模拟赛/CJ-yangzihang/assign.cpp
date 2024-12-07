#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M=1e6+10;
const int Mod=1e9+7;
int t, n, m, u;
int mi(int a, int b){
    int sum=1;
    while (b){
        if (b&1){
            sum=(sum*a)%Mod;
        }
        a=(a*a)%Mod;
        b>>=1;
    }
    return sum;
}
int C(int n, int m){
	int nn=1;
	for (int i=1; i<=n; i++){
		nn=(nn*i)%Mod;
	}
	int mm=1;
	for (int i=m; i>=m-n+1; i--){
		mm=(mm*i)%Mod;
	}
	return mm/nn;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
	cin >> t;
	while (t--){
		cin >> n >> m >> u;
		for (int i=1; i<=m; i++){
			cin >> c[i] >> d[i];
		}
		int sum=0
		for (int i=1; i<=n; i++){
			sum=(sum+C(1, n)*mi(u, 2*(n-i)))%Mod;
		}
		printf("%lld\n", sum);
	}
	
    return 0;
}