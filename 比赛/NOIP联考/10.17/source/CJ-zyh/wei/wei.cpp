#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2005;

int T;

int n;

int p[kMaxN];

int ans;

void solve() {
	int res = 0;
//	for (int i = 1; i <= n; ++i) cout << p[i] << ' ';
//	cout << '\n';
	for (int i = 1; i <= n; ++i) {
		int j = i;
		while (j <= n && p[j] >= p[max(i, j - 1)]) ++j;
		--j;
		int len = j - i + 1;
		//cout << "len = " << len << '\n';
		res += len * (len + 1) / 2;
		i = j;
	}
	//cout << "res = " << res << '\n';
	ans = max(ans, res);
}

int main() {
	freopen("wei.in", "r", stdin);
	freopen("wei.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			cin >> p[i];
		}
		ans = 0;
		solve();
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				swap(p[i], p[j]);
				solve();
				swap(p[i], p[j]);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
