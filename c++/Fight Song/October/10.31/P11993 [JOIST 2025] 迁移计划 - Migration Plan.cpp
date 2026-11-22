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
const int N = 2e6 + 10;

int n, Q;
int num;
int a[N];
int dep[N], dfn[N], siz[N], idx[N];

vector<int> e[N];
vector<int> lst[N];

void Dfs(int u) {
	siz[u] = 1;
	dfn[u] = ++num, idx[num] = u;
	lst[dep[u]].emplace_back(dfn[u]);
	for (int v : e[u]) {
		dep[v] = dep[u] + 1;
		Dfs(v);
		siz[u] += siz[v];
	}
}
namespace SegmentTree {
	int num;
	int root[N];
	struct Node {
		int sum;
		int lson, rson;
		bool vis;
	}; Node node[N * 40];

	void Up(int p) {
		node[p].sum = node[node[p].lson].sum + node[node[p].rson].sum;
	}
	// void Down(int p) {
	// 	if (!node[p].vis) return ;
	// 	node[node[p].lson].vis |= node[p].vis;
	// 	node[node[p].lson].sum = 0;
	// 	node[node[p].rson].vis |= node[p].vis;
	// 	node[node[p].rson].sum = 0;
	// 	node[p].vis = false;
	// }
	void Build(int &p, int l, int r, int L, int R, int d) {
		if (R < L) return ;
		p = ++num;
		if (l == r) {
			node[p].sum = a[idx[lst[d][L]]];
			// cerr<<l << " " << a[idx[lst[d][L]]] << "\n";
			return ;
		}
		int mid = l + r >> 1;
		int Mid = upper_bound(lst[d].begin() + L, lst[d].begin() + R + 1, mid) - lst[d].begin();
		// cerr<<mid << " " << Mid << " " << lst[d][Mid] << " " << R + 1 - L << "\n";
		Build(node[p].lson, l, mid, L, Mid - 1, d);
		Build(node[p].rson, mid + 1, r, Mid, R, d);
		Up(p);
	}
	void Merge(int &p, int &q, int l, int r) {
		if (!q) return;
		if (!p) { p = q; return; } 
		// Down(q);
		if (l == r) {
			node[p].sum += node[q].sum;
			return ;
		}
		int mid = l + r >> 1;
		Merge(node[p].lson, node[q].lson, l, mid);
		Merge(node[p].rson, node[q].rson, mid + 1, r);
		Up(p);
	}
	void Update(int &p, int l, int r, int pos, int val) {
		if (!p) p = ++num;
		if (l == r) {
			node[p].sum += val;
			return ;
		}
		// Down(p);
		int mid = l + r >> 1;
		if (pos <= mid) Update(node[p].lson, l, mid, pos, val);
		if (mid < pos) Update(node[p].rson, mid + 1, r, pos, val);
		Up(p);
	}
	int Query(int &p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p].sum;
		// Down(p);
		int mid = l + r >> 1;
		if (R <= mid) return Query(node[p].lson, l, mid, L, R);
		if (mid < L) return Query(node[p].rson, mid + 1, r, L, R);
		return Query(node[p].lson, l, mid, L, R) + Query(node[p].rson, mid + 1, r, L, R);
	}
} using namespace SegmentTree;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 2; i <= n; i++) {
		int fa;
		cin >> fa;
		e[fa].emplace_back(i);
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	
	Dfs(1);
	for (int i = 0; i <= n; i++) Build(root[i], 1, n, 0, lst[i].size() - 1, i);
	
	// Merge(root[1], root[2], 1, n);
	// printf("%d\n", Query(root[1], 1, n, dfn[2], dfn[2] + siz[2] - 1));
	// return 0;
	cin >> Q;
	while (Q--) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, y;
			cin >> x >> y;
			// cerr<<root[y] << " " << root[x];
			Merge(root[y], root[x], 1, n);
			root[x] = 0;
			// node[root[x]].vis = true; node[root[x]].sum = 0;
			// cerr<<node[root[1]].vis << "\n";
		}
		if (opt == 2) {
			int x, y;
			cin >> x >> y;
			Update(root[dep[x]], 1, n, dfn[x], y);
		}
		if (opt == 3) {
			int x;
			cin >> x;
			// cerr<<dfn[x] <<" " <<dfn[x] +siz[x] - 1 <<"\n";
			// cerr<<x << " " << node[root[dep[x]]].vis << "\n";
			printf("%d\n", Query(root[dep[x]], 1, n, dfn[x], dfn[x] + siz[x] - 1));
		}
	}
	return 0;
}
/*
Warm tea,cold air,and time that slows down.
暖茶，凉风，还有慢下来的时光

*/