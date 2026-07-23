#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = 2147483647;
const int N = 2e5 + 10;

int n, m;
int a[N];

struct SplayTree {
	int num;
	struct Node{
		int val, fa;
		int cnt, siz;
		int son[2];
	}; Node node[N * 40];
	
	bool Check(int x) {
		return x == node[node[x].fa].son[1];
	}
	void Up(int x) {
		node[x].siz = node[node[x].son[0]].siz + node[node[x].son[1]].siz + node[x].cnt;
	}
	void Rotate(int x) {
		int y = node[x].fa, z = node[y].fa;
		int k = Check(x);
		node[z].son[node[z].son[1] == y] = x, node[x].fa = z;
		node[y].son[k] = node[x].son[k ^ 1], node[node[x].son[k ^ 1]].fa = y;
		node[x].son[k ^ 1] = y; node[y].fa = x;
		Up(y), Up(x);
	}
	void Splay(int &root, int x, int y) {
		for (int i = node[x].fa; i = node[x].fa, i && i != y; Rotate(x)) {
            if (node[i].fa && node[i].fa != y) Rotate(Check(x) == Check(i) ? i : x);
        }
		if (!y) root = x;
	}
	void Insert(int &root, int val) {
		int u = root, fa = 0;
		while (u) {
			fa = u;
			if (val == node[u].val) {
				node[u].cnt++;
				Splay(root, u, 0);
				return;
			} else u = node[u].son[val > node[u].val];
		}
		u = ++num;
		if (fa) node[fa].son[val > node[fa].val] = u;
		node[u].val = val; node[u].fa = fa;
		node[u].cnt = 1; node[u].siz = 1;
		Splay(root, u, 0);
	}
	int Rank(int &root, int val) {
		int u = root, res = 0;
		while (u) {
			if (node[u].val < val) {
				res += node[node[u].son[0]].siz + node[u].cnt;
				u = node[u].son[1];
			} else u = node[u].son[0];
		}
		return res;
	}
	void Update(int &root, int pos, int val) {
		int u = root;
        while (u && node[u].val != pos) u = node[u].son[pos > node[u].val];
		Splay(root, u, 0);
		if(node[u].cnt > 1) {
            node[u].cnt--;
            Up(u);
        } else {
			int l = node[u].son[0], r = node[u].son[1];
            if (!l && !r) root = 0; 
            else if (!l) { root = r; node[r].fa = 0; }
            else if (!r) { root = l; node[l].fa = 0; }
            else {
                int pre = l;
                while(node[pre].son[1]) pre = node[pre].son[1];
                Splay(l, pre, 0);
                node[l].son[1] = r;
                node[r].fa = l;
                root = l;
                node[l].fa = 0;
                Up(l);
            }
		}
        Insert(root, val);
	}
	int Pre(int &root, int val) {
        int u = root, res = -INF;
        while (u) {
            if (node[u].val < val) { res = node[u].val; u = node[u].son[1]; }
            else u = node[u].son[0];
        }
        return res;
    }
    int Nxt(int &root, int val) {
        int u = root, res = INF;
        while (u) {
            if (node[u].val > val) { res = node[u].val; u = node[u].son[0]; }
            else u = node[u].son[1];
        }
        return res;
    }
}; SplayTree tree;
namespace SegmentTree {
	struct Node {
		int l, r;
		int root;
	}; Node node[N << 2];

	void Build(int u, int l, int r) {
		node[u].l = l, node[u].r = r;
		tree.Insert(node[u].root, -INF);
		tree.Insert(node[u].root, INF);
		for (int i = l; i <= r; i++) tree.Insert(node[u].root, a[i]);
		if (l == r) return;
		int mid = (l + r) >> 1;
		Build(u << 1, l, mid); Build(u << 1 | 1, mid + 1, r);
	}
	int Query_Rank(int u, int L, int R, int k) {
		if (L <= node[u].l && node[u].r <= R) return tree.Rank(node[u].root, k) - 1;
		int mid = (node[u].l + node[u].r) >> 1, res = 0;
		if (L <= mid) res += Query_Rank(u << 1, L, R, k);
		if (mid < R) res += Query_Rank(u << 1 | 1, L, R, k);
		return res;
	}
	void Update(int u, int pos, int val) {
		tree.Update(node[u].root, a[pos], val);
		if (node[u].l == node[u].r) return;
		int mid = (node[u].l + node[u].r) >> 1;
		if (pos <= mid) Update(u << 1, pos, val);
		else Update(u << 1 | 1, pos, val);
	}
	int Query_Pre(int u, int L, int R, int k) {
		if (L <= node[u].l && node[u].r <= R) return tree.Pre(node[u].root, k);
		int mid = (node[u].l + node[u].r) >> 1, res = -INF;
		if (L <= mid) res = max(res, Query_Pre(u << 1, L, R, k));
		if (mid < R) res = max(res, Query_Pre(u << 1 | 1, L, R, k));
		return res;
	}
	int Query_Nxt(int u, int L, int R, int k) {
		if (L <= node[u].l && node[u].r <= R) return tree.Nxt(node[u].root, k);
		int mid = (node[u].l + node[u].r) >> 1, res = INF;
		if (L <= mid) res = min(res, Query_Nxt(u << 1, L, R, k));
		if (mid < R) res = min(res, Query_Nxt(u << 1 | 1, L, R, k));
		return res;
	}
} using namespace SegmentTree;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	Build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int opt, l, r, k, pos;
		cin >> opt;
		// cerr<<i<<" ";
		if (opt == 3) cin >> pos >> k;
		else cin >> l >> r >> k;
		if (opt == 1) printf("%d\n", Query_Rank(1, l, r, k) + 1);
		if (opt == 2) {
			int L = 0, R = 1e8, ans = 0;
			while (L <= R) {
				int mid = (L + R) >> 1;
				if (Query_Rank(1, l, r, mid) + 1 <= k) L = mid + 1, ans = mid;
				else R = mid - 1;
			}
			printf("%d\n", ans);
		}
		if (opt == 3) {
			Update(1, pos, k);
			a[pos] = k;
		}
		if (opt == 4) printf("%d\n", Query_Pre(1, l, r, k));
		if (opt == 5) printf("%d\n", Query_Nxt(1, l, r, k));
	}
	return 0;
}