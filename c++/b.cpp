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
int a[N], a_pos[N];
int siz[N];
int dfnc[N], dfnr[N];
int idxl, idxr;
int root, minn = INF;
vector<int> e[N];

pair<int, int> Max(pair<int, int> a, pair<int, int> b) {
	if (a.first > b.first) return a;
	return b;
}
pair<int, int> Min(pair<int, int> a, pair<int, int> b) {
	if (a.first < b.first) return a;
	return b;
}
struct SegmentTree_Val {
	struct Node {
		// int val;
		pair<int, int> dfnc_max;
		pair<int, int> dfnr_min;
	};

	Node node[N << 2];

	void Up(int x) {
		node[x].dfnc_max = Max(node[x << 1].dfnc_max, node[x << 1 | 1].dfnc_max);
		node[x].dfnr_min = Min(node[x << 1].dfnr_min, node[x << 1 | 1].dfnr_min);
	}
	void Build(int x, int l, int r) {
		if (l == r) {
			// node[x].val = a_pos[l];
			node[x].dfnc_max = make_pair(dfnc[a_pos[l]], a_pos[l]);
			node[x].dfnr_min = make_pair(dfnr[a_pos[l]], a_pos[l]);
			// if (l == 1) printf("AAA:%d %d\n", node[x].dfnr_min);
			// cerr<<"dfnr["<<a_pos[l]<<"] = "<<dfnr[a_pos[l]]<<endl;
			return;
		}
		int mid = (l + r) >> 1;
		Build(x << 1, l, mid);
		Build(x << 1 | 1, mid + 1, r);
		Up(x);
	}
	void Update(int x, int l, int r, int p, int q) {
		if (l == r && l == p) {
			// node[x].val = a_pos[q];
			node[x].dfnc_max = make_pair(dfnc[a_pos[q]], a_pos[q]);
			node[x].dfnr_min = make_pair(dfnr[a_pos[q]], a_pos[q]);
			// cerr<<"dfnr["<<a_pos[q]<<"] = "<<dfnr[a_pos[q]]<<endl;
			return;
		}
		int mid = (l + r) >> 1;
		if (p <= mid) Update(x << 1, l, mid, p, q);
		if (mid < p) Update(x << 1 | 1, mid + 1, r, p, q);
		Up(x);
	}
	pair<int, int> Query_dfnr(int x, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			// printf("Debug: %d %d\n", node[x].dfnr_min.first, node[x].dfnr_min.second);
			return node[x].dfnr_min;
		}
		int mid = (l + r) >> 1;
		pair<int, int> rev = make_pair(INF, 0);
		if (L <= mid) rev = Min(rev, Query_dfnr(x << 1, l, mid, L, R));
		if (mid < R) rev = Min(rev, Query_dfnr(x << 1 | 1, mid + 1, r, L, R));
		return rev;
	}
	pair<int, int> Query_dfnc(int x, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			printf("Debug: %d %d\n", node[x].dfnc_max.first, node[x].dfnc_max.second);
			return node[x].dfnc_max;
		}
		int mid = (l + r) >> 1;
		pair<int, int> rev = make_pair(0, 0);
		if (L <= mid) rev = Max(rev, Query_dfnc(x << 1, l, mid, L, R));
		if (mid < R) rev = Max(rev, Query_dfnc(x << 1 | 1, mid + 1, r, L, R));
		return rev;
	}
};
SegmentTree_Val Stv;

struct SegmentTree {
	struct Node {
		int val;
		int maxn, minn;
	};

	Node node[N << 2];

	void Up(int x) {
		node[x].maxn = max(node[x << 1].maxn, node[x << 1 | 1].maxn);
		node[x].minn = min(node[x << 1].minn, node[x << 1 | 1].minn);
	}
	void Build(int x, int l, int r, int rev[]) {
		if (l == r) {
			node[x].val = node[x].minn = node[x].maxn = a[rev[l]];
			return;
		}
		int mid = (l + r) >> 1;
		Build(x << 1, l, mid, rev);
		Build(x << 1 | 1, mid + 1, r, rev);
		Up(x);
	}
	void Update(int x, int l, int r, int p, int q) {
		if (l == r && l == p) {
			node[x].val = node[x].maxn = node[x].minn = a[q];
			return;
		}
		int mid = (l + r) >> 1;
		if (p <= mid) Update(x << 1, l, mid, p, q);
		if (mid < p) Update(x << 1 | 1, mid + 1, r, p, q);
		Up(x);
	}
	int Query_maxn(int x, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return node[x].maxn;
		}
		int mid = (l + r) >> 1, rev = 0;
		if (L <= mid) rev = max(rev, Query_maxn(x << 1, l, mid, L, R));
		if (mid < R) rev = max(rev, Query_maxn(x << 1 | 1, mid + 1, r, L, R));
		return rev;
	}
	int Query_minn(int x, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return node[x].minn;
			// cerr<<
		}
		int mid = (l + r) >> 1, rev = INF;
		if (L <= mid) rev = min(rev, Query_minn(x << 1, l, mid, L, R));
		if (mid < R) rev = min(rev, Query_minn(x << 1 | 1, mid + 1, r, L, R));
		return rev;
	}
};
SegmentTree Seg;

