#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <deque>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e4 + 10;
const int M = 1e3 + 10;

int n, sx, sy;
bool vis[M][M];
int dis[M][M];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

void Bfs() {
	memset(dis, 0x3f, sizeof(dis));
	deque<pair<int, int> > q;
	q.push_back(make_pair(sx, sy)); dis[sx][sy] = 0;
	while (!q.empty()) {
		auto [x, y] = q.front(); q.pop_front();
		if (x == 0 && y == 0) {
			printf("%d\n", dis[x][y]);
			return;
		}
		for (int i = 0; i < 4; i++) {
			int xx = x + dx[i];
			int yy = y + dy[i];
			if (0 > xx || xx >= M || 0 > yy || yy >= M) continue;
			if (dis[xx][yy] <= dis[x][y] + vis[xx][yy]) continue;
			dis[xx][yy] = dis[x][y] + vis[xx][yy];
			if (vis[xx][yy]) q.push_back(make_pair(xx, yy));
			else q.push_front(make_pair(xx, yy));
		}
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> sx >> sy;
	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		vis[x][y] = true;
	}
	Bfs();
	return 0;
}