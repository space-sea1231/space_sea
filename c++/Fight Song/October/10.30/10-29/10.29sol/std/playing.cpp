#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
using ll = long long;
using pii = pair<int, int>;

inline int lowbit(int x) {
	return x & -x;
}

inline int highbit(int x) {
	if (!x) {
		return 0;
	}
	return 1 << (31 - __builtin_clz(x));
}

inline bool power2(int x) {
	return x && !(x & (x - 1));
}

int main() {
	freopen("playing.in","r",stdin);
	freopen("playing.out","w",stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		vector<int> a(n + 1);
		int S = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			S += a[i];
		}

		if (!power2(S)) {
			puts("no");
			continue;
		}

		int W = S + 1;
		vector<int> pre((n + 1) * W, -1);
		vector<char> opt((n + 1) * W);
		vector<char> f(W), g(W);

		f[a[1]] = 1;
		pre[W + a[1]] = 0;
		opt[W + a[1]] = 'l';

		int sum = a[1];

		for (int i = 1; i < n; ++i) {
			int x = a[i + 1];
			fill(g.begin(), g.end(), 0);

			for (int l = 0; l <= sum; ++l) {
				if (!f[l]) {
					continue;
				}
				int r = sum - l;

				if (l == 0 || x <= lowbit(l)) {
					int nl = l + x;
					if (!g[nl]) {
						g[nl] = 1;
						pre[(i + 1) * W + nl] = l;
						opt[(i + 1) * W + nl] = 'l';
					}
				} else if (power2(l) && x > l) {
					int nl = x;
					if (!g[nl]) {
						g[nl] = 1;
						pre[(i + 1) * W + nl] = l;
						opt[(i + 1) * W + nl] = 'l';
					}
				}

				if (r == 0 || x <= lowbit(r)) {
					int nr = r + x;
					int nl = l;
					if (highbit(nr) >= highbit(l)) {
						nl += highbit(nr);
					}
					if (!g[nl]) {
						g[nl] = 1;
						pre[(i + 1) * W + nl] = l;
						opt[(i + 1) * W + nl] = 'r';
					}
				}
			}

			sum += x;
			f.swap(g);
		}

		if (!f[S]) {
			puts("no");
			continue;
		}

		string ans(n, 'l');
		int l = S;
		for (int i = n; i >= 2; --i) {
			ans[i - 1] = opt[i * W + l];
			l = pre[i * W + l];
		}

		puts(ans.c_str());
	}
	return 0;
}
