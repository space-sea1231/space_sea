#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;

int n, k0;
int a[N][N];
bool vis[N];
pair<int, int> pos[N * N];

struct Node {
	int sx, sy, fx, fy;
};

vector<Node> ans;

int Change(int x, int y) { return (x - 1) * n + y; }

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> k0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			pos[a[i][j]] = make_pair(i, j);
		}
	}
	for (int i = 1; i <= n; i++) {
		int cur = 1;
		for (int j = 1; j <= n; j++) vis[j] = false;
		for (; !vis[cur]; cur = pos[Change(i, cur)].second) vis[cur] = true;
		for (int j = 1; j <= n; j++) vis[j] = false;
		for (; !vis[cur]; cur = pos[Change(i, cur)].second) {
			int v = Change(i, cur);
			int x = pos[v].first, y = pos[v].second;
			if (x != i) {
				ans.emplace_back((Node){x, y, i, y});
				swap(pos[v], pos[a[i][y]]);
				swap(a[x][y], a[i][y]);
			}
			vis[cur] = 1;
		}
		for (int j = 1; j <= n; j++) vis[j] = false;
		for (int v = Change(i, cur); !vis[cur]; cur = pos[v].second) {
			if (pos[v] != make_pair(i, cur)) {
				int x = pos[v].first, y = pos[v].second;
				ans.emplace_back((Node){x, y, x, cur});
				swap(pos[v], pos[a[x][cur]]);
				swap(a[x][y], a[i][cur]);
			}
			vis[cur] = 1;
		}
		for (int j = 1; j <= n; j++) {
			if (vis[j]) continue;
			int v = Change(i, j);
			int x = pos[v].first, y = pos[v].second;
			if (pos[v] == make_pair(i, j)) continue;
			if (x == i || y == j) {
				ans.emplace_back((Node){x, y, i, j});
				swap(pos[v], pos[a[i][j]]);
				swap(a[x][y], a[i][j]);
			} else {
				ans.emplace_back((Node){x, y, x, j});
				swap(pos[v], pos[a[x][j]]);
				swap(a[x][y], a[x][j]);
				ans.emplace_back((Node){x, j, i, j});
				swap(pos[v], pos[a[i][j]]);
				swap(a[x][j], a[i][j]);
			}
		}
	}
	printf("%d\n", (int)ans.size());
	for (Node cur : ans) printf("%d %d %d %d\n", cur.sx, cur.sy, cur.fx, cur.fy);

	return 0;
}