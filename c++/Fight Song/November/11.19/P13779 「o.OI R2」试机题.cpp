#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int N1 = 5e3 + 10;

int n, k;
int dep[N];
vector<int> e[N];

namespace Pts2 {
	int siz[N];
	pair<int, int> pre[N1][N1 >> 1][2][2];
	bitset<(N1 >> 1)> dp[N1][2][2], f[N1][2][2];
	vector<int> ans[2];
	/*
	dp[i][x][y][j] node i has j black node in it`s son tree 
	and the node i is x(0/1)black/white,
	there y(0/1)isn`t/is a son node the same color as it
	*/

	void Dfs(int u, int fa) {
		dp[u][0][0][0] = true;
		dp[u][1][0][1] = true;
		siz[u] = 1;

		for (int v : e[u]) {
			if (v == fa) continue;
			Dfs(v, u);
			for (int i = 0; i <= siz[u]; i++) {
				for (int j = 0; j <= siz[v] && i + j <= (n >> 1); j++) {
					for (int x0 = 0; x0 <= 1; x0++) {
						for (int x1 = 0; x1 <= 1; x1++) {
							if (!dp[u][x0][x1][i]) continue;
							for (int y0 = 0; y0 <= 1; y0++) {
								for (int y1 = 0; y1 <= 1; y1++) {
									if (x0 == y0 && (x1 || y1)) continue;
									// same color of son and itself, the line will >= 3
									if (!dp[v][y0][y1][j]) continue;
									f[v][x0][x1 + (x0 == y0)][i + j] = true;
									pre[v][i + j][x0][x1 + (x0 == y0)] = make_pair(i, x1);
								}
							}
						}
					}
				}
			}
			siz[u] += siz[v];
			siz[u] = min(siz[u], n >> 1);
			
			dp[u][0][0] = f[v][0][0];
			dp[u][0][1] = f[v][0][1];
			dp[u][1][0] = f[v][1][0];
			dp[u][1][1] = f[v][1][1];
		}
	}
	void Work(int u, int fa, int num, int op1, int op2) {
		// cerr << u << " " << fa << " " << num << " " << op1 << " " << op2 << "\n";
		ans[op1].emplace_back(u);
		reverse(e[u].begin(), e[u].end());
		for (int v : e[u]) {
			if (v == fa) continue;
			int x1 = pre[v][num][op1][op2].second;
			int scnt = num - pre[v][num][op1][op2].first; // 当前这个叶子结点的黑点个数
			num = pre[v][num][op1][op2].first;

			bool flag = true; // break tag
			int x0 = op1;

			for (int y0 = 0; y0 <= 1 && flag; y0++) {
				for (int y1 = 0; y1 <= 1 && flag; y1++) {
					if (x0 == y0 && (x1 || y1)) continue;
					if (!dp[v][y0][y1][scnt]) continue;
					if (x1 + (x0 == y0) == op2) {
						Work(v, u, scnt, y0, y1);
						flag = false;
					}
				}
			}
			op1 = x0, op2 = x1;
		}
	}
}

namespace Pts1 {
	void Dfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		for (int v : e[u]) {
			if (v == fa) continue;
			Dfs(v, u);
		}
	}
}
signed main() {
    cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	if (k == 1) {
		printf("xwx\n");
		return 0;
	}
	if (k == 3) {
		using namespace Pts2;
		Dfs(1, 0);
		bool flag = 
			dp[1][0][0][n >> 1] |
			dp[1][0][1][n >> 1] | 
			dp[1][1][0][n >> 1] | 
			dp[1][1][1][n >> 1];

		// printf("Debug:%d\n", dp[2][1][1][1]);
		// cerr << pre[2][1][1][1].first << " " << pre[2][1][1][1].second;
		if (!flag) {
			printf("xwx\n");
			return 0;
		}
		for (int i = 0; i < 4; i++) {
			if (dp[1][i & 1][i >> 1][n >> 1]) {
				Work(1, 0, n >> 1, i & 1, i >> 1);
				break;
			}
		}
		printf("Ciallo~\n");
		for (int i = 0, lim = ans[0].size(); i < lim; i++) {
			printf("%d %d ", ans[0][i], ans[1][i]);
		}
		return 0;
	}
	
	using namespace Pts1;
	Dfs(1, 0);
	if (k == 2) {
		vector<int> q[2];
		for (int i = 1; i <= n; i++) {
			q[dep[i] & 1].emplace_back(i);
		}
		if (q[0].size() != q[1].size()) {
			printf("xwx\n");
			return 0;
		}
		printf("Ciallo~\n");
		for (int i = 0, lim = q[0].size(); i < lim; i++) {
			printf("%d %d ", q[0][i], q[1][i]);
		}
	}
	if (k >= 4) {
		vector<int> q[3];
		for (int i = 1; i <= n; i++) {
			q[dep[i] % 3].emplace_back(i);
		}
		sort(q, q + 3, [](const vector<int> &a, const vector<int> &b) {
			return a.size() < b.size();
		});
		vector<int> ans[2] = {q[0], q[1]};
		for (int p : q[2]) {
			if (ans[0].size() < ans[1].size()) ans[0].emplace_back(p);
			else ans[1].emplace_back(p);
		}
		printf("Ciallo~\n");
		for (int i = 0, lim = ans[0].size(); i < lim; i++) {
			printf("%d %d ", ans[0][i], ans[1][i]);
		}
	}
	return 0;
}