#include <bits/stdc++.h>
using namespace std;
int t;
int n, m, k, p;
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> t;
	while (t--){
		cin >> n >> m >> k >> p;
		int tmp=p/n;
		if (m-tmp>=k){
			printf("Together\n");
		}else if (k<=n*m-p&&k<=m){
			printf("Chance\n");
		}else{
			printf("Divide\n");
		}
	}

	return 0;
}