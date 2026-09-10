#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
// #define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const int M = 2e4 + 10;

int s, n, m;
int f[M], cnt[N][M];
vector<int> a[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> s >> n >> m;
	for (int i = 1; i <= n; i++) a[i].resize(s);
	for (int i = 0; i < s; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[j][i];
			a[j][i] = (a[j][i] << 1) + 1;
		}
	}
	for (int i = 1; i <= n; i++) sort(a[i].begin(), a[i].end());
	for (int i = 1; i <= n; i++) {
		int p = 0;
		for (int j = 1; j <= m; j++) {
			cnt[i][j] = cnt[i][j - 1];
			while (p < s && a[i][p] == j) {
				p++;
				cnt[i][j] += i;
			}
		}
	}
	// #ifdef __Debug
	// for (int i = 1; i <= m; i++) {
	// 	for (int j = 1; j <= n; j++) {
	// 		printf("%d ", cnt[j][i]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// #endif
	for (int i = 1; i <= n; i++) {
		for (int j = m; j; j--) {// f[k] + cnt[i][j - k];
			for (int k = 0; k < s; k++) {
				if (j >= a[i][k]) f[j] = max(f[j], f[j - a[i][k]] + cnt[i][a[i][k]]);
			}
		}
	}
	printf("%d\n", f[m]);
	return 0;
}
