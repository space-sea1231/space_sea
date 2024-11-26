#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, sum, ans=-(1<<30);
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<=n; i++){
		int a;
		cin >> a;
		sum=max(sum+a, a);
		ans=max(ans, sum);
	}
	printf("%d", ans);

	return 0;
}