#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;

ll n, m;
ll ans;
ll a[N], sum[N];

void Dfs(int cur, ll tot) {
	if (tot > m) return;
	if (tot + sum[cur - 1] <= m) {
		ans = max(ans, tot + sum[cur - 1]);
		return ;
	}
	ans = max(ans, tot);
	for (int i = 1; i < cur; i++) Dfs(i, tot + a[i]);
}
signed main() {				
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	Dfs(n + 1, 0);
	printf("%lld\n", ans);
	return 0;
}