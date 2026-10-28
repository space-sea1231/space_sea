#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cassert>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int a[N];
vector<int> e[N];

namespace SegmentTree {
	int node[N << 2];

	void Up(int p) { node[p] = min(node[p << 1], node[p << 1 | 1]); }
	void Build(int p, int l, int r) {
		if (l == r) {
			node[p] = INF;
			return ;
		}
		int mid = l + r >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		Up(p);
	}
	void Update(int p, int l, int r, int pos) {
		if (l == r) {
			node[p] = (node[p] == INF ? l : INF);
			return ;
		}
		int mid = l + r >> 1;
		if (pos <= mid) Update(p << 1, l, mid, pos); 
		if (mid < pos) Update(p << 1 | 1, mid + 1, r, pos); 
		Up(p);
	}
	int Query(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p];
		int mid = l + r >> 1;
		if (R <= mid) return Query(p << 1, l, mid, L, R);
		if (mid < L) return Query(p << 1 | 1, mid + 1, r, L, R);
		return min(Query(p << 1, l, mid, L, R), Query(p << 1 | 1, mid + 1, r, L, R));
	}
} using namespace SegmentTree;

namespace ChainTree {
	int num;
	int son[N], fa[N], top[N];
	int dfn[N], seg[N], siz[N];
	void Dfs1(int u, int f) {
		fa[u] = f; siz[u] = 1;
		int maxn = 0;
		for (int v : e[u]) {
			if (v == f) continue;
			Dfs1(v, u);
			siz[u] += siz[v];
			if (maxn < siz[v]) {
				maxn = siz[v];
				son[u] = v;
			}	
		}
	}
	void Dfs2(int u, int f) {
		if (son[u]) {
			dfn[son[u]] = ++num;
			seg[num] = son[u];
			top[son[u]] = top[u];
			Dfs2(son[u], u);
		}
		for (int v : e[u]) {
			if (!dfn[v]) {
				dfn[v] = ++num;
				seg[num] = v;
				top[v] = v;
				Dfs2(v, u);
			}
		}
	}
	void Update1(int x) { Update(1, 1, n, dfn[x]); }
	int Query1(int x) {
		int minn = INF;
		while (x) {
			// cerr << top[x] << " " << x << "\n";
			minn = min(minn, Query(1, 1, n, dfn[top[x]], dfn[x]));
			x = fa[top[x]];
		}
		// cerr << "\n";
		return (minn == INF ? 0 : minn);
	}
} using namespace ChainTree;
void Init() {
	dfn[1] = top[1] = seg[1] = num = 1;
	seg[0] = -1;
	Dfs1(1, 0); Dfs2(1, 0);
	Build(1, 1, n);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	Init();
	// for (int i = 1; i <= n; i++) printf("dfn[%d]=%d top[%d]=%d seg[%d]=%d\n", i, dfn[i], i, top[i], i, seg[i]);
	for (int i = 1; i <= m; i++) {
		int opt, x;
		cin >> opt >> x;
		if (opt == 0) Update1(x);
		if (opt == 1) printf("%d\n", seg[Query1(x)]);
	}
	return 0;
}
/*
Bread tastes better when it`s shared
一起分享的面包，格外香甜
*/