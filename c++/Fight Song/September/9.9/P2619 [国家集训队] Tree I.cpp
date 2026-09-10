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

int n, m, k;
int cnt;
int fa[N];
bool flag;
struct Edge {
	int u, v, w;
	bool o;

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
		if (p1->w < p0->w + del) {
			*p = *p1;
			p++, p1++;
		} else {
			*p = *p0;
			p++, p0++;
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
	for (int i = 0; i <= n; i++) fa[i] = i;
	for (int i = 0; i < m; i++) {
		int fu = Find(edge[i].u);
		int fv = Find(edge[i].v);
		if (fu == fv) continue;
		fa[fu] = fv;
		rev += edge[i].w;
		tot++;
		if (!edge[i].o) cnt++;
	}
	if (tot == n - 1 && cnt <= k) flag = true;
	// if (tot == n - 1 && cnt <= k) flag1 = true;
	// cerr<<cnt << " " << rev << endl;
	return rev;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	edge.resize(m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		bool o;
		cin >> u >> v >> w >> o;
		if (o) edge1.emplace_back((Edge){u, v, w, o});
		else edge0.emplace_back((Edge){u, v, w, o});
	}
	sort(edge1.begin(), edge1.end());
	sort(edge0.begin(), edge0.end());
	int l = -1e6, r = 1e6;
	ll ans;
	while (l <= r) {
		cnt = 0;
		int mid = (l + r) >> 1;
		// cerr<<mid<<endl;
		Merge(mid);
		ll cur = Kruskal();
		if (cnt >= k) {
			l = mid + 1;
			ans = cur + 1LL * mid * (cnt - k);
		} else r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}