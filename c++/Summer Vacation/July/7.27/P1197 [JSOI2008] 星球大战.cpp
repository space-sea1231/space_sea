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
const int N = 4e5 + 10;

int n, m, k;
int cnt;
int fa[N];
int q[N], ans[N];
bool vis[N];
vector<int> e[N];

int Find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = Find(fa[x]);
}
void Merge(int u, int v) {
	int fu = Find(u), fv = Find(v);
	if (fv != fu) {
		fa[fv] = fu, cnt--;
		// cerr<<u<<" "<<v<<endl;
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v; u++, v++;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	cin >> k;
	for (int i = 1; i <= k; i++) {
		int u;
		cin >> u; u++;
		q[i] = u; vis[u] = true;
	}
	cnt = n - k;
	for (int u = 1; u <= n; u++) {
		if (!vis[u]) {
			for (auto v:e[u]) {
				if (vis[v]) continue;
				Merge(u, v);
			}
		}
	}
	ans[k + 1] = cnt;
	// cerr<<"---------\n";
	for (int i = k, u = q[i]; i; u = q[--i]) {
		cnt++;
		for (auto v:e[u]) {
			if (vis[v]) continue;
			Merge(u, v);
		}
		vis[u] = false;
		ans[i] = cnt;
	}
	for (int i = 1; i <= k + 1; i++) printf("%d\n", ans[i]);
	return 0;
}