#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
// #define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e5 + 10;

int n, m;
int a[N];
map<int, set<int> > mp;

inline int Gcd(int a, int b) {
	// #ifdef __Debug
	// printf("Gcd(%d,%d)=", a, b);
	// #endif
	if (b == 0) return a;
	while (b ^= a ^= b ^= a %= b);
	// #ifdef __Debug
	// printf("%d\n", a);
	// #endif
	return a;
}
namespace SGT_P {
	int pre[N << 2];

	inline void Up(int p) { pre[p] = max(pre[p << 1], pre[p << 1 | 1]);}
	void Update(int p, int l, int r, int pos, int w) {
		if (l == pos && r == pos) {
			pre[p] = w;
			// #ifdef __Debug
			// printf("U:pos=%d {%d, %d}\n", pos, w.pre, w.r);
			// #endif
			return;
		}
		int mid = l + r >> 1;
		if (pos <= mid) Update(p << 1, l, mid, pos, w);
		if (mid < pos) Update(p << 1 | 1, mid + 1, r, pos, w);
		Up(p);
	}
	int Query(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return pre[p];
		int mid = l + r >> 1;
		if (R <= mid) return Query(p << 1, l, mid, L, R);
		if (mid < L) return Query(p << 1 | 1, mid + 1, r, L, R);
		return max(Query(p << 1, l, mid, L, R), Query(p << 1 | 1, mid + 1, r, L, R));
	}
	int Pre(int pos) {
		int pre = 0;
		set<int>::iterator it = mp[a[pos]].lower_bound(pos);
		if (it != mp[a[pos]].begin()) pre = *prev(it);
		return pre;
	}
	int Nxt(int pos) {
		int nxt = 0;
		// if (pos > N) cerr<<pos << endl;// << " " << a[pos]<<endl;
		set<int>::iterator it = mp[a[pos]].upper_bound(pos);
		if (it != mp[a[pos]].end()) nxt = *it;
		return nxt;
	}
}

namespace SGT_GCD {
	int node[N << 2];
	inline void Init() { for (int i = 1; i < N; i++) node[i] = 1; }
	inline void Up(int p) { node[p] = Gcd(node[p << 1], node[p << 1 | 1]); }
	void Build(int p, int l, int r) {
		if (l == r) {
			node[p] = abs(a[l] - a[l - 1]);
			return ;
		}
		int mid = l + r >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		Up(p);
	}
	void Update(int p, int l, int r, int pos, int w) {
		if (l == pos && r == pos) {
			node[p] = w;
			// #ifdef __Debug
			// printf("Debug_GCD:%d -> %d\n", pos, w);
			// #endif
			return ;
		}
		int mid = l + r >> 1;
		if (pos <= mid) Update(p << 1, l, mid, pos, w);
		if (mid < pos) Update(p << 1 | 1, mid + 1, r, pos, w);
		Up(p);
	}
	inline void UpdateD(int p) {
		Update(1, 1, n, p, abs(a[p] - a[p - 1]));
		if (p != n) Update(1, 1, n, p + 1, abs(a[p + 1] - a[p]));
	}
	int Query(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p];
		int mid = l + r >> 1;
		if (R <= mid) return Query(p << 1, l, mid, L, R);
		if (mid < L) return Query(p << 1 | 1, mid + 1, r, L, R);
		return Gcd(Query(p << 1, l, mid, L, R), Query(p << 1 | 1, mid + 1, r, L, R));
	}
}

namespace SGT {
	struct Node {
		int maxn, minn;
	}; Node node[N << 2];

