#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int t, n, m, maxn, sum;
int a[N];
signed main(){
	// ios::sync_with_stdio(0);
	// cin.tie();
	cin >> t;
	while (t--){
		maxn=sum=0;
		cin >> n >> m;
		for (int i=1; i<=n; i++){
			cin >> a[i];
			maxn=max(maxn, a[i]);
			sum+=maxn;
		}
		if (m==0){
			cout<<sum<<'\n';
			continue;
		}
		if(n==2) {
			if (m&1) cout << a[2] + max(a[1], a[2]) << '\n';
			else cout<<a[1] + max(a[1], a[2])<<'\n';
		}
		else{
			printf("%lld\n", maxn*n);
		}
	}

	return 0;
}