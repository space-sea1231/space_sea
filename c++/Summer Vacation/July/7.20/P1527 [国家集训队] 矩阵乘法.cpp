#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N1 = 5e2 + 10;
const int N2 = 3e5 + 10;
const int M = 6e4 + 10;

int n, m;
int top;
int id[N2];
int tot[N2], ans[N2];
int t1[N2], t2[N2];

struct Node {
	int x, y, v;

	bool operator<(const Node src) {
		return v < src.v;
	}
}; Node node[N2];

struct Question {
	int sx, sy, fx, fy, k;

}; Question que[M];

struct BinaryTree {
	int sum[N1][N1];
	
	int Lowbit(int x) {
		return x & -x;
	}
	void Add(int x, int y, int v) {
		// cerr<<"ADD: " << x << " " << y << " " << v << endl;
		for (int i = x; i <= n; i += Lowbit(i)) {
			for (int j = y; j <= n; j += Lowbit(j)) {
				sum[i][j] += v;
			}
		}
	}
	int Query(int x, int y) {
		// cerr<<"Query: " << x << " " << y << " " << endl;
		int rev = 0;
		for (int i = x; i; i -= Lowbit(i)) {
			for (int j = y; j; j -= Lowbit(j)) {
				rev += sum[i][j];
			}
		}
		return rev;
	}
	int Square(Question src) {
		// cerr<<src.fx << " " << src.fy << endl;
		int rev = Query(src.fx, src.fy);
		rev -= Query(src.sx - 1, src.fy);
		rev -= Query(src.fx, src.sy - 1);
		rev += Query(src.sx - 1, src.sy - 1);
		return rev;
	}
}; BinaryTree tree;

void Solve(int l, int r, int ql, int qr) {
	if (ql > qr) return;
	if (l == r) {
		for (int i = ql; i <= qr; i++) ans[id[i]] = node[l].v;
		return;
	}
	int mid = (l + r) >> 1;
	for (int i = l; i <= mid; i++) tree.Add(node[i].x, node[i].y, 1);
	int ptr1 = 0, ptr2 = 0;
	for (int i = ql; i <= qr; i++) {
		int u = id[i];
		int s = tree.Square(que[u]);
		// printf("s=%d\n", s);
		if (s >= que[u].k) t1[++ptr1] = u;
		else {
			t2[++ptr2] = u;
			que[u].k -= s;
		}
	}
	int cnt = ql - 1;
	for (int i = 1; i <= ptr1; i++) id[++cnt] = t1[i];
	for (int i = 1; i <= ptr2; i++) id[++cnt] = t2[i];
	for (int i = l; i <= mid; i++) tree.Add(node[i].x, node[i].y, -1);
	Solve(l, mid, ql, ql + ptr1 - 1);
	Solve(mid + 1, r, ql + ptr1, qr);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int v;
			cin >> v;
			node[++top] = (Node){i, j, v};
		}
	}
	sort(node + 1, node + top + 1);
	for (int i = 1; i <= m; i++) {
		int sx, sy, fx, fy, k;
		cin >> sx >> sy >> fx >> fy >> k;
		// cerr<<sx << " " << sy << " " << fx << " " << fy << endl;
		que[i] = (Question){sx, sy, fx, fy, k};
		id[i] = i;
	}
	Solve(1, top, 1, m);
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
/*

*/