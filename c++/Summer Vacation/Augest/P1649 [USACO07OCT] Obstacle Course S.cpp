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
const int N = 1e2 + 10;

int n;
int ans = INF;
int sx, sy, fx, fy;
char c[N][N];
int dis[N][N][4];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, 1, -1, 0};

struct Node {
	int x, y;
	int face;
	int dis;

	bool operator<(const Node &src) const {
		return dis > src.dis;
	}
};

bool Check(int x, int y) {return 1 <= x && x <= n && 1 <= y && y <= n && c[x][y] != 'x';}
void Bfs() {
	priority_queue<Node> q;
	for (int i = 0; i < 4; i++) {
		q.push((Node){sx, sy, i, 0});
		dis[sx][sy][i] = 0;
	}
	while (!q.empty()) {
		Node u = q.top(); q.pop();
		if (u.dis >= ans) continue;
		for (int i = 0; i < 4; i++) {
			int xx = u.x + dx[i], yy = u.y + dy[i];
			int w = dis[u.x][u.y][u.face] + (u.face != -1 && u.face != i);
			if (Check(xx, yy) && w <= dis[xx][yy][i]) {
				q.push((Node){xx, yy, i, w});
				dis[xx][yy][i] = w;
				if (xx == fx && yy == fy) ans = min(ans, w);
			}
		}
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> c[i][j];
			if (c[i][j] == 'A') sx = i, sy = j;
			if (c[i][j] == 'B') fx = i, fy = j;
			for (int k = 0; k < 4; k++) dis[i][j][k] = INF;
		}
	}
	Bfs();
	printf("%d\n", (ans == INF ? -1 : ans));
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= n; j++) {
	// 		printf("%d ", dis[i][j]);
	// 	}
	// 	printf("\n");
	// }
	return 0;
}