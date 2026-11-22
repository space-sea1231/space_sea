#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;

int T;
int n, m;
int disA[N], disB[N];
bool vis[N];

struct Edge {
	int v;
	int vala, valb;
};
vector<Edge> e[N];

struct Edge1 {
	int u, wa, wb;

	bool operator<(const Edge1 &s) const {
		if (wa == s.wa) return wb > s.wb;
		return wa > s.wa;
	}
};

struct Edge2 {
	int u, wa, wb;

	bool operator<(const Edge2 &s) const {
		return ((ll)wa * wb > (ll)s.wa * s.wb);
	}
};

// bool CmpA(const Edge &a, const Edge &b) {
// 	return a.vala < b.vala;
// }
// bool CmpB(const Edge &a, const Edge &b) {
// 	return a.valb < b.valb;
// }
// bool CmpC(const Edge &a, const Edge &b) {
// 	return (ll)a.valb * a.vala < (ll)b.valb * b.valb;
// }
pair<int, int> Min(pair<int, int> a, pair<int, int> b) {
	if ((ll)a.first * a.second < (ll)b.first * b.second) return a;
	return b;
}

pair<int, int> DijsktraA() {
	for (int i = 1; i <= n; i++) {
		vis[i] = false;
		disA[i] = disB[i] = INF;
	}
	priority_queue<Edge1> q;
	q.push((Edge1){1, 0, 0});
	disA[1] = disB[1] = 0;
	while(!q.empty()) {
		Edge1 cur = q.top(); q.pop();
		if (cur.u == n) return make_pair(disA[n], disB[n]);
		if (vis[cur.u]) continue;
		vis[cur.u] = true;
		for (auto [v, vala, valb] : e[cur.u]) {
			if (disA[v] > disA[cur.u] + vala || (disA[v] == disA[cur.u] + vala && disB[v] > disB[cur.u] + valb)) {
				disA[v] = disA[cur.u] + vala;
				disB[v] = disB[cur.u] + valb;
				q.push((Edge1){v, disA[v], disB[v]});
			}
		}
	}
	return make_pair(INF, INF);
}
pair<int, int> DijsktraB() {
	for (int i = 1; i <= n; i++) {
		vis[i] = false;
		disA[i] = disB[i] = INF;
	}
	priority_queue<Edge1> q;
	q.push((Edge1){1, 0, 0});
	disA[1] = disB[1] = 0;
	while(!q.empty()) {
		Edge1 cur = q.top(); q.pop();
		if (cur.u == n) return make_pair(disA[n], disB[n]);
		if (vis[cur.u]) continue;
		vis[cur.u] = true;
		for (auto [v, vala, valb] : e[cur.u]) {
			if (disB[v] > disB[cur.u] + valb || (disB[v] == disB[cur.u] + valb && disA[v] > disA[cur.u] + vala)) {
				disA[v] = disA[cur.u] + vala;
				disB[v] = disB[cur.u] + valb;
				q.push((Edge1){v, disB[v], disA[v]});
			}
		}
	}
	return make_pair(INF, INF);
}
pair<int, int> DijsktraC() {
	for (int i = 1; i <= n; i++) {
		vis[i] = false;
		disA[i] = disB[i] = INF;
	}
	priority_queue<Edge2> q;
	q.push((Edge2){1, 0, 0});
	disA[1] = disB[1] = 0;
	while(!q.empty()) {
		Edge2 cur = q.top(); q.pop();
		if (cur.u == n) return make_pair(disA[n], disB[n]);
		if (vis[cur.u]) continue;
		vis[cur.u] = true;
		for (auto [v, vala, valb] : e[cur.u]) {
			if ((ll)disA[v] * disB[v] > (ll)(disA[cur.u] + vala) * (disB[cur.u] + valb)) {
				disA[v] = disA[cur.u] + vala;
				disB[v] = disB[cur.u] + valb;
				q.push((Edge2){v, disA[v], disB[v]});
			}
		}
	}
	return make_pair(INF, INF);
}
void Solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i <= m; i++) {
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		e[u].emplace_back((Edge){v, a, b});
	}
	pair<int, int> ansA = DijsktraA();
	pair<int, int> ansB = DijsktraB();
	pair<int, int> ansC = DijsktraC();

	pair<int, int> ans = Min(ansA, Min(ansB, ansC));
	if (ans.first == INF) printf("%lld %lld\n", (ll)1e18, (ll)1e18);
	else printf("%d %d\n", ans.first, ans.second);
	// for (int i = 1; i <= n; i++) sort(e[i].begin(), e[i].end(), CmpA);
	// pair<int, int> ansC = Dijsktra();
}
signed main() {
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	// priority_queue<Edge1> q;
	// q.push((Edge1){1, 222, 1});
	// q.push((Edge1){2, 122, 1});
	// printf("%d", q.top().u);
	// return 0;
	cin >> T;
	while (T--) Solve();
	return 0;
}