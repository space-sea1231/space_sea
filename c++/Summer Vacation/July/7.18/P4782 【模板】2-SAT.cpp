#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;

int n, m;
int num, cnt;
int low[N], dfn[N];
int color[N];
bool vis[N];
vector<int> e[N];
stack<int> q;

void Tarjan(int u) {
	dfn[u] = low[u] = ++num;
	vis[u] = true; q.push(u);
	for (auto v:e[u]) {
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		cnt++;
		do {
			u = q.top(); q.pop();
			color[u] = cnt;
			vis[u] = false;
		} while (low[u] != dfn[u]);
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, a, v, b;
		cin >> u >> a >> v >> b;
		e[u + n * (a & 1)].emplace_back(v + n * (b ^ 1));
		e[v + n * (b & 1)].emplace_back(u + n * (a ^ 1));
	}
	// printf("Debug3: ");
	// for (auto v:e[3]) printf("%d ", v);
	// printf("\n");
	// printf("Debug6: ");
	// for (auto v:e[6]) printf("%d ", v);
	// printf("\n");
	for (int i = 1; i <= (n << 1); i++) if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= n; i++) {
		if (color[i] == color[i + n]) {// 如果是1 a+n为u a为v
			printf("IMPOSSIBLE\n");
			return 0;
		} 
	}
	for (int i = 1; i <= (n << 1); i++) printf("color[%d]=%d\n", i, color[i]);
	printf("POSSIBLE\n");
	for (int i = 1; i <= n; i++) printf("%d ", color[i] < color[i + n]);
	return 0;
}