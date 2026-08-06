#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;

int n, m;
struct Node {
	int l, r;
	bool flag;
}; Node node[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i <= n; i++) {
		node[i].l = i - 1, node[i].r = i + 1;
		node[i].flag = true;
	}
	for (int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, y;
			cin >> x >> y;
			if (x == y) continue;
			node[node[x].l].r = node[x].r;
			node[node[x].r].l = node[x].l;
			node[x].l = node[y].l, node[x].r = y;
			node[node[y].l].r = x, node[y].l = x;
		}
		if (opt == 2) {
			int x, y;
			cin >> x >> y;
			if (x == y) continue;
			node[node[x].l].r = node[x].r;
			node[node[x].r].l = node[x].l;
			node[x].r = node[y].r, node[x].l = y;
			node[node[y].r].l = x, node[y].r = x;
		}
		if (opt == 3) {
			int x;
			cin >> x;
			if (!node[x].flag) continue;
			node[node[x].l].r = node[x].r;
			node[node[x].r].l = node[x].l;
			node[x].flag = false;
		}
	}
	if (node[0].r > n) printf("Empty!\n");
	else for (int i = 0; i = node[i].r, i <= n; ) printf("%d ", i);
	return 0;
}