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

const int INF = sizeof(int) == 3 ? (int)1e9 + 1 : (int)1e18 + 1;

int t;
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
struct Array {
	int val[5][5];
	
	bool operator<(const Array &s) const {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (val[i][j] != s.val[i][j]) return val[i][j] < s.val[i][j];
			}
		}
		return false;
	}
}; Array f, s;

int H(Array f) {
	int cnt = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (f.val[i][j] != s.val[i][j] && f.val[i][j]) cnt++;
		}
	}
	return cnt;
}

struct Node {
	Array val;
	int dis;

	bool operator<(const Node &s) const {return dis + H(val) > s.dis + H(s.val);}
};

set<Array> vis1, vis2;
priority_queue<Node> q1, q2;

bool Check(int x, int y) {return 0 <= x && x <= 4 && 0 <= y && y <= 4;}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	s.val[0][0] = s.val[0][1] = s.val[0][2] = s.val[0][3] = s.val[0][4] = 1;
	s.val[1][1] = s.val[1][2] = s.val[1][3] = s.val[1][4] = 1;
	s.val[2][3] = s.val[2][4] = 1;
	s.val[3][4] = 1;
	s.val[2][2] = -1;
	cin >> t;
	while (t--) {
		vis1.clear(), vis2.clear();
		bool flag = true;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				char c;
				cin >> c;
				if (c == '*') f.val[i][j] = -1;
				else f.val[i][j] = c - '0';
				if (f.val[i][j] != s.val[i][j]) flag = false;
				// printf("%d", f.val[i][j]);
			}
			// printf("\n");
		}
		// printf("\n");
		if (flag) {printf("0\n"); continue;}
		for (int k = 0; k < 8; k++) {
			// cerr<<k << " ";
			vis1.clear(), vis1.insert(f);
			while (!q1.empty()) q1.pop();
			while (!q2.empty()) q2.pop();
			q1.push((Node){f, 0});
			q2.push((Node){s, 0});
			
			while (!q1.empty()) {
				Node cur = q1.top(); q1.pop();
				if (vis2.find(cur.val) != vis2.end()) {
					if (k == 0) printf("%d\n", 1);
					else printf("%d\n", k * 2);
					goto ed;
				}
				if (cur.dis == k + 1) continue;
				int x, y;
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						if (cur.val.val[i][j] == -1) x = i, y = j;
					}
				}
				for (int i = 0; i < 8; i++) {
					int xx = x + dx[i];
					int yy = y + dy[i];
					if (Check(xx, yy)) {
						swap(cur.val.val[x][y], cur.val.val[xx][yy]);
						if (vis1.find(cur.val) == vis1.end()) {
							// printf("1:k=%d xx=%d yy=%d\n", k, xx, yy);
							// if (xx == 2 && yy == 2) {
							// 	for (int a = 0; a < 5; a++) {
								// 		for (int b = 0; b < 5; b++) {
							// 			printf("%d", cur.val.val[a][b]);
							// 		}
							// 		printf("\n");
							// 	}
							// 	printf("\n");
							// 	for (int a = 0; a < 5; a++) {
							// 		for (int b = 0; b < 5; b++) {
							// 			printf("%d", s.val[a][b]);
							// 		}
							// 		printf("\n");
							// 	}
							// 	printf("\n");
							// }
							vis1.insert(cur.val);
							q1.push((Node){cur.val, cur.dis + 1});
						}
						swap(cur.val.val[x][y], cur.val.val[xx][yy]);
					}
				}
			}
			vis2.clear(), vis2.insert(s);
			while (!q2.empty()) {
				Node cur = q2.top(); q2.pop();
				if (vis1.find(cur.val) != vis1.end()) {
					printf("%d\n", k * 2 + 1);
					goto ed;
				}
				if (cur.dis == k) continue;
				int x, y;
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						if (cur.val.val[i][j] == -1) x = i, y = j;
					}
				}
				for (int i = 0; i < 8; i++) {
					int xx = x + dx[i];
					int yy = y + dy[i];
					if (Check(xx, yy)) {
						swap(cur.val.val[x][y], cur.val.val[xx][yy]);
						if (vis2.find(cur.val) == vis2.end()) {
							// printf("2:k=%d xx=%d yy=%d\n", k, xx, yy);
							vis2.insert(cur.val);
							q2.push((Node){cur.val, cur.dis + 1});
						}
						swap(cur.val.val[x][y], cur.val.val[xx][yy]);
					}
				}
			}
		}
		printf("-1\n");
		ed:;
	}
	return 0;
}
/*
0
11111
01111
00*11
00001
00000

1
11111
01111
00011
00001
000*0

2
11111
01111
0001*
00001
00010

3
11111
01111
00010
00*01
00010

4
11111
0*111
00010
00101
00010
*/