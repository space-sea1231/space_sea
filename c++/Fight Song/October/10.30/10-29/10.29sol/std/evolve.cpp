#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ldb = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

struct State {
	int j, pre;
	bool sw;
	State(int _j = 0, int _pre = -1, bool _sw = 0) : j(_j), pre(_pre), sw(_sw) {}
};

bool subseq(const string &a, const string &b) {
	int p = 0;
	for (int i = 0; i < (int)b.size() && p < (int)a.size(); ++i) {
		if (a[p] == b[i]) {
			++p;
		}
	}
	return p == (int)a.size();
}

int main() {
	freopen("evolve.in","r",stdin);
	freopen("evolve.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	string U;
	cin >> U;

	vector<string> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	sort(a.begin(), a.end(), [&](const string &x, const string &y) {
		if (x.size() != y.size()) {
			return x.size() < y.size();
		}
		return x < y;
	});

	vector<string> s(n + 1);
	for (int i = 1; i <= n; ++i) {
		s[i] = a[i - 1];
		if (!subseq(s[i], U)) {
			cout << "impossible\n";
			return 0;
		}
	}

	vector<vector<State> > f(n + 1);
	f[1].pb(0, -1, 0);

	for (int i = 1; i < n; ++i) {
		vector<State> g;

		bool ok = subseq(s[i], s[i + 1]);

		for (int k = 0; k < (int)f[i].size(); ++k) {
			int j = f[i][k].j;

			if (ok) {
				g.pb(j, k, 0);
			}

			if (j == 0 || subseq(s[j], s[i + 1])) {
				g.pb(i, k, 1);
			}
		}

		vector<State> h;
		for (int k = 0; k < (int)g.size(); ++k) {
			bool same = 0;
			for (int t = 0; t < (int)h.size(); ++t) {
				if (g[k].j == h[t].j) {
					same = 1;
					break;
				}
			}
			if (!same) {
				h.pb(g[k]);
			}
		}

		vector<State> nxt;
		for (int k = 0; k < (int)h.size(); ++k) {
			bool bad = 0;

			for (int t = 0; t < (int)h.size(); ++t) {
				if (k == t) {
					continue;
				}

				if (h[t].j == 0) {
					bad = 1;
					break;
				}

				if (h[k].j != 0 && subseq(s[h[t].j], s[h[k].j])) {
					bad = 1;
					break;
				}
			}

			if (!bad) {
				nxt.pb(h[k]);
			}
		}

		if (nxt.empty() || (int)nxt.size() > 2) {
			cout << "impossible\n";
			return 0;
		}

		f[i + 1] = nxt;
	}

	vector<int> col(n + 1);

	int cur = 0;
	int rev = 0;

	for (int i = n; i >= 2; --i) {
		State st = f[i][cur];

		col[i] = rev;

		if (st.sw) {
			rev ^= 1;
		}

		cur = st.pre;
	}

	col[1] = rev;

	vector<int> ans[2];

	for (int i = 1; i <= n; ++i) {
		ans[col[i]].pb(i);
	}

	cout << ans[0].size() << ' ' << ans[1].size() << '\n';

	for (int i = 0; i < (int)ans[0].size(); ++i) {
		cout << s[ans[0][i]] << '\n';
	}
	for (int i = 0; i < (int)ans[1].size(); ++i) {
		cout << s[ans[1][i]] << '\n';
	}

	return 0;
}
