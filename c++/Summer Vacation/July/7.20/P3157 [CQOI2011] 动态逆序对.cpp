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
int top;
ll val_pos[N], ans[N];
struct BinaryTree {
	int sum[N];

	int Lowbit(int x) {
		return x & -x;
	}
	void Add(int x, int y) {
		for (int i = x; i <= n; i += Lowbit(i)) sum[i] += y;
	}
	int Query(int x) {
		int rev = 0;
		for (int i = x; i; i -= Lowbit(i)) rev += sum[i];
		return rev;
	}
}; BinaryTree tree1, tree2;

struct Node {
	int val, tim, pos;
}; Node node[N];

bool CmpA1(Node a, Node b) {
	if (a.tim != b.tim) return a.tim < b.tim;
	return a.pos < b.pos;
}

bool CmpB1(Node a, Node b) {
	return a.pos > b.pos;
}
// bool flag;
void Cdq1(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	Cdq1(l, mid), Cdq1(mid + 1, r);
	// if (l == 4 && r == 5) flag = true;
	sort(node + l, node + mid + 1, CmpB1);
	sort(node + mid + 1, node + r + 1, CmpB1);
	int ptr = mid + 1;
	for (int i = l; i <= mid; i++) {
		while (ptr <= r && node[ptr].pos > node[i].pos) tree1.Add(node[ptr++].val, 1);
		// if (flag) printf("%d %d\n", node[ptr].val, node[i].val);
		ans[node[i].tim] += tree1.Query(node[i].val);
	}
	for (int i = mid + 1; i < ptr; i++) tree1.Add(node[i].val, -1);
	// if (l == 4 && r == 5) flag = false;
}

bool CmpA2(Node a, Node b) {
	if (a.tim != b.tim) return a.tim > b.tim;
	return a.pos < b.pos;
}
bool CmpB2(Node a, Node b) {
	return a.pos < b.pos;
}
void Cdq2(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	Cdq2(l, mid), Cdq2(mid + 1, r);
	sort(node + l, node + mid + 1, CmpB2);
	sort(node + mid + 1, node + r + 1, CmpB2);
	int ptr = l;
	for (int i = mid + 1; i <= r; i++) {
		while (ptr <= mid && node[ptr].pos < node[i].pos) tree2.Add(n + 1 - node[ptr++].val, 1);
		// if (node[i].tim == 4) printf("Debug:%d %d %d\n", l, r, tree2.Query(n + 1 - node[i].val));
		if (node[i].tim <= m) ans[node[i].tim] += tree2.Query(n + 1 - node[i].val);
	}
	for (int i = l; i < ptr; i++) tree2.Add(n + 1 - node[i].val, -1);
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> node[i].val;
		node[i].pos = i;
		val_pos[node[i].val] = i;
	}
	for (int i = 1; i <= m; i++) {
		int a;
		cin >> a;
		node[val_pos[a]].tim = i;
	}
	// for (int i = 1; i <= n; i++) printf("tim[%d]=%d\n", i, node[i].tim);
	int ans1 = 0;
	for (int i = 1; i <= n; i++) if (node[i].tim == 0) node[i].tim = m + 1;
	sort(node + 1, node + n + 1, CmpA1);
	// for (int i = 1; i <= n; i++) printf("val[%d]=%d\n", i, node[i].val);
	Cdq1(1, n);
	// cerr<<ans[0] << ' ';
	// for (int i = 1; i <= m; i++) printf("ans[%d]=%d\n", i, ans[i]);
	sort(node + 1, node + n + 1, CmpA2);
	// printf("\n");
	// for (int i = 1; i <= n; i++) printf("val[%d]=%d\n", i, node[i].val);
	Cdq2(1, n);
	// for (int i = 1; i <= m; i++) printf("ans[%d]=%d\n", i, ans[i]);
	for (int i = m; i; i--) ans[i] += ans[i + 1];
	// cerr<<ans[0];
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
/*
3
3 2
3 4 2
1 3 4 2
1 5 3 4 2
*/