	inline void Up(int p) {
		node[p].maxn = max(node[p << 1].maxn, node[p << 1 | 1].maxn);
		node[p].minn = min(node[p << 1].minn, node[p << 1 | 1].minn);
	}
	void Build(int p, int l, int r) {
		if (l == r) {
			node[p].maxn = node[p].minn = a[l];
			return ;
		}
		int mid = l + r >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		Up(p);
	}
	void Update(int p, int l, int r, int pos, int w) {
		if (l == pos && r == pos) {
			node[p].maxn = node[p].minn = w;
			return ;
		}
		int mid = l + r >> 1;
		if (pos <= mid) Update(p << 1, l, mid, pos, w);
		if (mid < pos) Update(p << 1 | 1, mid + 1, r, pos, w);
		Up(p);
	}
	int Query_Min(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p].minn;
		int mid = l + r >> 1;
		if (R <= mid) return Query_Min(p << 1, l, mid, L, R);
		if (mid < L) return Query_Min(p << 1 | 1, mid + 1, r, L, R);
		return min(Query_Min(p << 1, l, mid, L, R), Query_Min(p << 1 | 1, mid + 1, r, L, R));
	}
	int Query_Max(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p].maxn;
		int mid = l + r >> 1;
		if (R <= mid) return Query_Max(p << 1, l, mid, L, R);
		if (mid < L) return Query_Max(p << 1 | 1, mid + 1, r, L, R);
		return max(Query_Max(p << 1, l, mid, L, R), Query_Max(p << 1 | 1, mid + 1, r, L, R));
	}
	bool Query(int l, int r, int k) {
		if (l == r) return true;
		int maxn = Query_Max(1, 1, n, l, r);
		int minn = Query_Min(1, 1, n, l, r);
		if (k == 0) return maxn == minn;
		// #ifdef __Debug
		// printf("Query(%d,%d,%d):maxn=%d minn=%d\n", l, r, k, maxn, minn);
		// #endif
		if ((maxn - minn) % k || (maxn - minn) / k != r - l) return false;
		// #ifdef __Debug
		// printf("---Past1---\n");
		// #endif
		int L = SGT_P::Query(1, 1, n, l, r);
		// #ifdef __Debug
		// printf("L=%d R=%d\n", L, R);
		// #endif
		if (l <= L) return false;
		// #ifdef __Debug
		// printf("---Past2---\n");
		// #endif
		if (SGT_GCD::Query(1, 1, n, l + 1, r) != k || (l == r && a[l] % k)) return false;
		return true;
	}
};

inline void Modify(int x, int y) {
	mp[a[x]].erase(x);
	mp[y].insert(x);
	// if (a[x] > N) cerr<<x << " " << y << " " << a[x] << "\n";
	int nxt = SGT_P::Nxt(x);
	a[x] = y;
	if (nxt) SGT_P::Update(1, 1, n, nxt, SGT_P::Pre(nxt));
	SGT_P::Update(1, 1, n, x, SGT_P::Pre(x));
	SGT_GCD::UpdateD(x);
	SGT::Update(1, 1, n, x, y);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	SGT_GCD::Init();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		mp[a[i]].insert(i);
	}
	SGT_GCD::Build(1, 1, n);
	SGT::Build(1, 1, n);
	for (int i = 1; i <= n; i++) SGT_P::Update(1, 1, n, i, SGT_P::Pre(i));

	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, y;
			cin >> x >> y;
			x ^= cnt, y ^= cnt;
			Modify(x, y);
		}
		if (opt == 2) {
			int l, r, k;
			cin >> l >> r >> k;
			l ^= cnt, r ^= cnt, k ^= cnt;
			if (SGT::Query(l, r, k)) {
				printf("Yes\n");
				cnt++;
			}
			else printf("No\n");
		}
		#ifdef __Debug
		printf("\n");
		#endif
	}
	// #ifdef __Debug
	// printf("%d\n", SGT_GCD::Query(1, 1, n, 1, 5));
	// #endif
	// printf("%d\n", Gcd(2, 4));
	return 0;
}
/*
1.max
2.min
3.differential`s gcd
4.prefix same
Special Containment Procedures
Secure（控制）、Contain（收容）、Protect（保护）

Dead reason:
1.Incomplete Update
2.No special verdict l==r
*/