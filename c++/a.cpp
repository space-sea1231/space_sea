#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;
typedef __int128_t i128;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int t, n;
ll ans;
ll a[N], b[N], f[N];
ll suma[N], sumb[N];
vector<int> e[N];
// struct Node {
// 	int a, b;
// 	bool operator<(const Node src) const {
// 		return a * src.b > src.a * b;
// 	}
// };
// bool cmp(int a, int b) {
// 	return suma[a] * sumb[b] > suma[b] * sumb[a];
// }
struct cmp{
    bool operator()(int a, int b){
        return suma[a] * sumb[b] < suma[b] * sumb[a];
    }
};
priority_queue<int, vector<int>, cmp> q;

void Dfs(int u) {
	// printf("Debug:%d\n", u);
	for (auto v:e[u]) {
		q.push(v);
	}
	while (!q.empty()) {
		int v = q.top(); q.pop();
		// printf("u=%d v=%d ", u, v);
		ans += sumb[u] * suma[v];
		// printf("sumb[%d]=%d suma[%d]=%d\n", u, sumb[u], v, suma[v]);
		sumb[u] += sumb[v]; suma[u] += suma[v];
	}
	for (auto v:e[u]) {
		suma[v] = suma[u];
		sumb[v] = sumb[u]; 
		Dfs(v);
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n;
		ans = 0;
		for (int i = 0; i <= n; i++) e[i].clear();
		for (int i = 1; i <= n; i++) {cin >> a[i]; suma[i] = a[i];}
		for (int i = 1; i <= n; i++) {cin >> b[i]; sumb[i] = b[i];}
		for (int i = 1; i <= n; i++) {
			cin >> f[i];
			// printf("f[%d]=%d\n", i, f[i]);
			e[f[i]].emplace_back(i);
		}
		Dfs(1);
		printf("%lld\n", ans);
	}
	// q.push((Node){1, 2});
	// q.push((Node){1, 3});
	// printf("%d %d\n", q.top().a, q.top().b);
	return 0;
}