#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int a[N];
namespace LCT {
	int stk[N];
	struct Node {
		int s, fa;
		int ch[2];
		bool flag;
	}; Node node[N];
	
	bool Nroot(int x) {
		return node[node[x].fa].ch[0] == x || node[node[x].fa].ch[1] == x;
	}
	void Flip(int x) {
		swap(node[x].ch[0], node[x].ch[1]);
		node[x].flag ^= true;
	}
	void Up(int x) {
		node[x].s = node[node[x].ch[0]].s ^ node[node[x].ch[1]].s ^ a[x];
	}
	void Down(int x) {
		if (node[x].flag) {
			if (node[x].ch[0]) Flip(node[x].ch[0]);
			if (node[x].ch[1]) Flip(node[x].ch[1]);
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
		if (w) node[w].fa = y;
		node[y].fa = x, node[x].fa = z;
		Up(y);
	}
	void Splay(int x) {
		int y = x, z = 0;
		stk[++z] = y;
		while (Nroot(y)) stk[++z] = y = node[y].fa;
		while (z) Down(stk[z--]);
		while (Nroot(x)) {
			y = node[x].fa, z = node[y].fa;
			if (Nroot(y)) Rotate((node[y].ch[0] == x) ^ (node[z].ch[0] == y) ? x : y);
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
	int FindRoot(int x) {
		Access(x); Splay(x);
		while(node[x].ch[0]) {
			Down(x);
			x = node[x].ch[0];
		}
		Splay(x);
		return x;
	}
	void Split(int x, int y) {
		MakeRoot(x); Access(y);
		Splay(y);
	}
	void Link(int x, int y) {
		MakeRoot(x);
		if (FindRoot(y) != x) node[x].fa = y;
	}
	void Cut(int x, int y) {
		MakeRoot(x);
		if (FindRoot(y) == x && node[y].fa == x && !node[y].ch[0]) {
			node[y].fa = node[x].ch[1] = 0;
			Up(x);
		}
	}
} using namespace LCT;
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) {
		int opt, x, y;
		cin >> opt >> x >> y;
		if (opt == 0) {
			Split(x, y);
			printf("%d\n", node[y].s);
		}
		if (opt == 1) Link(x, y);
		if (opt == 2) Cut(x, y);
		if (opt == 3) {
			Splay(x);
			a[x] = y;
			Up(x);
		}
	}
	return 0;
}