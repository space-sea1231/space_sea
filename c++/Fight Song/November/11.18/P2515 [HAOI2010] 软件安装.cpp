#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e2 + 10;
const int M = 5e2 + 10;

int n, m;
int cnt, num;
int wei[N], val[N];
int f[N][M], fa[N];
int loop[N];
bool vis[N], in[N];
int head[N], to[N], nxt[N];
int fa1[N];
vector<int> e[N];
stack<int> st;

void Add(int u, int v) {
	to[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
int Find(int x) {
	if (fa1[x] == x) return x;
	return fa1[x] = Find(fa1[x]);
}
bool flag;
void Topu(int u) {
	in[u] = true; 
	st.push(u);
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (vis[v]) continue;
		if (in[v]) {
			num++;
			while (st.top() != v) {
				wei[num + n] += wei[st.top()];
				val[num + n] += val[st.top()];
				loop[st.top()] = num + n;
				vis[st.top()] = true;
				st.pop();
			}
			wei[num + n] += wei[st.top()];
			val[num + n] += val[st.top()];
			loop[st.top()] = num + n;
			vis[st.top()] = true;
			st.pop();
			flag = true;
			return ;
		}
		Topu(v);
		if (flag) return ;
	}
	vis[u] = true;
	st.pop();
}
void Dfs(int u, int siz) {
	// cerr << u << " " <<siz << "\n";
	for (int i = wei[u]; i <= siz; i++)  f[u][i] = val[u];
	for (int v : e[u]) Dfs(v, siz - wei[u]);
	for (int v : e[u]) {
		for (int k = siz; k >= wei[u] + wei[v]; k--) {
			for (int j = wei[v]; j <= k - wei[u]; j++) {
				f[u][k] = max(f[u][k], f[u][k - j] + f[v][j]);
			}
		}
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> wei[i];
	for (int i = 1; i <= n; i++) cin >> val[i];
	for (int i = 1; i <= n; i++) {
		loop[i] = i;
		cin >> fa[i];
		if (fa[i]) Add(fa[i], i);
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			while (!st.empty()) st.pop();
			flag = false;
			Topu(i);
		}
	}
	// for (int i = 1; i <= n + num; i++) vis[i] = false;
	for (int i = 1; i <= n + num; i++) fa1[i] = i;
	// for (int i = 1; i <= n; i++) printf("Debug:loop[%d]=%d\n", i, loop[i]);
	for (int i = 1; i <= n; i++) {
		if (loop[fa[i]] == loop[i]) continue;
		// cerr << loop[fa[i]] << " " << loop[i] << "\n";
		e[loop[fa[i]]].emplace_back(loop[i]);
		fa1[Find(loop[i])] = Find(loop[fa[i]]);
	}
	// cerr << wei[0] << " " << val[0] << "\n";
	for (int i = 1; i <= n; i++) {
		if (Find(loop[i])) {
			e[0].emplace_back(Find(loop[i]));
			fa1[Find(loop[i])] = 0;
			// cerr << 0 << " " << loop[i] << "\n";
		}
	}
	Dfs(0, m);
	int ans = 0;
	for (int i = 1; i <= m; i++) ans = max(ans, f[0][i]);
	printf("%d\n", ans);
	return 0;
}
/*
Keep a warm pocket and a worm heart.
口袋要暖，心更要暖。

昨晚梦到大胃王比赛了喵
第三份菜是酸的
我是...女的？
*/