struct TreeChain {
	int dfn;
	int son[N], father[N], top[N];
	int dep[N], siz[N];
	int seg[N], rev[N];// seg:树编号->链编号

	void Dfs1(int u, int fa) {
		dfnc[u] = ++idxl;
		siz[u] = 1; dep[u] = dep[fa] + 1;
		for (auto v:e[u]) {
			if (v == fa) continue;
			Dfs1(v, u);
			siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) son[u] = v;
		}
		dfnr[u] = ++idxr;
	}
	void Dfs2(int u, int fa) {
		if (son[u]) {
			int v = son[u];
			top[v] = top[u];
			seg[v] = ++dfn;
			rev[dfn] = v;
			Dfs2(v, u);
		}
		for (auto v:e[u]) {
			if (v == fa || v == son[u]) continue;
			top[v] = v;
			seg[v] = ++dfn;
			rev[dfn] = v;
			Dfs2(v, u);
		}
	}
	int QueryMax(int x, int y) {
		int fx = top[x], fy = top[y], rev = 0;
		while (fx != fy) {
			if (dep[fx] < dep[fy]) {
				swap(fx, fy);
				swap(x, y);
			}
			rev = max(rev, Seg.Query_maxn(1, 1, n, seg[fx], seg[x]));
			x = father[top[x]], fx = top[x];
		}
		if (dep[x] > dep[y]) swap(x, y);
		rev = max(rev, Seg.Query_maxn(1, 1, n, seg[x], seg[y]));
		return rev;
	}
	int QueryMin(int x, int y) {
		int fx = top[x], fy = top[y], rev = INF;
		while (fx != fy) {
			if (dep[fx] < dep[fy]) {
				swap(fx, fy);
				swap(x, y);
			}
			rev = min(rev, Seg.Query_minn(1, 1, n, seg[fx], seg[x]));
			x = father[top[x]], fx = top[x];
		}
		if (dep[x] > dep[y]) swap(x, y);
		rev = min(rev, Seg.Query_minn(1, 1, n, seg[x], seg[y]));
		printf("fa=%d x=%d minn=%d\n", x, y, Seg.Query_minn(1, 1, n, seg[x], seg[y]));
		printf("fa=%d x=%d minn=%d\n", seg[x], seg[y], Seg.Query_minn(1, 1, n, seg[x], seg[y]));
		return rev;
	}
	int QueryLen(int x, int y) {
		int fx = top[x], fy = top[y], rev = 0;
		while (fx != fy) {
			if (dep[fx] < dep[fy]) {
				swap(fx, fy);
				swap(x, y);
			}
			x = father[top[x]], fx = top[x];
			rev += seg[x] - seg[fx] + 1;
		}
		if (dep[x] > dep[y]) swap(x, y);
		rev += seg[y] - seg[x] + 1;
		return rev;
	}
	void Init() {
		seg[root] = ++dfn;
		top[root] = root;
		rev[1] = root;
		Dfs1(root, 0);
		Dfs2(root, 0);
		Seg.Build(1, 1, n, rev);
	}
};
TreeChain Tc;
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
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			a_pos[a[i]] = i;
		}
		for (int i = 1; i < n; i++) {
			int u, v;
			cin >> u >> v;
			e[u].emplace_back(v);
			e[v].emplace_back(u);
		}
		Dfs_Root(1, 0);
		Tc.Init(); Stv.Build(1, 1, n);
		cin >> m;
		for (int i = 1; i <= n; i++) printf("dfnc[%d]=%d\n", i, dfnc[i]);
		for (int i = 1; i <= m; i++) {
			int opt, x, y;
			cin >> opt >> x >> y;
			if (opt == 1) {
				Stv.Update(1, 1, n, a[x], a[y]);
				Stv.Update(1, 1, n, a[y], a[x]);
				Seg.Update(1, 1, n, Tc.seg[x], Tc.seg[y]);
				Seg.Update(1, 1, n, Tc.seg[y], Tc.seg[x]);
				swap(a[x], a[y]); swap(a_pos[x], a_pos[y]);
			}
			if (opt == 2) {
				int u = Stv.Query_dfnr(1, 1, n, x, y).second;
				int v = Stv.Query_dfnc(1, 1, n, x, y).second;
				cerr << u << " " << v << endl;
				cerr<<Stv.Query_dfnr(1, 1, n, x, y).first << " " << Stv.Query_dfnr(1, 1, n, x, y).second << endl;
				int maxn = Tc.QueryMax(u, v);
				int minn = Tc.QueryMin(u, v);
				int len = Tc.QueryLen(u, v);
				printf("len=%d\n", len);
				if (len == y - x + 1 && maxn == y && minn == x) printf("Yes\n");
				else printf("No\n");
			}
		}
	}
	return 0;
}