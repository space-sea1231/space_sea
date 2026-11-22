#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;

const int N = 5e4 + 10;
const int K = 17;
const ll M = 1e14;

int n, m;
int a[N];
int dep[N], ed[N];
int f[N][K];
ll g[N][K];
bool vis[N];
vector<pair<int, int> > e[N];

struct Node {
	int from;   // 根的儿子编号
	ll data;    // 军队：回根后剩余时间；子树：该儿子到根的边权
} acc[N], pro[N];

int ac, pr;
bool visitNode[N];

void Dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	for (auto [v, w] : e[u]) {
		if (v == fa) continue;
		f[v][0] = u; g[v][0] = w;
		ed[u] = true;
		for (int i = 1; i < K; i++) {
			f[v][i] = f[f[v][i - 1]][i - 1];
			g[v][i] = g[v][i - 1] + g[f[v][i - 1]][i - 1];
		}
		Dfs(v, u);
	}
}

bool Dfs1(int u, int fa) {
	if (vis[u]) return true;               // 本节点有军队，整棵子树覆盖
	bool flag = true & ed[u];
	for (auto [v, w] : e[u]) {
		if (v == fa || vis[v]) continue;
		flag &= Dfs1(v, u);
	}
	if (!flag && f[u][0] == 1) {
		pro[++pr].from = u;
		pro[pr].data = g[u][0];
	}
	return flag;
}

bool cmpNode(Node x, Node y) {
	return x.data < y.data;
}

bool Check(ll mid) {
	pr = 0;
	for (int i = 1; i <= n; i++) vis[i] = false;

	vector<pair<ll, int> > arm;
	for (int i = 1; i <= m; i++) {
		int u = a[i];
		ll lst = mid;
		for (int j = K - 1; ~j; j--) {
			if (lst >= g[u][j] && f[u][j] > 1) {
				lst -= g[u][j];
				u = f[u][j];
			}
		}
		if (f[u][0] == 1) {
			if (lst >= g[u][0]) arm.push_back({lst - g[u][0], u});
			else vis[u] = true;
		} else {
			vis[u] = true;
		}
	}

	vis[1] = false;
	Dfs1(1, 0);   // 内部有 if (vis[u]) return true;

	bool inNeed[N] = {false};
	for (int i = 1; i <= pr; i++) inNeed[pro[i].from] = true;

	bool covered[N] = {false};
	vector<pair<ll, int> > freeArm;
	for (auto [rest, son] : arm) {
		if (rest < g[son][0] && inNeed[son] && !covered[son]) {
			covered[son] = true;        // 只能留守自己子树，只消耗一支
		} else {
			freeArm.push_back({rest, son});
		}
	}

	vector<pair<ll, int> > remNeed;
	for (int i = 1; i <= pr; i++) {
		if (!covered[pro[i].from]) {
			remNeed.push_back({pro[i].data, pro[i].from});
		}
	}

	sort(freeArm.begin(), freeArm.end());
	sort(remNeed.begin(), remNeed.end());

	int j = 0;
	for (int i = 0; i < (int)remNeed.size(); i++) {
		while (j < (int)freeArm.size() && freeArm[j].first < remNeed[i].first) j++;
		if (j == (int)freeArm.size()) return false;
		j++;
	}
	return true;
}

int search2(ll L, ll R) {
	while (L < R) {
		ll Mid = (L + R) >> 1;
		if (Check(Mid)) R = Mid;
		else L = Mid + 1;
	}
	return (int)L;
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].emplace_back(v, w);
		e[v].emplace_back(u, w);
	}
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> a[i];

	int cnt = 0;
	for (auto [v, w] : e[1]) cnt++;
	if (m < cnt) { printf("-1\n"); return 0; }

	Dfs(1, 0);

	// 上界：2 * 最深距离，足够覆盖“跳到根再下到另一子树”
	ll maxDis = 0;
	for (int i = 1; i <= n; i++) maxDis = max(maxDis, (ll)dep[i]); // 仅示意，真实用 dis
	ll l = 0, r = M;
	while (l < r) {
		ll mid = (l + r) >> 1;
		if (Check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", r);
	return 0;
}