#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int t, n, m;
int p[N], p_pos[N];
int siz[N], dfnc[N], dfnr[N];
int idxl, idxr;
int root, minn = INF;
vector<int> e[N];
// vector<int> euler;

// struct SegmentTree {
// 	struct Node {
// 		int val, minn;
// 	};

// 	Node node[N << 2];

// 	void Up(int x) {
// 		node[x].minn = min(node[x << 1].minn, node[x << 1 | 1].minn);
// 	}
// 	void Build(int x, int l, int r) {
// 		if (l == r) {
// 			node[x].val = node[x].minn = p[l];
// 			return;
// 		}
// 		int mid = (l + r) >> 1;
// 		Build(x << 1, l, mid);
// 		Build(x << 1 | 1, mid + 1, r);
// 		Up(x);
// 	}

// };
// SegmentTree tree;
struct SegmentTree_Val {
	struct Node {
		int val;
		int dfnc_max;
		int dfnr_min;
	};

	Node node[N << 2];

	void Up(int x) {
		node[x].dfnc_max = max(node[x << 1].dfnc_max, node[x << 1 | 1].dfnc_max);
		node[x].dfnr_min = min(node[x << 1].dfnr_min, node[x << 1 | 1].dfnr_min);
	}
	void Build(int x, int l, int r) {
		if (l == r) {
			node[x].val = p_pos[l];
			node[x].dfnc_max = dfnc[p_pos[l]];
			node[x].dfnr_min = dfnr[p_pos[l]];
			return;
		}
		int mid = (l + r) >> 1;
		Build(x << 1, l, mid);
		Build(x << 1 | 1, mid + 1, r);
		Up(x);
	}
	int Query_dfnr(int x, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			
		}
	}
};
SegmentTree_Val tree;

void Dfs_Root(int u, int fa) {
	siz[u] = 1;
	int siz_max = 0;
	for (auto v:e[u]) {
		if (v == fa) continue;
		Dfs_Root(v, u);
		siz[u] += siz[v];
		siz_max = max(siz_max, siz[v]);
	}
	siz_max = max(siz_max, n - siz[u]);
	if (minn > siz_max) {
		minn = siz_max;
		root = u;
	}
}
void Dfs(int u, int fa) {
	// euler.emplace_back(u)
	dfnc[u] = ++idxl;
	for (auto v:e[u]) {
		if (v == fa) continue;
		Dfs(v, u);
	}
	dfnr[u] = ++idxr;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			cin >> p[i];
			p_pos[p[i]] = i;
		}
		// tree.Build(1, 1, n);
		for (int i = 1; i < n; i++) {
			int u, v;
			cin >> u >> v;
			e[u].emplace_back(v);
			e[v].emplace_back(u);
		}
		Dfs_Root(1, 0);
		Dfs(root, 0);
		for (int i = 1; i <= m; i++) {
			int opt, x, y;
			cin >> opt >> x >> y;
			if (opt == 1) {
				
			}
			if (opt == 2) {
				int u = Query_dfnr(1, 1, n, x, y);
			}
		}
	}
	return 0;
}