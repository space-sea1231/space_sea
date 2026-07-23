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
bool vis[N];

namespace LCT {
	struct Node {
		int fa;
		int ch[2];
		int val;
		int flag;
	}; Node node[N * 40];
	
	bool Nroot(int x) {
		return node[node[x].fa].ch[0] == x || node[node[x].fa].ch[1] == x;
	}
	void Flip(int x) {
		swap(node[x].ch[0], node[x].ch[1]);
		node[x].flag ^= true;
	}
	void Up(int x) {
		node[x].val = node[node[x].ch[0]].val + node[node[x].ch[1]].val + 1;
	}
	void Down(int x) {
		if (node[x].flag) {
			swap(node[x].ch[0], node[x].ch[1]);
			node[node[x].ch[0]].flag ^= true;
			node[node[x].ch[1]].flag ^= true;
			node[x].flag = false;
		}
	}
	void Rotate(int x) {
		int y = node[x].fa, z = node[y].fa;
		bool k = node[y].ch[1] == x;
		int w = node[x].ch[k ^ 1];
		if (Nroot(y)) node[z].ch[node[z].ch[1] == y] = x;
		node[x].ch[k ^ 1] = y;
		node[y].ch[k] = w;	
		node[y].fa = x, node[x].fa = z;
		Up(x);
	}
	void Splay(int x) {
		int y = x, z = 0;
		stk[++z] = y;
		while (Nroot(y)) stk[++z] = y = node[y].fa;
		while (z) Down(stk[z--]);
		while (Nroot(x)) {
			y = node[x].fa, z = node[y].fa;
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
	void MakeRoot(int x) {
		Access(x); Splay(x); Flip(x);
	}
	void Split(int x, int y) {
		MakeRoot(x); Access(y);
		Splay(y);
	}
	void Link(int x, int y) {
		MakeRoot(x);
		node[y].fa = x;
	}
	void Cut(int x, int y) {
		MakeRoot(x);
		node[x].ch[0] = node[y].fa = 0;
		Up(x);
	}
} using namespace LCT;
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			int u = i, v = a[i] + i;
			while (v <= n) {
				vis[u] = true;
				Link(u, v);
				u = v, v = a[v] + v;
			}
			Link(v, n + 1);
			vis[v] = true;
		}
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x;
			cin >> x;
			Split(x, n + 1);
			printf("%d\n", node[x].val);
		}
		if (opt == 2) {
			int x, y;
			cin >> x >> y;
			int to = min(n + 1, x + a[x]);
			Cut(x, to); Link(x, y);
		}
	}
	return 0;
}
