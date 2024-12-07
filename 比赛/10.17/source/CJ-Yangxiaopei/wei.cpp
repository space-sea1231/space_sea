#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, a[400005];
signed main(){
	freopen("wei.in", "r", stdin);
	freopen("wei.out", "w", stdout);
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i]; 
		}
		int sum = 0;
		for(int i = 1; i <= n; i++){
			for(int j = i; j <= n; j++){
				if(a[j] < a[j - 1] && j != i){
					break;
				}
				sum++;
			}
		}
		for(int k = 1; k < n; k++){
			swap(a[k], a[k + 1]);
			int cnt = 0;
			for(int i = 1; i <= n; i++){
				for(int j = i; j <= n; j++){
					if(a[j] < a[j - 1] && j != i){
						break;
					}
					cnt++;
				}
			}
			sum = max(sum, cnt);
			swap(a[k], a[k + 1]);
		}
		cout << sum << "\n";
	}
	return 0;
}

