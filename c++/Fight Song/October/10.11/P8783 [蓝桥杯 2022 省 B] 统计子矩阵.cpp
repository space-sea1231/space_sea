#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e2 + 10;

int n, m, k;
int a[N][N];
int sum[N][N];

int Calc(int sx, int sy, int fx, int fy) {
	return sum[fx][fy] - sum[sx - 1][fy] - sum[fx][sy - 1] + sum[sx - 1][sy - 1];
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
		}
	}
	ll ans = 0;
	for (int u = 1; u <= n; u++) {
		for (int d = u; d <= n; d++) {
			int l = 1, r = 0;
			while (l <= m && r < m) {
				r++;
				while (Calc(u, l, d, r) > k) l++;
				ans += r - l + 1;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}