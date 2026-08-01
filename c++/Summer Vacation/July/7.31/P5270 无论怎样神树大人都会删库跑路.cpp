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
typedef unsigned long long ull;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int base = 1e9 + 7;

int n, t, q, m;
int r[N], rans[N];
ull d, val[N];
ull per[N];
vector<int> c[N], pre[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> t >> q;
	per[0] = 1;
	for (int i = 1; i <= 100000; i++) per[i] = per[i - 1] * base;
	for (int i = 1; i <= t; i++) {
		int x;
		cin >> x;
		d += per[x];
	}
	for (int i = 1; i <= n; i++) {
		int len;
		cin >> len;
		// c[i].resize(len);
		for (int j = 0; j < len; j++) {
			int x;
			cin >> x;
			c[i].emplace_back(x);
			val[i] += per[x];
		}
		ull cur = 0;
		for (int j = 0; j < len; j++) {
			cur += per[c[i][j]];
			pre[i].emplace_back(cur);
		}
	}
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> r[i];
	int len = 0, l = 1;
    ull sum = 0, ans = 0;
	bool flag = false;
	for (int i = 1; q; q--, i++) {
		int x = (i - 1) % m + 1;
		len += c[r[x]].size();
		sum += val[r[x]];
		while (len - (int)c[r[l]].size() >= t) {
			sum -= val[r[l]];
			len -= (int)c[r[l]].size();
			l = l % m + 1;
		}
		if (len >= t) {
			if (flag) rans[x] = rans[x - 1];
			if (sum - ((len == t) ? 0 : pre[r[l]][len - t - 1]) == d) {
				ans++; 
				if (flag) rans[x]++;
			}
		}
		if (flag && x == m) {
			q--;
			break;
		}
		if (len >= t && x == m) flag = true; 
	}
	cerr<<rans[q%m];
	ans += (ull)(q / m) * rans[m];
	ans += rans[q % m];
	printf("%u\n", ans);
	return 0;
}