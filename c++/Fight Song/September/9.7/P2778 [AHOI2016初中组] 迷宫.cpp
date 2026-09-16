#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
// #include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const double INF = 1e9;
const int N = 8e3 + 10;
const int K = 20;

int n, m;
int fa[N][K], dep[N];
vector<int> e[N];

struct Node {
	int x, y, r;
	int id;

	bool operator<(const Node &s) const { return r > s.r; }
}; Node node[N];

inline ll Dist(Node i, Node j) {
	ll x = i.x - j.x;
	ll y = i.y - j.y;
	return sqrt(x * x + y * y);
}
void Dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	for (int v : e[u]) {
		if (v == f) continue;
		for (int i = 1; i < K; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
		Dfs(v, u);
	}
}
int Lca(int x, int y) {
	int cnt = 0;
	if (dep[x] < dep[y]) swap(x, y);
	if (x == 0 && y == 0) return 0;
	if (y == 0) {
		for (int i = K - 1; ~i; i--) {
			if (fa[x][i] != 0) {
				// cerr << fa[x][i] << " " << dep[fa[x][i]] << " " << i << endl;
				x = fa[x][i];
				cnt += (1 << i);
			}
		}
		return cnt + 1;
	}
	for (int i = K - 1; ~i; i--) {
		if (dep[fa[x][i]] >= dep[y]) {
			// cerr << fa[x][i] << " " << dep[fa[x][i]] << " " << y << " " << dep[y] << endl;
			x = fa[x][i];
			cnt += (1 << i);
		}
	}
	if (x == y) return cnt;
	for (int i = K - 1; ~i; i--) {
		if (fa[x][i] != fa[y][i]) {
			// cerr << fa[x][i] << " " << dep[fa[x][i]] << " " << y << " " << dep[y] << endl;
			x = fa[x][i];
			y = fa[y][i];
			cnt += (1 << i + 1);
		}
	}
	return cnt + 2;
}
inline int Find(int x, int y) {
	for (int i = n; i; i--) {
		ll aaa = Dist(node[i], (Node){x, y});
		// if (x == 0 && y == 0) printf("Debug: i=%d %d %.2lf\n\n", i, node[i].r, aaa);
		if (node[i].r > aaa) {
			// printf("%d\n", i);
			return i;
		}
	}
	return 0;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) fa[i][0] = i;
	for (int i = 1; i <= n; i++) {
		cin >> node[i].x >> node[i].y >> node[i].r;
		node[i].id = i;
	}
	sort(node + 1, node + n + 1);
	for (int i = 1; i <= n; i++) {
		ll cur = INF;
		for (int j = 1; j < i; j++) {
			int dis = node[i].r + Dist(node[i], node[j]);
			if (node[j].r >= dis && cur >= dis) {
				cur = dis;
				// fa[node[i].id][0] = node[j].id;
				fa[i][0] = j;
			
			}
		}
	}
	for (int i = 1; i <= n; i++) e[fa[i][0] == i ? fa[i][0] = 0 : fa[i][0]].emplace_back(i);
	Dfs(0, 0); dep[0] = -1;
	// cerr<<dep[0] << " " << dep[2] << endl;
	// printf("%d\n", Lca(1, 3));
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int sx, sy, fx, fy;
		cin >> sx >> sy >> fx >> fy;
		int x = Find(sx, sy);
		int y = Find(fx, fy);
		// cerr<<x << " " << y << endl;
		// cerr<<dep[x] << " " << dep[y] << endl << endl;
		printf("%d\n", Lca(x, y));
	}
	// cerr<<node[3].x << endl;
	// for (int i = 1; i <= n; i++) printf("%d fa[%d]=%d\n", i, node[i].id, fa[node[i].id]);
	return 0;
}