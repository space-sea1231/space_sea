#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;

int n, m;
int a[N], b[N], c[N];
int top[N];

struct Node {
	int val, id;

	bool operator<(const Node &src) const {
		return val > src.val;
	}
};
priority_queue<Node> q;

int Calc(int x, int a, int b, int c) {
	return a * x * x + b * x + c;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i];
		q.push((Node){Calc(++top[i], a[i], b[i], c[i]), i});
	}
	for (int i = 1; i <= m; i++) {
		int ans = q.top().val, id = q.top().id; q.pop();
		printf("%d ", ans);
		q.push((Node){Calc(++top[id], a[id], b[id], c[id]), id});
	}
	return 0;
}