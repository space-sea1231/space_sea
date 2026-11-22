#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int lenC;
ll ans;
int C[N], L[N];
int tmpC[N];
vector<int> e[N];

namespace SegmentTree {
	int num;
	int root[N];

	struct Node {
		int sum, cnt;
		int lson, rson;
	}; Node node[N * 40]; // log

	void Up(int p) {
		node[p].sum = node[node[p].lson].sum + node[node[p].rson].sum;
		node[p].cnt = node[node[p].lson].cnt + node[node[p].rson].cnt;
	}
	void Update(int &p, int l, int r, int pos, int val) {
		p = ++num;
		if (l == r) {
			node[num].cnt = 1;
			node[num].sum = val;
			return ;
		}
		int mid = l + r >> 1;
		if (pos <= mid) Update(node[p].lson, l, mid, pos, val);
		if (mid < pos) Update(node[p].rson, mid + 1, r, pos, val);
		Up(p);
	}
	void Merge(int &p, int &q, int l, int r) {
		if (!q) return ;
		if (!p) { p = q; return ; }
		if (l == r) {
			node[p].cnt += node[q].cnt;
			node[p].sum += node[q].sum;
			return ;
		}
		int mid = l + r >> 1;
		Merge(node[p].lson, node[q].lson, l, mid);
		Merge(node[p].rson, node[q].rson, mid + 1, r);
		Up(p);
	}
	int Query_cnt(int &p, int l, int r, int L, int R) {
		if (R < L) return 0;
		if (L <= l && r <= R) return node[p].cnt;
		int mid = l + r >> 1;
		if (R <= mid) return Query_cnt(node[p].lson, l, mid, L, R);
		if (mid < L) return Query_cnt(node[p].rson, mid + 1, r, L, R);
		return Query_cnt(node[p].lson, l, mid, L, R) + Query_cnt(node[p].rson, mid + 1, r, L, R);
	}
	int Query_sum(int &p, int l, int r, int L, int R) {
		if (R < L) return 0;
		if (L <= l && r <= R) return node[p].sum;
		int mid = l + r >> 1;
		if (R <= mid) return Query_sum(node[p].lson, l, mid, L, R);
		if (mid < L) return Query_sum(node[p].rson, mid + 1, r, L, R);
		return Query_sum(node[p].lson, l, mid, L, R) + Query_sum(node[p].rson, mid + 1, r, L, R);
	}
} using namespace SegmentTree;

void Dfs(int u) {
	Update(root[u], 1, lenC, C[u], tmpC[C[u]]);
	for (int v : e[u]) {
		Dfs(v);
		Merge(root[u], root[v], 1, lenC);
	}
	// if (u == 1) cerr<<Query_cnt(root[u], 1, lenC, 2, 2) << " " << C[u] << "\n";
	int l = 1, r = lenC, tot = 0, pos = 0, vl = 0;
	while (l <= r) {
		int mid = l + r >> 1, val = Query_sum(root[u], 1, lenC, 1, mid);
		if (val < m) {
			l = mid + 1;
			tot = Query_cnt(root[u], 1, lenC, 1, mid);
			pos = mid; vl = val;
		} else r = mid - 1;
	}
	l = 1, r = lenC;
	int nxt = 0;
	while (l <= r) {
		int mid = l + r >> 1, val = Query_sum(root[u], 1, lenC, 1, mid);
		if (val > vl) {
			r = mid - 1;
			nxt = mid;
		} else l = mid + 1;
	} // tot 有多少个可选 pos 最大酬劳
	if (nxt) tot += (m - Query_sum(root[u], 1, lenC, 1, pos)) / tmpC[nxt];
	ans = max(ans, (ll)tot * L[u]);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int fa;
		cin >> fa >> C[i] >> L[i];
		e[fa].emplace_back(i);
		tmpC[i] = C[i];
	}
	sort(tmpC + 1, tmpC + n + 1);
	lenC = unique(tmpC + 1, tmpC + n + 1) - tmpC - 1;
	for (int i = 1; i <= n; i++) C[i] = lower_bound(tmpC + 1, tmpC + lenC + 1, C[i]) - tmpC;
	Dfs(1);
	// printf("%d\n", Query_cnt(root[1], 1, lenC, 1, 1));
	printf("%lld\n", ans);
	return 0;
}
/*
The quieter you become,the more you can hear.
你越安静，能听见的就越多
*/