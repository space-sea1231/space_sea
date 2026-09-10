#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
// #include <random>
// #include <chrono>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e3 + 10;

// mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
// inline int Random(int l, int r) { return Rand() % (r - l + 1) + l; }

int n, m, k;
int fa[N];
bool flag, flag1;
struct Edge {
	int u, v;
	double w;
	int id;

	bool operator<(const Edge &s) const {
		return w < s.w;
	}
};
vector<Edge> edge0, edge1, edge;

inline int Find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = Find(fa[x]);
}
void Merge(ll del) {
	// vector<Edge>::iterator p0 = edge0.begin(), p1 = edge1.begin(), p = edge.begin();
	// while (p0 != edge0.end() && p1 != edge1.end()) {
	// 	if (p0->w < p1->w + del || (p0->w == p1->w + del && Random(0, 1))) {
	// 		*p = *p0;
	// 		p++, p0++;
	// 	} else {
	// 		*p = *p1;
	// 		p++, p1++;
	// 	}
	// }
	// while (p0 != edge0.end()) {
	// 	*p = *p0;
	// 	p++, p0++;
	// }
	// while (p1 != edge1.end()) {
	// 	*p = *p1;
	// 	p++, p1++;
	// }
	vector<Edge>::iterator p0 = edge0.begin(), p1 = edge1.begin(), p = edge.begin();
	while (p1 != edge1.end()) {
		*p = *p1;
		p->w += del / 100000.0;
		p++, p1++;
	}
	while (p0 != edge0.end()) {
		*p = *p0;
		p++, p0++;
	}
	sort(edge.begin(), edge.end());
}
bool Kruskal(ll del) {
	Merge(del);
	int cnt = 0;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 0; i < m; i++) {
		int fu = Find(edge[i].u);
		int fv = Find(edge[i].v);
		if (fu == fv) continue;
		fa[fu] = fv;
		// tot++;
		if (edge[i].u == 1 || edge[i].v == 1) cnt++;
	}
	// if (tot == n - 1 && cnt <= k) flag = true;
	return cnt <= k;
	// if (tot == n - 1 && cnt <= k) flag1 = true;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	edge.resize(m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		if (u == 1 || v == 1) edge1.emplace_back((Edge){u, v, w, i});
		else edge0.emplace_back((Edge){u, v, w, i});
	}
	// sort(edge1.begin(), edge1.end());
	// sort(edge0.begin(), edge0.end());
	ll l = -1e16, r = 1e16;
	ll ans = r;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (Kruskal(mid)) {
			r = mid - 1;
			ans = mid;
		} else l = mid + 1;
	}
	// if (!flag || (int)edge1.size() < k) printf("-1\n");
	if (!Kruskal(ans)) {
		printf("-1\n");
		return 0;
	}
	// cerr<<ans;
	printf("%d\n", n - 1);
	Merge(ans);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 0; i < m; i++) {
		int fu = Find(edge[i].u);
		int fv = Find(edge[i].v);
		if (fu == fv) continue;
		fa[fu] = fv;
		printf("%d ", edge[i].id);
	}
	return 0;
}