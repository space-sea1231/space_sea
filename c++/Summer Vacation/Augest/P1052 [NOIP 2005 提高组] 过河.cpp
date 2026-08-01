#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = 2e9;
const int N = 2e4 + 10;
const int M = 1e2 + 10;

int l, s, t, m;
int ans, top = 1;
int a[N], f[N];
bool vis[N];
struct Node {
	vector<int> q;
}; Node node[M];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> l >> s >> t >> m;
	for (int i = 1; i <= m; i++) cin >> a[i];
	if (s == t) {
		int ans = 0;
		for (int i = 1; i <= m; i++) ans += (a[i] % s == 0);
		printf("%d\n", ans);
		return 0;
	}
	sort(a + 1, a + m + 1); a[m + 1] = INF;
	// for (int i = 1; i <= m; i++) printf("%d ", a[i]);
	// printf("\n");
	int front = (a[1] > 110 ? a[1] - 11 : 0);
 	for (int i = 1; i <= m; i++) {
		node[top].q.emplace_back(a[i] - front);
		if (a[i + 1] - a[i] > 110) {
			if (!node[top].q.empty()) top++;
			front = a[i + 1] - 11;
		}
	}
	for (int i = 1; i < top; i++) {
		int n = node[i].q.back() + 11;
		// cerr<<n << endl;
		for (int j = 1; j <= n; j++) f[j] = INF, vis[j] = false;
		if (i != 1 || a[1] > 110) for (int j = 1; j <= 10; j++) f[j] = 0;
		for (auto j:node[i].q) vis[j] = true;
		for (int j = 1; j <= n; j++) {
			for (int k = j - s; k >= 0 && k >= j - t; k--) {
				f[j] = min(f[j], f[k] + (int)vis[j]);
				// cerr<<"f[" << j << "]=" << f[j] << endl;
			}
		}
		// printf("i=%d f[%d]=%d %d\n", i, n, f[n], f[11]);
		int kkk = INF;
		for (int i = n - 10; i <= n; i++) kkk = min(kkk, f[i]);
		ans += kkk;
		// return 0;
	}
	printf("%d\n", ans);
	return 0;
}