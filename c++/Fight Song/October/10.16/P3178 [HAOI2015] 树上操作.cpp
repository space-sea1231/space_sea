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
	struct Node {
		ll sum;
		ll vis;
	}; Node node[N << 2];
	
	void Up(int p) { node[p].sum = node[p << 1].sum + node[p << 1 | 1].sum; }
	void Down(int p, int l, int r) {
		int mid = l + r >> 1;
		node[p << 1].sum += (ll)(mid - l + 1) * node[p].vis;
		node[p << 1].vis += node[p].vis;
		node[p << 1 | 1].sum += (ll)(r - mid) * node[p].vis;
		node[p << 1 | 1].vis += node[p].vis;
		node[p].vis = 0;
	}
	void Build(int p, int l, int r, int seg[]) {
		if (l == r) {
			node[p].sum = a[seg[l]];
			return ;
		}
		int mid = l + r >> 1;
		Build(p << 1, l, mid, seg);
		Build(p << 1 | 1, mid + 1, r, seg);
		Up(p);
	}
	void Update_node(int p, int l, int r, int pos, int v) {
		if (l == r) {
			node[p].sum += v;
			return ;
		}
		Down(p, l, r);
		int mid = l + r >> 1;
		if (pos <= mid) Update_node(p << 1, l, mid, pos, v); 
		if (mid < pos) Update_node(p << 1 | 1, mid + 1, r, pos, v); 
		Up(p);
	}
	void Update_line(int p, int l, int r, int L, int R, int v) {
		if (L <= l && r <= R) {
			node[p].sum += (ll)(r - l + 1) * v;
			node[p].vis += v;
			return ;
		}
		Down(p, l, r);
		int mid = l + r >> 1;
		if (L <= mid) Update_line(p << 1, l, mid, L, R, v); 
		if (mid < R) Update_line(p << 1 | 1, mid + 1, r, L, R, v); 
		Up(p);
	}
	ll Query(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p].sum;
		Down(p, l, r);
		int mid = l + r >> 1;
		if (R <= mid) return Query(p << 1, l, mid, L, R);
		if (mid < L) return Query(p << 1 | 1, mid + 1, r, L, R);
		return Query(p << 1, l, mid, L, R) + Query(p << 1 | 1, mid + 1, r, L, R);
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
	void Update1(int x, int v) { Update_node(1, 1, n, dfn[x], v); }
	void Update2(int x, int v) { Update_line(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, v);}
	ll Query1(int x) {
		ll sum = 0;
		while (x) {
			// cerr << top[x] << " " << x << "\n";
			sum += Query(1, 1, n, dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		// cerr << "\n";
		return sum;
	}
} using namespace ChainTree;
void Init() {
	dfn[1] = top[1] = seg[1] = num = 1;
	Dfs1(1, 0); Dfs2(1, 0);
	Build(1, 1, n, seg);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	Init();
	// for (int i = 1; i <= n; i++) printf("dfn[%d]=%d top[%d]=%d seg[%d]=%d\n", i, dfn[i], i, top[i], i, seg[i]);
	for (int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, a;
			cin >> x >> a;
			Update1(x, a);
		}
		if (opt == 2) {
			int x, a;
			cin >> x >> a;
			Update2(x, a);
		}
		if (opt == 3) {
			int x;
			cin >> x;
			printf("%lld\n", Query1(x));
		}
	}
	return 0;
}
/*
Bread tastes better when it`s shared
一起分享的面包，格外香甜
*/