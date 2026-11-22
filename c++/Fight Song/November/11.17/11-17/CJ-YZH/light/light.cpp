#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 2e5 + 10;

int n, m;
int a[N], c[N];
int nxt[N], lst[N];
struct BinaryTree {
	int tree[N];

	int Lowbit(int x) {
		return x & -x;
	}
	void Update(int x, int y) {
		for (int i = x; i <= n; i += Lowbit(i)) tree[i] += y;
	}
	int Query(int x) {
		int rev = 0;
		for (int i = x; i; i -= Lowbit(i)) rev += tree[i];
		return rev;
	}
}; BinaryTree B;

namespace SegmentTree {
	struct Node {
		bool val;
		int vis;
		int maxn;
	}; Node node[N << 1];
	
	void Up(int p) {
		node[p].maxn = max(node[p << 1].maxn, node[p << 1 | 1].maxn);
		node[p].val = node[p << 1].val | node[p << 1 | 1].val;
	}
	void Down(int p) {
		if (node[p].vis) {
			node[p << 1].val = node[p << 1 | 1].val = false;
			node[p << 1].vis = node[p << 1 | 1].vis = node[p].vis;
			node[p].vis = false;
		}
	}
	void Build(int p, int l ,int r) {
		node[p].val = true;
		if (l == r) {
			node[p].maxn = a[l];
			return ;
		}
		int mid = l + r >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		Up(p);
	}
	void Update(int p, int l, int r, int L, int R) {
		// cerr << "Debug1: " << p << " " << l << " " << r << " " << L << " " << R << "\n";
		if (L <= l && r <= R) {
			// cerr << p << " " << node[p].val << "\n";
			node[p].val = false;
			node[p].vis = true;
			return ;
		}
		Down(p);
		int mid = l + r >> 1;
		if (mid >= R) Update(p << 1, l, mid, L, R);
		if (mid < L) Update(p << 1 | 1, mid + 1, r, L, R);
		Up(p);
	}
	int QueryMx(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p].maxn;
		int mid = l + r >> 1;
		if (mid >= R) return QueryMx(p << 1, l, mid, L, R);
		if (mid < L) return QueryMx(p << 1 | 1, mid + 1, r, L, R);
		return max(QueryMx(p << 1, l, mid, L, R), QueryMx(p << 1 | 1, mid + 1, r, L, R));
	}
	int Query(int p, int l, int r, int L, int R) {
		// cerr << p << " " << l << " " << r << " " << L << " " << R << "\n";
		// cerr << node[p].val  << "\n";
		if (L <= l && r <= R) return node[p].val;
		Down(p);
		int mid = l + r >> 1;
		if (mid >= R) return Query(p << 1, l, mid, L, R);
		if (mid < L) return Query(p << 1 | 1, mid + 1, r, L, R);
		return Query(p << 1, l, mid, L, R) | Query(p << 1 | 1, mid + 1, r, L, R);
	}
} using namespace SegmentTree;

struct Limit {
	int l, r;
	int val;
	bool flag;

}; Limit lim[N];

bool Cmp1(Limit &a, Limit &b) {
	if (a.val == b.val) {
		if (a.l == b.l) return a.r < b.r;
		return a.l > b.l;
	}
	return a.val < b.val;
}
bool Cmp2(Limit &a, Limit &b) {
	if (a.val == b.val) {
		if (a.l == b.l) return a.r > b.r;
		return a.l < b.l;
	}
	return a.val < b.val;
}
signed main() {
    freopen("light.in", "r", stdin);
    freopen("light.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	if (m == 0) {
		printf("0\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) lst[i] = i - 1, nxt[i] = i + 1;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= m; i++) cin >> lim[i].l >> lim[i].r >> lim[i].val;
	Build(1, 1, n);
	sort(lim + 1, lim + m + 1, Cmp1);
	for (int i = 1; i <= m;) {
		for (int j = i; j <= m; j++) {
			if (!Query(1, 1, n, lim[j].l, lim[j].r) || (QueryMx(1, 1, n, lim[j].l, lim[j].r) > lim[j].val)) {
				printf("-1\n");
				return 0;
			}
			if (lim[j + 1].val != lim[j].val) break;
		}
		for (int j = i; j <= m; j++) {
			Update(1, 1, n, lim[j].l, lim[j].r);
			i = j + 1;
			if (lim[j + 1].val != lim[j].val) break;
		}
	}
	for (int i = 1, j; i <= m;) {
		for (j = i; j <= m; j++) {
			if (B.Query(lim[j].r)) lim[j].flag = true;
			B.Update(lim[i].r, 1);
			if (lim[j + 1].val != lim[j].val) break;
		}
		for (int k = i; k <= j; k++) {
			B.Update(lim[j].r, -1);
		}
		i = j + 1;
	}
	sort(lim + 1, lim + m + 1, Cmp2);
	int pos;
	int lll = 0;
	ll min1 = INF, min2 = INF, lstmin; // 1.当前最大值 2.下一个最大值
	ll ans = 0, f[2] = {0, 0};
	bool flag = false;
	lim[0].val = INF;
	for (int i = 1; i <= m; i++) {
		if (lim[i].flag) continue;
		cerr << lim[i].l << " " << lim[i].r << "\n";
		if (lim[i].val != lim[lll].val) {
			pos = lim[i].l;
			min1 = min2 = lstmin = INF;
			ans += f[1];
			f[0] = f[1] = 0;
			flag = false;
		} else {
			flag = true;
			pos = max(pos, lim[i].l);
			if (lim[i].l >= lim[lll].r) {
				min1 = lstmin = min2, min2 = INF;
				ans += f[1];
				f[0] = f[1] = 0;
			}
		}
		// printf("Debug%d: l=%d r=%d val=%d\n", i, lim[i].l, lim[i].r, lim[i].val);
		while (pos <= lim[i].r) {
			min1 = min(min1, (ll)c[pos] * (lim[i].val - a[pos]));
			// cerr << lst[pos] << " " << pos << " " << nxt[pos] << " " << min1 << "\n";
			if (lim[i].val == lim[i + 1].val && pos >= lim[i + 1].l) {
				min2 = min(min2, (ll)c[pos] * (lim[i].val - a[pos]));
			}
			nxt[lst[pos]] = nxt[pos];
			lst[nxt[pos]] = lst[pos];
			pos = nxt[pos];
		}
		// printf("Ed: min1=%lld min2=%lld\n", min1, min2);
		if (lim[i].val == lim[lll].val) {
			int f0 = f[0], f1 = f[1];
			f[0] = f1;
			f[1] = min(f0 + lstmin, f1 + min1);
		}
		lll = i;
	}
	// cerr << flag;
	// cerr << ans << " " << min1 << "\n";
	printf("%lld\n", ans + (flag ? f[1] : min1));
	return 0;
}