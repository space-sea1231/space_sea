#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
// const int K = 20;

int n, m;
ll sum;
int cnt;
int lg[N];
int fa[N], siz[N];
bool vis[N];
struct Node {
	ll val;
	int id;
	bool operator<(const Node &s) const {
		if (!id) return true;          
		if (!s.id) return false;
		ll a = val * s.id, b = s.val * id;  
		if (a != b) return a < b;
		return id < s.id;
	}
}; Node node[N], tree[N << 2], st[N];

bool Cmp1(Node &srca, Node &srcb) {
	if (srca.val == srcb.val) return srca.id < srcb.id;
	return srca.val < srcb.val;
}
int Find(int x) {
	if (fa[x] == x) return fa[x];
	return fa[x] = Find(fa[x]);
}
int fx, fy;
void Merge(int x, int y) {
	fx = Find(x), fy = Find(y);
	if (siz[fx] < siz[fy]) swap(fx, fy);
	// if (x == 4 && y == 3) printf("sss:%d\n", sum);
	sum -= (ll)siz[fx] * siz[fx] + (ll)siz[fy] * siz[fy];
	fa[fy] = fx; siz[fx] += siz[fy];
	sum += (ll)siz[fx] * siz[fx]; cnt--;
}
void Up(int x) {
	tree[x] = max(tree[x << 1], tree[x << 1 | 1]);
}
void Build(int x, int l, int r) {
	if (l == r) {
		tree[x] = st[l];
		return ;
	}
	int mid = (l + r) >> 1;
	Build(x << 1, l, mid);
	Build(x << 1 | 1, mid + 1, r);
	Up(x);
}
Node Query(int x, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[x];
	int mid = (l + r) >> 1;
	Node rev = (Node){0, 0};
	if (L <= mid) rev = max(rev, Query(x << 1, l, mid, L, R));
	if (mid < R) rev = max(rev, Query(x << 1 | 1, mid + 1, r, L, R));
	return rev;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	lg[0] = -1;
	ll maxn = 0;
	for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1, lg[i] = lg[i >> 1] + 1;
	for (int i = 1; i <= n; i++) {cin >> node[i].val; node[i].id = i; maxn = max(maxn, node[i].val);}
	sort(node + 1, node + n + 1, Cmp1);
	int top = 1; node[n + 1].val = INF;
	while (top <= n) {
		int k = node[top].val;
		while (node[top].val <= k) {
			if (vis[node[top].id - 1]) Merge(node[top].id, node[top].id - 1);
			if (vis[node[top].id + 1]) Merge(node[top].id, node[top].id + 1);
			vis[node[top].id] = 1; cnt++, sum++;
			top++;
		}
		if (!st[cnt].id || st[cnt].val * k <= sum * st[cnt].id) {
			st[cnt].val = sum;
			st[cnt].id = k;
			// printf("Debug%d: %d %d\n", cnt, i, sum);
		}
	}
	Build(1, 1, n);
	// for (int i = 1; i <= maxn; i++) printf("st[%d]=%d\n", i, st[i][0].val);
	// for (int k = 1; k <= lg[n]; k++) {
	// 	for (int i = 1; i + (1 << k) - 1 <= n; i++) {
	// 		st[i][k] = max(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
	// 	}
	// }
	ll last = 0;
	int a, b, x, y;
	int l, r, len;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b >> x >> y;
		l = ((ll)a * (last % n) + x - 1) % n + 1;
		r = ((ll)b * (last % n) + y - 1) % n + 1;
		if (l > r) swap(l, r);
		len = r - l + 1;
		// Node ans = max(st[l][lg[len]], st[r - (1 << lg[len]) + 1][lg[len]]);
		Node ans = Query(1, 1, n, l, r);
		if (ans.id == 0) printf("-1 -1\n");
		else printf("%lld %d\n", ans.val, ans.id);
		printf("%d %d %d\n", l, r, last % n);
		last = ans.id ? ans.val * ans.id : 1;
	}
	return 0;
}