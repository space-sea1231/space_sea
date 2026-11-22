#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int K = 1e2 + 10;

int n, k;
// int f[N][K], tmp[K];
vector<int> e[N];

// void Dfs(int u, int fa) {
// 	f[u][1] = 1;
// 	for (int v : e[u]) {
// 		if (v == fa) continue;
// 		Dfs(v, u);
// 	}
// 	for (int v : e[u]) {
// 		if (v == fa) continue;
// 		for (int i = 0; i < K; i++) {
// 			// 合并
// 			if (i > 0 && f[v][i] + f[u][i - 1] < k) f[u][i - 1] = 1;
// 			if (i < K - 1 && f[v][i] + f[u][i + 1] < k) f[u][i + 1] = min(f[u][i + 1], f[v][i] + 1);
// 		}
// 		if (v == 2) cerr << f[u][0] << " " << f[u][1] << " " << f[u][2] << "\n";
// 		for (int i = 0; i < K; i++) {
// 			tmp[i] = f[u][i];
// 			f[u][i] = INF;
// 		}
// 	}
// }

bool color[N];
vector<int> q[2];

void Dfs(int u, int fa) {
	color[u] = color[fa] ^ 1;
	q[color[u]].emplace_back(u);
	for (int v : e[u]) {
		if (v == fa) continue;
		Dfs(v, u);
	}
}
signed main() {
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	// memset(f, 0x3f, sizeof(f));
	cin >> n >> k;
	if (k == 1) {
		printf("Neil_Qian AKIOI\n");
		return 0;
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	Dfs(1, 0);
	if (q[0].size() != q[1].size()) {
		printf("Neil_Qian AKIOI\n");
		return 0;
	}
	printf("Cerydra~\n");
	for (int i = 0, lim = q[0].size(); i < lim; i++) {
		printf("%d %d ", q[0][i], q[1][i]);
	}
	printf("\n");
	// Dfs(1, 0);
	// cerr << f[1][0];
	return 0;
}