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

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int T;
int n;
int a[N];
int f[N][2], g[N];
int F[N][2], G[N];
vector<int> e[N];

void Dfs(int u, int fa) {
	f[u][0] = 0, f[u][1] = a[u]; g[u] = 1;
	for (int v : e[u]) {
		if (v == fa) continue;
		Dfs(v, u);
		// cerr << u << " " << v << "\n";
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
		if (f[v][0] < f[v][1]) g[u] += g[v];
	}
}
void Dfs1(int u, int fa) {
	if (fa) {
		int d1 = F[fa][1] - f[u][0];
		int d0 = F[fa][0] - max(f[u][0], f[u][1]);
		F[u][0] = f[u][0] + max(d0, d1);
		F[u][1] = f[u][1] + d0;
		G[u] = g[u];
		if (d0 < d1) G[u] += G[fa] - (f[u][0] < f[u][1] ? g[u] : 0);
	} else {
		F[u][0] = f[u][0];
		F[u][1] = f[u][1];
		G[u] = g[u];
	}
	for (int v : e[u]) {
		if (v == fa) continue;
		Dfs1(v, u);
	}
}
void Solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	Dfs(1, 0); Dfs1(1, 0);
	int ans = 0;
	// for (int i = 1; i <= n; i++) printf("f[%d]=%d,%d\n", i, f[i][0], f[i][1]);
	for (int i = 1; i <= n; i++) if (F[i][0] != F[i][1]) ans = max(ans, G[i]);
	printf("%lld\n", ans);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) Solve();
	return 0;
}
/*
A hot drink in clod hands holds the morning still.
冷手里捧一杯热饮，清晨就停止了
*/

