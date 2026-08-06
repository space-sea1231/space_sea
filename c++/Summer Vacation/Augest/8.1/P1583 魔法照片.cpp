#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e4 + 10;

int n, k;
int e[N];
struct Node {
	int id;
	ll val;
}; Node node[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i <= 10; i++) cin >> e[i];
	for (int i = 1; i <= n; i++) {
		cin >> node[i].val;
		node[i].id = i;
	}
	sort(node + 1, node + n + 1, [&](Node a, Node b) {
		if (a.val == b.val) return a.id < b.id;
		return a.val > b.val;
	});
	for (int i = 1; i <= n; i++) node[i].val += e[(i - 1) % 10 + 1];
	sort(node + 1, node + n + 1, [&](Node a, Node b) {
		if (a.val == b.val) return a.id < b.id;
		return a.val > b.val;
	});
	for (int i = 1; i <= k; i++) printf("%d ", node[i].id);
	return 0;
}