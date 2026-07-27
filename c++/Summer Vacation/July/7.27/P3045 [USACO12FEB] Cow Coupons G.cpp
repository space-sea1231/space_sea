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
const int N = 5e4 + 10;

ll n, k, m;
int a[N], b[N];
bool vis[N];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > A, B;
priority_queue<int, vector<int>, greater<int> > delta;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> k >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		A.push(make_pair(a[i], i));
		B.push(make_pair(b[i], i));
	}
	for (int i = 1; i <= k; i++) delta.push(0);
	while (!A.empty()) {
		pair<int, int> x = A.top(), y = B.top();
		if (vis[x.second]) {
			A.pop();
			continue;
		}
		if (vis[y.second]) {
			B.pop();
			continue;
		}
		if (x.first < y.first + delta.top()) {
			m -= x.first;
			vis[x.second] = true;
			A.pop();
		} else {
			m -= y.first + delta.top();
			delta.pop(); delta.push(a[y.second] - b[y.second]);
			vis[y.second] = true;
			B.pop();
		}
		if (m < 0) break;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans += vis[i];
	printf("%d\n", ans - (m < 0));
	return 0;
}