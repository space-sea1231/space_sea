#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 1e5 + 10;

int c, T;
int n;
ll mid;
ll a[N];
vector<int> e[N];

struct Function {
	int del;
	ll val;

 	bool operator < (const Function &s) const {
        if (del != s.del) return del < s.del;
        return val < s.val;
    }
	bool operator == (const Function &s) const {
        if (del != s.del) return false;
        if (val != s.val) return false;
        return true;
    }
    Function& operator += (const Function &s) {
        del += s.del;
        val += s.val;
        return *this;
    }
	Function operator + (const Function &s) {
        return (Function){del + s.del, val + s.val};
    }
}; Function f[N][2];
void Dfs(int u, int fa) {
	f[u][0] = {0, a[u]};
	f[u][1] = {-N, 0};

	for (int v : e[u]) {
		if (v == fa) continue;
		Dfs(v, u);

		int c0 = f[v][0].del + (f[v][0].val >= mid ? 1 : -1);
		int c1 = f[v][1].del + (f[v][1].val >= mid ? 1 : -1);

		Function nxt[2];
		nxt[0] = nxt[1] = {-N, 0};

		if (f[u][0].del > -N / 2 && f[v][0].del > -N / 2)
			nxt[0] = max(nxt[0], f[u][0] + f[v][0]);
		if (f[u][1].del > -N / 2 && f[v][1].del > -N / 2)
			nxt[0] = max(nxt[0], f[u][1] + f[v][1]);
		if (f[u][0].del > -N / 2 && f[v][1].del > -N / 2)
			nxt[1] = max(nxt[1], f[u][0] + f[v][1]);
		if (f[u][1].del > -N / 2 && f[v][0].del > -N / 2)
			nxt[1] = max(nxt[1], f[u][1] + f[v][0]);

		if (f[u][0].del > -N / 2 && f[v][0].del > -N / 2)
			nxt[1] = max(nxt[1], {f[u][0].del + c0, f[u][0].val});
		if (f[u][1].del > -N / 2 && f[v][1].del > -N / 2)
			nxt[1] = max(nxt[1], {f[u][1].del + c1, f[u][1].val});
		if (f[u][0].del > -N / 2 && f[v][1].del > -N / 2)
			nxt[0] = max(nxt[0], {f[u][0].del + c1, f[u][0].val});
		if (f[u][1].del > -N / 2 && f[v][0].del > -N / 2)
			nxt[0] = max(nxt[0], {f[u][1].del + c0, f[u][1].val});

		f[u][0] = nxt[0];
		f[u][1] = nxt[1];
	}
}
bool Check() {
	Dfs(1, 0);
	return f[1][0].del + (f[1][0].val >= mid ? 1 : -1) >= 1;
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
	ll l = -INF, r = INF, ans = 0;
	while (l <= r) {
		mid = l + r >> 1;
		if (Check()) {
			l = mid + 1;
			ans = mid;
		} else r = mid - 1;
	}
	// mid = 4;
	// Check();
	// for (int i = 1; i <= n; i++) printf("f[%d][0] = {%d, %d} f[%d][1] = {%d, %d}\n", i, f[i][0].del, f[i][0].val, i, f[i][1].del, f[i][1].val);
	printf("%lld\n", ans);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> c >> T;
	while (T--) Solve();
	return 0;
}
/*
我们收容，我们控制，我们保护。
我们生于黑暗，死于混沌。我们探索黑暗，为了无限光明。
我们不能退缩，因为我们背后是全人类，若当一日收容失败，即为地狱大门敞开之日。
向赴死之人致敬！------scp基金会

基金会与你同行，信息与你无限，
死亡在前，家在身后，档案封存，真相静默，
你我在暗，守光之人，异常无声，收容有序，
基金会在影，世界在光，守望无声，却抵万物，恐惧有形，责任无形，
锁链一道人间一夜，若失败无人.

谎言作盾，偏执为枪。
人间无恙，我辈皆亡。
知者缄默，见者遗忘。
以命为锁，以魂为岗。
前路无归，后无故乡。
神明陨落，秩序登场。
白昼安稳，黑夜奔忙。
心有烈焰，面如寒霜。
守着混沌，护着寻常。

我们不会再退回到黑暗、蒙昧、恐怖的夜晚。
我们不会被未知所驾驭。我们不能再度生活在恐惧之中。
没有其他事物能保护我们，我们必须保护我们自己。
人类不能生活在恐惧之中，没有东西能保护我们，我们必须保护我们自己。
人类到如今已经繁衍了250000年，只有最近的4000年是有意义的。
*/