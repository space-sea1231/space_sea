#include <bits/stdc++.h>
using namespace std;
long long ans;
int t, n, a[400005], f[400005];
void calc() {
	long long res = 0;
	for(int i = 1; i <= n; i++)
		res += (f[i] = (a[i] > a[i - 1] ? f[i - 1] : 0) + 1);
	ans = max(ans, res);
	return;
}
int main() {
	freopen("wei.in", "r", stdin);
	freopen("wei.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--) {
		cin >> n, ans = 0;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		calc();
		for(int i = 1; i < n; i++)
			for(int j = i + 1; j <= n; j++)
				swap(a[i], a[j]), calc(), swap(a[i], a[j]);
		cout << ans % (1ll << 32) << '\n';
	}
	return 0;
}