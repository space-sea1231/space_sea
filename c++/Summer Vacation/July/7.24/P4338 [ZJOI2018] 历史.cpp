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

int n, m;
ll ans;
ll a[N];
vector<int> e[N];
namespace LCT {
	struct Node {
		ll son, siz, aux;
		int fa, ch[2];
	}; Node node[N << 1];
	
	void Dfs(int u, int fa) {
		ll p = 0, maxn = a[u];
		node[u].siz = a[u];
		node[u].fa = fa;
		for (auto v:e[u]) {
			if (v == fa) continue;
			Dfs(v, u);
			node[u].siz += node[v].siz;
			if (maxn < node[v].siz) maxn = node[p = v].siz;
		}
		ans += min(node[u].siz - 1, 2 * (node[u].siz - maxn));
		if (maxn * 2 > node[u].siz) node[u].ch[1] = p;
		node[u].aux = node[u].siz - a[u] - node[node[u].ch[1]].siz;
	}
	bool Nroot(int x) {
		return node[node[x].fa].ch[0] == x || node[node[x].fa].ch[1] == x;
	}
	void Up(int x) {
		node[x].siz = node[node[x].ch[0]].siz + node[node[x].ch[1]].siz + node[x].aux + a[x];
	}
	void Rotate(int x) {
		int y = node[x].fa, z = node[y].fa;
		bool k = node[y].ch[1] == x;
		int w = node[x].ch[k ^ 1];
		if (Nroot(y)) node[z].ch[node[z].ch[1] == y] = x;
		node[x].ch[k ^ 1] = y;
		node[y].ch[k] = w;
		if (w) node[w].fa = y;
		node[y].fa = x, node[x].fa = z;
		Up(y);
	}
	void Splay(int x) {
		while (Nroot(x)) {
			int y = node[x].fa, z = node[y].fa;
			if (Nroot(y)) Rotate((node[z].ch[1] == y) ^ (node[y].ch[1] == x) ? x : y);
			Rotate(x);
		}
		Up(x);
	}
	ll Calc(int u, ll total, ll weight) {
		if (node[u].ch[1]) return 2 * (total - weight);
		if (2 * a[u] > total) return 2 * (total - a[u]);
		return total - 1;
	}
	void Access(int u, int w) {
		int v;
		for (u = node[v = u].fa; u; u = node[v = u].fa) {
			Splay(u);
			ll total = node[u].siz - node[node[u].ch[0]].siz;
			ll weight = node[node[u].ch[1]].siz;
			ans -= Calc(u, total, weight);
			node[u].siz += w, node[u].aux += w, total += w;
			if (weight * 2 <= total) node[u].aux += weight, node[u].ch[1] = 0;
			if (node[v].siz * 2 > total) node[u].aux -= node[v].siz, node[u].ch[1] = v, weight = node[v].siz;
			ans += Calc(u, total, weight);
			Up(u);
		}
	}
	void Update(int u, int w) {
		Splay(u);
		ll total = node[u].siz - node[node[u].ch[0]].siz;
		ll weight = node[node[u].ch[1]].siz;
		ans -= Calc(u, total, weight);
		node[u].siz += w, a[u] += w, total += w;
		if (weight * 2 <= total) node[u].aux += weight, node[u].ch[1] = 0;
		ans += Calc(u, total, weight);
		Up(u);
		Access(u, w);
	}
} using namespace LCT;
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	Dfs(1, 0); printf("%lld\n", ans);
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		Update(x, y);
		printf("%lld\n", ans);
	}

	return 0;
}