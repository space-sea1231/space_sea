#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;

int c, T, n;
ll d;
int lst[N], nxt[N];
ll a[N];
ll f[N], g[N], h[N];

void Solve() {
	cin >> n >> d;
	int L = 1, R = 1;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		while (a[i] - a[L] > d) L++;
		while (R < n && a[R + 1] - a[i] <= d) R++;
		lst[i] = L, nxt[i] = R;
		f[i] = h[i] = g[i] = 0;
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		int l = lst[i], r = nxt[i];
		if (l < i) ans += g[l];
		if (l + 1 < i) ans += h[l + 1];
		if (i == r) continue;
		f[r]++;
		if (lst[r] == i) f[r] += f[i], g[r] += g[i];
		if (lst[r] == i - 1) g[r] += h[i];
		if (r - 1 > i) {
			h[r]++;
			if (lst[r - 1] == i) h[r] += f[i];
		}
	}
	printf("%lld\n", ans);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> c >> T;
	while (T--) Solve();
	return 0;
}
/*
A warm scarf can hold a whole day`s courage
一条暖围巾,能装下一整天的勇气
*/