#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int t;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		int n, m, a, b;
		cin >> n >> m >> a >> b;
		int res1 = 0, res2 = 0;
		if (b != m && b != 1) res1 = n - 2;
		if (a != n && a != 1) res2 = m - 2;
		int ans = max(res1, res2);
		ans += n * 2 + m * 2 - 4;
		if (m == 1) ans = n;
		if (n == 1) ans = m;
		printf("%d\n", ans);
	}
	return 0;
}