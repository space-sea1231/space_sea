#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

int Test_id, T;
int n, m;
ll k;
ll a[N];

namespace SegmentTree {
	struct Node {
		ll val;
		ll max_v, min_v;
		ll tag;
	} tree[N << 2];

	void Up(int p) {
		tree[p].val = tree[p << 1].val + tree[p << 1 | 1].val;
		tree[p].max_v = max(tree[p << 1].max_v, tree[p << 1 | 1].max_v);
		tree[p].min_v = min(tree[p << 1].min_v, tree[p << 1 | 1].min_v);
	}

	void Apply(int p, int l, int r, ll v) {
		tree[p].val = v * (r - l + 1);
		tree[p].max_v = v;
		tree[p].min_v = v;
		tree[p].tag = v;
	}

	void Down(int p, int l, int r) {
		if (tree[p].tag == -1) return;
		int mid = (l + r) >> 1;
		Apply(p << 1, l, mid, tree[p].tag);
		Apply(p << 1 | 1, mid + 1, r, tree[p].tag);
		tree[p].tag = -1;
	}

	void Build(int p, int l, int r) {
		tree[p].tag = -1;
		if (l == r) {
			tree[p].val = tree[p].max_v = tree[p].min_v = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		Up(p);
	}

	void UpdateRange(int p, int l, int r, int L, int R, ll v) {
		if (L <= l && r <= R) {
			Apply(p, l, r, v);
			return;
		}
		Down(p, l, r);
		int mid = (l + r) >> 1;
		if (L <= mid) UpdateRange(p << 1, l, mid, L, R, v);
		if (R > mid) UpdateRange(p << 1 | 1, mid + 1, r, L, R, v);
		Up(p);
	}

	void UpdatePoint(int p, int l, int r, int pos, ll v) {
		if (l == r) {
			tree[p].val = tree[p].max_v = tree[p].min_v = v;
			return;
		}
		Down(p, l, r);
		int mid = (l + r) >> 1;
		if (pos <= mid) UpdatePoint(p << 1, l, mid, pos, v);
		else UpdatePoint(p << 1 | 1, mid + 1, r, pos, v);
		Up(p);
	}

	ll QuerySum(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return tree[p].val;
		Down(p, l, r);
		int mid = (l + r) >> 1;
		ll res = 0;
		if (L <= mid) res += QuerySum(p << 1, l, mid, L, R);
		if (R > mid) res += QuerySum(p << 1 | 1, mid + 1, r, L, R);
		return res;
	}

	ll QueryVal(int p, int l, int r, int pos) {
		if (l == r) return tree[p].val;
		Down(p, l, r);
		int mid = (l + r) >> 1;
		if (pos <= mid) return QueryVal(p << 1, l, mid, pos);
		return QueryVal(p << 1 | 1, mid + 1, r, pos);
	}

	int FindFirstGE(int p, int l, int r, ll v) {
		if (tree[p].max_v < v) return -1;
		if (l == r) return l;
		Down(p, l, r);
		int mid = (l + r) >> 1;
		if (tree[p << 1].max_v >= v) return FindFirstGE(p << 1, l, mid, v);
		return FindFirstGE(p << 1 | 1, mid + 1, r, v);
	}
} using namespace SegmentTree;

void Solve() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);

	Build(1, 1, n);

	int sz = n;
	ll ans = 0;
	bool possible = true;

	for (int i = 1; i <= m; i++) {
		ll b, c;
		cin >> b >> c;
		if (!possible) continue;

		int L = FindFirstGE(1, 1, n, b);
		if (L != -1 && L <= sz) {
			ll cnt = sz - L + 1;
			ll sum = QuerySum(1, 1, n, L, sz);
			ll max_del = sum - cnt * (b - 1);

			if (c <= max_del) {
				int low = L, high = sz, mid_pos = sz;
				while (low <= high) {
					int mid = (low + high) >> 1;
					ll cur_cnt = mid - L + 1;
					ll cur_sum = QuerySum(1, 1, n, L, mid);
					if (cur_sum - cur_cnt * (b - 1) >= c) {
						mid_pos = mid;
						high = mid - 1;
					} else {
						low = mid + 1;
					}
				}

				if (mid_pos > L) {
					ll already = QuerySum(1, 1, n, L, mid_pos - 1) - (ll)(mid_pos - L) * (b - 1);
					UpdateRange(1, 1, n, L, mid_pos - 1, b - 1);
					c -= already;
				}
				ll cur_val = QueryVal(1, 1, n, mid_pos);
				UpdatePoint(1, 1, n, mid_pos, cur_val - c);
				c = 0;
			} else {
				UpdateRange(1, 1, n, L, sz, b - 1);
				c -= max_del;
			}
		}

		if (c > 0) {
			ll target = b + c - 1;
			if (sz == 0) {
				possible = false;
				continue;
			}
			ll cur = QueryVal(1, 1, n, sz);
			sz--;

			while (cur < target) {
				if (sz == 0) {
					possible = false;
					break;
				}
				ll other = QueryVal(1, 1, n, sz);
				sz--;

				if (cur + other <= k) {
					possible = false;
					break;
				}

				cur = cur + other - k;
				ans++;
			}

			if (!possible) continue;

			cur -= c;
			if (cur > 0) {
				sz++;
				UpdatePoint(1, 1, n, sz, cur);
			}
		}
	}

	if (!possible) cout << -1 << "\n";
	else cout << ans << "\n";
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	if (cin >> Test_id >> T) {
		while (T--) Solve();
	}
	return 0;
}
/*
Retain 保留
1.区间修改
2.单点修改
3.区间和
4.线段树二分

大部分人要我学习去看 世俗的眼光
我认真学习了世俗眼光 世俗到天亮
一部外国电影没听懂一句话
看完结局才是笑话
你看我多乖多聪明多么听话 多奸诈
喝了几大碗米酒再离开是为了模仿
一出门不小心吐的那幅是谁的书画
你一天一口一个 亲爱的对方
多么不流行的模样
都应该练练书法再出门闯荡
才会有人热情买账
要是能重来 我要选李白
几百年前做的好坏 没那么多人猜
要是能重来 我要选李白
至少我还能写写诗来澎湃 逗逗女孩
要是能重来 我要选李白
创作也能到那么高端 被那么多人崇拜
要是能重来
喝了几大碗米酒再离开是为了模仿
一出门不小心吐的那幅是谁的书画
你一天一口一个 亲爱的对方
多么不流行的模样
都应该练练书法再出门闯荡
才会有人热情买账
要是能重来 我要选李白
几百年前做的好坏 没那么多人猜
要是能重来 我要选李白
至少我还能写写诗来澎湃 逗逗女孩
要是能重来 我要选李白
创作也能到那么高端 被那么多人崇拜
要是能重来
要是能重来 我要选李白
几百年前做的好坏 没那么多人猜
要是能重来 我要选李白
至少我还能写写诗来澎湃 逗逗女孩
要是能重来 我要选李白
创作也能到那么高端 被那么多人崇拜
要是能重来
*/