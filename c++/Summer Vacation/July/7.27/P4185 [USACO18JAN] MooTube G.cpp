#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int fa[N], siz[N];
int ans[N];
struct Edge {
	int u, v, w;
	
	bool operator<(const Edge &src) const {
		return w > src.w;
	}
}; Edge e[N];
struct Question {
	int u, w;
	int id;
	
	bool operator<(const Question &src) const {
		return w > src.w;
	}
}; Question q[N];

int Find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = Find(fa[x]);
}
void Merge(int u, int v) {
	int fu = Find(u), fv = Find(v);
	if (siz[fu] < siz[fv]) swap(fu, fv);
	fa[fv] = fu, siz[fu] += siz[fv];
	// cerr<<u << " " <<fu<<endl;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) siz[i] = 1, fa[i] = i;
	for (int i = 1; i < n; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	for (int i = 1; i <= m; i++) {cin >> q[i].w >> q[i].u; q[i].id = i;}
	sort(e + 1, e + n);
	sort(q + 1, q + m + 1);
	int top = 1;
	for (int i = 1; i <= m; i++) {
		while (top < n && e[top].w >= q[i].w) {
			Merge(e[top].u, e[top].v);
			top++;
		}
		ans[q[i].id] = siz[Find(q[i].u)] - 1;
		// Debug(Find(q[i].u));
		// printf("siz[%d]=%d\n", Find(q[i].u), siz[Find(q[i].u)]);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}