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
const int N = 2e2 + 10;

int t;
int n, m;
int num, top, col;
int dfn[N], low[N];
int stk[N], color[N];
bool vis[N];
vector<int> e[N];

void Tarjan(int u) {
	dfn[u] = low[u] = ++num;
	stk[++top] = u, vis[u] = true;
	for (auto v:e[u]) {
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int cur; col++;
		do {
			cur = stk[top--];
			color[cur] = col; vis[cur] = false;
		} while (cur != u);
	}
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n * 2; i++) {
			dfn[i] = low[i] = 0;
			num = col = 0;
			e[i].clear();
		}
		for (int i = 1; i <= m; i++) {
			char cu, cv;
			int u, v;
			cin >> cu >> u >> cv >> v;
			bool a = cu == 'm', b = cv == 'm';
			e[u + n * a].emplace_back(v + n * (b ^ 1));
			e[v + n * b].emplace_back(u + n * (a ^ 1));
			// printf("%d -> %d\n", u + n * a, v + n * (b ^ 1));
			// printf("%d -> %d\n", u + n * b, v + n * (a ^ 1));
		}
		for (int i = 1; i <= n * 2; i++) if (!dfn[i]) Tarjan(i);
		// for (int i = 1; i <= n * 2; i++) printf("color[%d]=%d\n", i, color[i]);
		bool flag = true;
		for (int i = 1; i <= n; i++) if (color[i] == color[i + n]) flag = false;
		if (flag) printf("GOOD\n");
		else printf("BAD\n");
	}
	return 0;
}