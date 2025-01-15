#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, k, sum;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> t;
	while (t--){
		int cnt=0;
		cin >> k;
		if (k==0){
			printf("NO!\n");
			continue;
		}
		sum=(k<<1)+1;
		while (sum%2){
			sum=sum*((sum>>1)+1);
			cnt++;
		}
		printf("%lld\n", cnt);
	}

	return 0;
}