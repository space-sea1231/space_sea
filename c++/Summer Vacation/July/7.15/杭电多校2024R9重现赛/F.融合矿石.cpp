#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e3 + 10;

int t;
int n, m;
int v[20], u[N];
int a[N], b[N];
int g[N], f[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		memset(g, 0, sizeof(g));
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= 10; i++) cin >> v[i];
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
		for (int i = 1; i <= n; i++) {
			for (int j = a[i]; j <= m; j++) {
				g[j] = max(g[j], g[j - a[i]] + b[i]);
			}
		}
		// for (int i = 1; i <= m; i++) printf("g[%d]=%d\n", i, g[i]);
		for (int i = 1; i <= m; i++) u[i] = v[g[i] * 10 / i + (g[i] * 10 % i != 0)];
		// for (int i = 1; i <= m; i++) printf("u[%d]=%d g=%d i=%d    %d\n", i, u[i], g[i], i, g[i] * 10 / i);
		for (int i = 0; i <= m; i++) {
			for (int j = 0; j + i <= m; j++) {
				f[i + j] = max(f[i + j], f[i] + j * u[j]);
			}
		}
		int ans = 0;
		for (int i = 1; i <= m; i++) ans = max(ans, f[i]);
		printf("%d\n", ans);
	}
	return 0;
}