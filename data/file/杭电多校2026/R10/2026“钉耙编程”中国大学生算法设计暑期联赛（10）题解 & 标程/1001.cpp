#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 2E5, M = 17;

#define ls p << 1
#define rs p << 1 | 1
#define Mid (pl + pr >> 1) 
template<class Info, class Tag>
struct LazySegmentTree {
	int n;
	vector<Info> info;
	vector<Tag> tag; 
	LazySegmentTree(int siz) : n(siz) {
		info.resize(n << 2);
		tag.resize(n << 2);
		auto build = [&](auto&& self, int p, int pl, int pr) -> void {
			if (pl == pr) {
				return;
			}
			self(self, ls, pl, Mid);
			self(self, rs, Mid + 1, pr);
			push_up(p);
		};
		build(build, 1, 1, n);
	}

	LazySegmentTree(vector<Info>& init, int siz) : n(siz) {
		info.resize(n << 2);
		tag.resize(n << 2);
		auto build = [&](auto&& self, int p, int pl, int pr) -> void {
			if (pl == pr) {
				info[p] = init[pl];
				return;
			}
			self(self, ls, pl, Mid);
			self(self, rs, Mid + 1, pr);
			push_up(p);
		};
		build(build, 1, 1, n);
	}
	
	void push_up(int p) {
		info[p] = info[ls] + info[rs];
	}

	void apply(int p, const Tag& t) {
		info[p].apply(t);
		tag[p].apply(t);
	}

	void push_down(int p) {
		apply(ls, tag[p]);
		apply(rs, tag[p]);
		tag[p] = Tag();
	}
	
	void update(int x, int p, int pl, int pr, const Info& a) {
		if (pl == pr) {
			info[p] = a;
			return;
		}
		push_down(p);
		if (x <= Mid) update(x, ls, pl, Mid, a);
		else update(x, rs, Mid + 1, pr, a);
		push_up(p);
	}

	void update(int x, const Info& a) {
		update(x, 1, 1, n, a);
	}

	void update(int L, int R, int p, int pl, int pr, const Tag& t) {
		if (L <= pl && pr <= R) {
			apply(p, t);
			return;
		}
		push_down(p);
		if (L <= Mid) update(L, R, ls, pl, Mid, t);
		if (R > Mid) update(L, R, rs, Mid + 1, pr, t);
		push_up(p);
	}

	void update(int L, int R, const Tag& t) {
		update(L, R, 1, 1, n, t);
	}
	
	Info query(int L, int R, int p, int pl, int pr) {
		if (L > pr || R < pl) return Info();
		if (L <= pl && pr <= R) return info[p];
		push_down(p);
		return query(L, R, ls, pl, Mid) + query(L, R, rs, Mid + 1, pr);
	}

	Info query(int L, int R) {
		return query(L, R, 1, 1, n);
	}
	
	Info temp;
	template<class F>
	int findFirst(int p, int pl, int pr, int L, F check) {
		if (pr < L) return -1;
		if (pl >= L && !check(temp + info[p])) {
			temp = temp + info[p];
			return -1;
		}
		if (pl == pr) return pl;
		push_down(p);
		int res = findFirst(ls, pl, Mid, L, check);
		if (res == -1) {
			res = findFirst(rs, Mid + 1, pr, L, check);
		}
		return res;
	}
	
	template<class F>
	int findFirst(int L, F check) {
		temp = Info();
		return findFirst(1, 1, n, L, check);
	}

	template<class F>
	int findLast(int p, int pl, int pr, int R, F check) {
		if (pl > R) return -1;
		if (pr <= R && !check(info[p] + temp)) {
			temp = info[p] + temp;
			return -1;
		}
		if (pl == pr) return pr;
		push_down(p);
		int res = findLast(rs, Mid + 1, pr, R, check);
		if (res == -1) {
			res = findLast(ls, pl, Mid, R, check);
		}
		return res;
	}

	template<class F>
	int findLast(int R, F check) {
		temp = Info();
		return findLast(1, 1, n, R, check);
	}
};


struct Tag {
	int v {0};

	void apply(const Tag& t) {
		v += t.v;
	}
};

struct Info {
	int mx {0};
	int cnt {1};

	void apply(const Tag& t) {
		mx += t.v;
	}
};

Info operator+ (const Info& a, const Info& b) {
	Info c;

	if (a.mx > b.mx) {
		c = a;
	}
	else if (a.mx < b.mx) {
		c = b;
	}
	else {
		c.mx = a.mx;
		c.cnt = a.cnt + b.cnt;
	}

	return c;
}

namespace ST1 {
	int info[N + 1][M + 1];

	void init(int n) {
		const int k = __lg(n);
		for (int j = 1; j <= k; j++) {
			for (int i = 1; i + (1 << j) - 1 <= n; i++) {
				info[i][j] = min(info[i][j - 1], info[i + (1 << (j - 1))][j - 1]);
			}
		}
	}

	int query(int L, int R) {
		int k = __lg(R - L + 1);
		return min(info[L][k], info[R - (1 << k) + 1][k]);
	}
}

namespace ST2 {
	int info[N + 1][M + 1];

