#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
struct Array {
	int val[4][4];

	bool operator<(const Array &s) const {
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				if (val[i][j] != s.val[i][j]) return val[i][j] < s.val[i][j];
			}
		}
		return false;
	}
}; Array f, s;

int H(Array src) {
	int cnt = 0;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			if (src.val[i][j] != s.val[i][j] && src.val[i][j]) cnt++;
		}
	}
	return cnt;
}

struct Node {
	Array val;
	int dis;

	bool operator<(const Node &s) const {return dis + H(val) > s.dis + H(s.val);}
};
set<Array> vis;
priority_queue<Node> q;

bool Check(int x, int y) {return 1 <= x && x <= 3 && 1 <= y && y <= 3;}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	s.val[1][1] = 1, s.val[1][2] = 2, s.val[1][3] = 3;
	s.val[2][1] = 8, s.val[2][3] = 4;
	s.val[3][1] = 7, s.val[3][2] = 6; s.val[3][3] = 5;
	int sx, sy;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			char c;
			cin >> c;
			f.val[i][j] = c - '0';
		}
	}
	vis.insert(f);
	q.push(Node{f, 0});
	while (!q.empty()) {
		Node cur = q.top(); q.pop();
		if (!H(cur.val)) {
			printf("%d\n", cur.dis);
			return 0;
		}
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				if (!cur.val.val[i][j]) sx = i, sy = j;
			}
		}
		for (int i = 0; i < 4; i++) {
			int xx = sx + dx[i];
			int yy = sy + dy[i];
			if (Check(xx, yy)) {
				swap(cur.val.val[sx][sy], cur.val.val[xx][yy]);
				if (!vis.count(cur.val)) {
					vis.insert(cur.val);
					q.push((Node){cur.val, cur.dis + 1});
				}
				swap(cur.val.val[sx][sy], cur.val.val[xx][yy]);
			}
		}
	}

	return 0;
}