#include<bits/stdc++.h>
using namespace std;
const int N = 2000 + 10;
int a[N], dp[N];
int n;
int work() {
	memset(dp, 0, sizeof dp);
	for (int i = 1; i <= n; ++i) {
		dp[i] = 1;
		for (int j = 1; j < i; ++j) {
			if (a[i] > a[j]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
	int maxx = -1;
	for (int i = 1; i <= n; ++i) maxx = max(maxx, dp[i]);
	return maxx;
}
void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	int ans1 = work();
	for (int i = n; i > 1; --i) {
		if (a[i] < a[i - 1]) {
			swap(a[i], a[i - 1]);
		}
	}
	int ans2 = work();
	cout << min(ans1, ans2) << '\n';
}
int main() {
//	freopen("wei.in","r",stdin);
//	freopen("wei.out","w",stdout);
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