	void init(int n) {
		const int k = __lg(n);
		for (int j = 1; j <= k; j++) {
			for (int i = 1; i + (1 << j) - 1 <= n; i++) {
				info[i][j] = min(info[i][j - 1], info[i + (1 << (j - 1))][j - 1]);
			}
		}
	}

	int query(int L, int R) {
		int k = __lg(R - L + 1);
		return min(info[L][k], info[R - (1 << k) + 1][k]);
	}
}

struct SuffixArray {
	int n;
	string s;
	vector<int> sa, rk, oldrk, tp, cnt, lcp;

	SuffixArray(const string &s) : s(s) {
		n = s.size() - 1;
		sa.resize(n + 1);
		rk.resize((n << 1) + 1);
		oldrk.resize((n << 1) + 1);
		tp.resize(n + 1);
		cnt.resize(max(n + 1, 128));
		getsa();
		getlcp();
	}

	void getsa() {
		int m = max(n, 127);
		for (int i = 1; i <= n; i++) {
			rk[i] = s[i];
			tp[i] = i;
		}
		fill(cnt.begin(), cnt.begin() + m + 1, 0);
		for (int i = 1; i <= n; i++) ++cnt[rk[i]];
		for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--) sa[cnt[rk[tp[i]]]--] = tp[i];

		for (int w = 1, p = 0; p < n; w <<= 1, m = p) {
			p = 0;
			for (int i = 1; i <= w; i++) tp[++p] = n - w + i;
			for (int i = 1; i <= n; i++)
				if (sa[i] > w) tp[++p] = sa[i] - w;

			fill(cnt.begin(), cnt.begin() + m + 1, 0);
			for (int i = 1; i <= n; i++) ++cnt[rk[i]];
			for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
			for (int i = n; i >= 1; i--) sa[cnt[rk[tp[i]]]--] = tp[i];

			oldrk.swap(rk);
			rk[sa[1]] = p = 1;
			for (int i = 2; i <= n; i++) {
				rk[sa[i]] = (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
					oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) ? p : ++p;
			}
		}
	}

	void getlcp() {
		lcp.resize(n + 1);
		for (int i = 1; i <= n; i++) rk[sa[i]] = i;

		int h = 0;
		lcp[1] = 0;
		for (int i = 1; i <= n; i++) {
			int j = sa[rk[i] - 1];
			if (h > 0) h--;
			while (i + h <= n && j + h <= n && s[i + h] == s[j + h]) h++;
			lcp[rk[i]] = h;
		}
	}
};

void solve() {
	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;

	vector<int> f(n + 2), g(n + 2);

	auto t = s;
	reverse(t.begin(), t.end());

	s = " " + s;
	t = " " + t;
	SuffixArray sa1(s), sa2(t);

	for (int i = 1; i <= n; i++) {
		ST1::info[i][0] = sa1.lcp[i];
		ST2::info[i][0] = sa2.lcp[i];
	}

	ST1::init(n);
	ST2::init(n);

	auto pre_lcp = [&](int i, int j) {
		assert(i != j);
		i = n - i + 1;
		j = n - j + 1;
		i = sa2.rk[i];
		j = sa2.rk[j];
		if (i > j) {
			swap(i, j);
		}

		if (i == 0) {
			return 0;
		}

		return ST2::query(i + 1, j);
	};

	auto suf_lcp = [&](int i, int j) {
		assert(i != j);
		i = sa1.rk[i];
		j = sa1.rk[j];
		if (i > j) {
			swap(i, j);
		}

		if (i == 0) {
			return 0;
		}

		return ST1::query(i + 1, j);
	};

	ll ans = 0;

	LazySegmentTree<Info, Tag> seg(n);

	auto update = [&](int L, int R, int v, int len) {
		L = L - 1ll * len * (len - 1) / 2 % n;
		R = R - 1ll * len * (len - 1) / 2 % n;

		L = L % n + n;
		R = R % n + n;

		if (L > n) {
			L -= n;
		}
		if (R > n) {
			R -= n;
		}

		if (L <= R) {
			seg.update(L, R, {v});
		}
		else {
			seg.update(L, n, {v});
			seg.update(1, R, {v});
		}
	};

	vector<vector<pair<int, int>>> line(n + 1);

	for (int len = 1; len <= n && 1ll * (len - k + 1 + len) * k / 2 <= n; len++) {
		for (int i = len, j = 2 * len; j <= n; i += len, j += len) {
			int len1 = pre_lcp(i - 1, j - 1);
			int len2 = suf_lcp(i, j);

			len1 = min(len1, len - 1);
			len2 = min(len2, len);

			if (len1 + len2 < len) continue;

			int L = i - len1, R = i + len2 - len;
			if (R + 2 * len - 1 == n) {
				R--;
			}


			if (R < L) continue;

			line[len].emplace_back(L, R);
		}
	}

	for (int len = 1; len <= n && 1ll * (len - k + 1 + len) * k / 2 <= n; len++) {
		for (auto [L, R] : line[len]) {
			update(L, R, 1, len);
		}

		if (len >= k - 1) {
			auto info = seg.query(1, n);
			if (info.mx == k - 1) {
				ans += info.cnt;
			}

			for (auto [L, R] : line[len - k + 2]) {
				update(L, R, -1, len - k + 2);
			}
		}
	}

	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int tt = 1;
	cin >> tt;
	while (tt--) solve();

	return 0;
}