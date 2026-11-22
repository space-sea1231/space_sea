#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;

int T;
int n;
int a[N];
vector<int> e[N];

void Solve() {
	cin >> n;
	bool flagB = true;
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
		if (u != 1 || v != i + 1) flagB = false;
	}
	// if (T != 2) return;
	if (flagB) {
		int cnt = 0, cnt1 = 0;
		ll sum = 0;
		bool flag = false;
		for (int i = 2; i <= n; i++) {
			if (a[i] > 0) {
				cnt++;
				sum += a[i];
			}
			if (a[i] < 0) flag = true;
			if (a[i] == 0) cnt1++;
		}
		if (sum > a[1]) printf("%d\n", cnt + 1 - cnt1);
		else if (sum == a[1]) printf("%d\n", flag);
		else printf("%d\n", cnt + 1 + (cnt1 || flag));
		// cerr << a[1] << " " << sum <<" " << cnt << "\n";
	}
}
signed main() {
	freopen("night.in", "r", stdin);
	freopen("night.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) Solve();
	return 0;
}
/*
我们烧去旧日历 又写下新一页
相信借诗文书卷 也能重建新世间
我不信命运 我不问苍天
若浪潮将席卷 / 春风将停歇
终将越过堇青色之夜 / 明日再相见
*/