#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << "\n";

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int n, m;
int a[N];
int stk[N];

namespace LCT {
	struct Node {
		int fa;
		int ch[2];
		int val;
		int flag;
	}; Node node[N];
	
	bool Nroot(int x) {
		return node[node[x].fa].ch[0] == x || node[node[x].fa].ch[1] == x;
	}
	void Up(int x) {
		node[x].val = node[node[x].ch[0]].val + node[node[x].ch[1]].val + 1;
	}
	void Rotate(int x) {
		int y = node[x].fa, z = node[y].fa;
		bool k = node[y].ch[1] == x;
		int w = node[x].ch[k ^ 1];
		if (Nroot(y)) node[z].ch[node[z].ch[1] == y] = x;
		node[x].ch[k ^ 1] = y;
		node[y].ch[k] = w;
		if (w) node[w].fa = y;
		node[y].fa = x, node[x].fa = z;
		Up(y);
	}

	void Splay(int x) {
		while (Nroot(x)) {
			int y = node[x].fa, z = node[y].fa;
			if (Nroot(y)) Rotate((node[z].ch[1] == y) ^ (node[y].ch[1] == x) ? x : y);
			Rotate(x);
		}
		Up(x);
	}
	void Access(int x) {
		for (int y = 0; x; x = node[y = x].fa) {
			Splay(x);
			node[x].ch[1] = y; Up(x);
		}
	}
} using namespace LCT;
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		node[i].val = 1;
		if (i + a[i] <= n) node[i].fa = i + a[i];
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x;
			cin >> x; x++;
			Access(x); Splay(x);
			printf("%d\n", node[x].val);
		}
		if (opt == 2) {
			int x, y;
			cin >> x >> y; x++;
			Access(x); Splay(x);
			node[x].ch[0] = node[node[x].ch[0]].fa = 0;
			if (x + y <= n) node[x].fa = x + y;
			Up(x);
		}
	}
	return 0;
}