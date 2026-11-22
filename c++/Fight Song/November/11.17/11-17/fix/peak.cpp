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

const ll INF = 1e18;
const int LIM = 1e9;
const int N = 2e5 + 10;

int n, m, sz;
int a[N], c[N];
int val[N];
int need[N];
ll f[N];

vector<int> srt[N], fix[N], pos[N];
vector<ll> cost[N];
vector<pair<int, int> > seg[N];

struct Limit {
	int l, r;
	int val;
}; Limit lim[N];

bool Init() {
	sort(val + 1, val + m + 1);
	sz = unique(val + 1, val + m + 1) - (val + 1);
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair< int, int> > > q;
	for (int i = 1; i <= n; i++) {
		for (int p : srt[i]) q.push(make_pair(lim[p].val, lim[p].r));
		while (!q.empty() && q.top().second < i) q.pop();
		if (q.empty()) continue;
		int up = q.top().first;
		// cerr << i << " " << a[i] << " " << up << "\n";
		if (a[i] > up) return false;
		// int up = q.empty() ? LIM : q.top().first;
		// if (a[i] > up) return false;
		// if (up == LIM) continue;

		int id = lower_bound(val + 1, val + sz + 1, up) - val;
		if (a[i] == up) {
			fix[id].emplace_back(i);
		} else {
			// cerr << id << " " << i << "\n";
			pos[id].emplace_back(i);
			cost[id].emplace_back((ll)c[i] * (up - a[i]));
		}
	}
	for (int i = 1; i <= m; i++) {
		int l = lim[i].l, r = lim[i].r, id = lower_bound(val + 1, val + sz + 1, lim[i].val) - val;
		vector<int>::iterator it = lower_bound(fix[id].begin(), fix[id].end(), l);
		if (it != fix[id].end() && *it <= r) continue;
		int x = lower_bound(pos[id].begin(), pos[id].end(), l) - pos[id].begin() + 1;
		int y = upper_bound(pos[id].begin(), pos[id].end(), r) - pos[id].begin();
		// cerr << i << " " << x << " " << y << "\n";
		if (x > y) return false;
		seg[id].emplace_back(make_pair(x, y));
	}
	return true;
}
ll Solve(int id) {
	if (seg[id].empty()) return 0;
	// cerr << id << " " << seg[id].front().first << " " << seg[id].front().second << "\n";
	int k = pos[id].size(), last = 0, l = 0;
	for (int i = 1; i <= k; i++) need[i] = 0;
	for (pair<int, int> s : seg[id]) {
		need[s.second] = max(need[s.second], s.first);
		last = max(last, s.first);
	}
	deque<int> q{0};
	for (int i = 1; i <= k; i++) {
		l = max(l, need[i - 1]);
		while (!q.empty() && q.front() < l) q.pop_front();
		f[i] = INF;
		if (q.empty()) continue;
		f[i] = f[q.front()] + cost[id][i - 1];
		while (!q.empty() && f[q.back()] > f[i]) q.pop_back();
		q.push_back(i);
	}
	return *min_element(f + last, f + k + 1);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= m; i++) {
		cin >> lim[i].l >> lim[i].r >> lim[i].val;
		val[i] = lim[i].val;
		srt[lim[i].l].emplace_back(i);
	}
	if (!Init()) {
		printf("-1\n");
		return 0;
	}
	ll ans = 0;
	for (int i = 1; i <= sz; i++) {
		ll rev = Solve(i);
		if (rev == INF) { 
			printf("-1\n");
			return 0;
		}
		ans += rev;
	}
	printf("%lld\n", ans);
	return 0;
}