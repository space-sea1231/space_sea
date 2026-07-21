#include <bits/stdc++.h>
using namespace std;
#define fre(x) freopen(#x".in", "r", stdin); freopen(#x".out", "wb", stdout)
#define ck(x)  { cout << "check " << x << endl;}
#define int long long
#define double long double
#define inf 0x3fffffffffffffff

void solve() {
	int n, k, m;
	cin >> n >> k >> m;
	int mod = 1, cnt = 0;
	while (mod <= 2e9) {
		mod *= k;
		cnt++;
	}
	vector<int> u(n);
	vector<int> ori;
	for (auto &x : u) {
		cin >> x;
		ori.push_back(x);
		x = (x % mod + mod) % mod;
	}
	vector<array<int, 2>> a(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i][0];
		a[i][0]--;
	}
	for (int i = 0; i < m; i++) {
		cin >> a[i][1];
		a[i][1]--;
	}
	auto res = u, sum = u;
	for (int i = 1; i < cnt; i++) {
		vector<int> t(n);
		for (auto [x, y] : a) {
			t[x] = (t[x] + res[y]) % mod;
		}
		for (int j = 0; j < n; j++) {
			res[j] = (-k * t[j] % mod + mod) % mod;
			sum[j] = (sum[j] + res[j]) % mod;
		}
	}
	for (int i = 0; i < n; i++) {
		if (sum[i] > 1e9) {
			sum[i] -= mod;
		}
		if (sum[i] > 1e9 || sum[i] < -1e9) {
			cout << "No Solution\n";
			return ;
		}
	}
	vector<int> t(n);
	for (auto [x, y] : a) {
		t[x] += sum[y];
	}
	for (int i = 0; i < n; i++) {
		if ((t[i] * k + sum[i]) != ori[i]) {
			cout << "No Solution\n";
			return ;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << sum[i] << " \n"[i == n - 1];
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
