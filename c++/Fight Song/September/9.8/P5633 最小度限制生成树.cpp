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
const int N = 5e4 + 10;

int n, m, s, k;
int cnt;
int fa[N];
bool flag;
struct Edge {
	int u, v, w;

	bool operator<(const Edge &s) const {
		return w < s.w;
	}
};
vector<Edge> edge0, edge1, edge;

inline int Find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = Find(fa[x]);
}
void Merge(int del) {
	vector<Edge>::iterator p0 = edge0.begin(), p1 = edge1.begin(), p = edge.begin();
	while (p0 != edge0.end() && p1 != edge1.end()) {
		if (p0->w < p1->w + del) {
			*p = *p0;
			p++, p0++;
		} else {
			*p = *p1;
			p++, p1++;
		}
	}
	while (p0 != edge0.end()) {
		*p = *p0;
		p++, p0++;
	}
	while (p1 != edge1.end()) {
		*p = *p1;
		p++, p1++;
	}
}
ll Kruskal() {
	ll rev = 0;
	int tot = 0;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 0; i < m; i++) {
		int fu = Find(edge[i].u);
		int fv = Find(edge[i].v);
		if (fu == fv) continue;
		fa[fu] = fv;
		rev += edge[i].w;
		tot++;
		if (edge[i].u == s || edge[i].v == s) cnt++;
	}
	if (tot == n - 1 && cnt <= k) flag = true;
	// if (tot == n - 1 && cnt <= k) flag1 = true;
	return rev;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> s >> k;
	edge.resize(m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		if (u == s || v == s) edge1.emplace_back((Edge){u, v, w});
		else edge0.emplace_back((Edge){u, v, w});
	}
	sort(edge1.begin(), edge1.end());
	sort(edge0.begin(), edge0.end());
	int l = -1e6, r = 1e6;
	ll ans = 0;
	while (l <= r) {
		cnt = 0;
		int mid = (l + r) >> 1;
		Merge(mid);
		ll cur = Kruskal();
		if (cnt >= k) {
			l = mid + 1;
			ans = cur + 1LL * mid * (cnt - k);
		} else r = mid - 1;
	}
	if (!flag || (int)edge1.size() < k) printf("Impossible\n");
	else printf("%lld\n", ans);
	return 0;
}