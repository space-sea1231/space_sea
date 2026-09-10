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
const int N = 2e5 + 10;

int n;

struct Node {
	ll w, v;

	bool operator<(const Node a) const {
		return (2 * w + 1) * v > (2 * a.w + 1) * a.v;
	}
};
priority_queue<Node> q;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		ans += a;
		q.push((Node){1, a});
	}
	for (int i = 1; i < n - 1; i++) {
		Node x = q.top(); q.pop();
		// printf("Debug:%d %d\n", x.w, x.v);
		ans += (2 * x.w + 1) * x.v;
		q.push((Node){x.w + 1, x.v});
	}
	printf("%lld\n", ans);
	return 0;
}