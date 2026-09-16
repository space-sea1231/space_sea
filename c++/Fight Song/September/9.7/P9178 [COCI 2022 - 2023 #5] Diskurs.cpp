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
const int N = 1.1e6 + 10;

int n, m;
int a[N];
int dis[N];
queue<pair<int, int> > q;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < (1 << m); i++) dis[i] = -1;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		q.push(make_pair(a[i], dis[a[i]] = 0));
	}
	while (!q.empty()) {
		pair<int, int> u = q.front(); q.pop();
		// cerr<<u.first << " " << u.second << "\n";
		for (int i = 0; i < m; i++) {
			int v = u.first ^ (1 << i);
			if (dis[v] == -1) {
				dis[v] = u.second + 1;
				q.push(make_pair(v, dis[v]));
			}
		}
	}
	// for (int i = 0; i < (1 << m); i++) printf("dis[%d]=%d\n", i, dis[i]);
	for (int i = 1; i <= n; i++) printf("%d ", m - dis[(1 << m) - 1 ^ a[i]]);
	return 0;
}