#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
// #define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 33;

int t, n;
ll ans;
ll sum1, sum2;
int a[N];
vector<ll> q[N];

void Dfs1(int dep, int cnt) {
	if (dep > (n + 1 >> 1)) {
		q[cnt].emplace_back(sum1 - sum2);
		return;
	}
	sum1 += a[dep];
	Dfs1(dep + 1, cnt + 1);
	sum1 -= a[dep], sum2 += a[dep];
	Dfs1(dep + 1, cnt);
	sum2 -= a[dep];
}
inline void Calc(int i) {
	ll val = sum2 - sum1;
	// cerr << val << "\n";
	if (q[i].empty()) return;
	vector<ll>::iterator it = lower_bound(q[i].begin(), q[i].end(), val);
	if (it == q[i].end()) {
		ans = min(ans, abs(*prev(it) - val));
		return ;
	}
	ll a = abs(*it - val);
	ll b = INF;
	if (val > 0 && it != q[i].begin()) b = abs(*prev(it) - val);
	if (val < 0 && next(it) != q[i].end()) b = abs(*next(it) - val);
	ans = min(ans, min(a, b));
}
void Dfs2(int dep, int cnt) {
	if (dep <= (n + 1 >> 1)) {
		Calc((n + 1 >> 1) - cnt);
		if (n & 1) Calc((n >> 1) - cnt);
		return ;
	}
	sum1 += a[dep];
	Dfs2(dep - 1, cnt + 1);
	sum1 -= a[dep], sum2 += a[dep];
	Dfs2(dep - 1, cnt);
	sum2 -= a[dep];
}
inline void Init() {
	ans = INF;
	for (int i = 1; i <= n; i++) q[i].clear();
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n;
		Init();
		for (int i = 1; i <= n; i++) cin >> a[i];
		Dfs1(1, 0);
		for (int i = 1; i <= n; i++) sort(q[i].begin(), q[i].end());
		// #ifdef __Debug
		// for (int v : q[2]) printf("%d ", v);
		// printf("\n");
		// #endif
		Dfs2(n, 0);
		printf("%lld\n", ans);
	}
	return 0;
}