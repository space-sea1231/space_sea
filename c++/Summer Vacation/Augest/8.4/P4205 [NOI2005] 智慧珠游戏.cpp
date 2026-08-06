#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 4e5 + 10;
const int K = 6e3 + 10;
const int M = 20;
const int table[12][5][2] = {
    // directions of shapes
    {{0, 0}, {1, 0}, {0, 1}},                   // A
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},           // B
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}},           // C
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},           // D
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},   // E
    {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {0, 3}},   // F
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {1, 2}},   // G
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}},   // H
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}},   // I
    {{0, 0}, {-1, 1}, {0, 1}, {1, 1}, {0, 2}},  // J
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}},   // K
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {0, 3}},   // L
};

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
char c[M][M], ans[M][M];
bool vis[M][M], flag[M];
int stk[N];
struct Node {
	int ch;
    vector<pair<int, int> > cells;
}; Node node[K];
int top;
set<vector<pair<int, int>>> st[12];
vector<pair<int, int> > pos;

namespace DLX {
	int num;
	int head[N], siz[100];
	int L[N], R[N], D[N], U[N];
	int row[N], col[N];

	void Build(int c) {
		for (int i = 0; i <= c; i++) {
			L[i] = i - 1, R[i] = i + 1;
			U[i] = D[i] = i;
		}
		L[0] = c, R[c] = 0, num = c;
	}
	int GetPos(int x, int y) {return x * (x - 1) / 2 + y;}
	void Update(int r, int c) {
		col[++num] = c, row[num] = r, siz[c]++;
		D[num] = D[c], U[D[c]] = num, U[num] = c, D[c] = num;
		if (!head[r]) head[r] = L[num] = R[num] = num;
		else {
			L[R[head[r]]] = num, R[num] = R[head[r]];
			L[num] = head[r], R[head[r]] = num;
		} 
	}
	void Remove(int c) {
		L[R[c]] = L[c], R[L[c]] = R[c];
		for (int i = D[c]; i != c; i = D[i]) {
			for (int j = R[i]; j != i; j = R[j]) {
				U[D[j]] = U[j], D[U[j]] = D[j], siz[col[j]]--;
			}
		}
	}
	void Recover(int c) {
		for (int i = U[c]; i != c; i = U[i]) {
			for (int j = L[i]; j != i; j = L[j]) {
				U[D[j]] = D[U[j]] = j, siz[col[j]]++;
			}
		}
		L[R[c]] = R[L[c]] = c;
	}
	void Dance(int dep) {
		if (!R[0]) {
			 for (int i = 1; i < dep; i++) {
                int id = stk[i];
                int ch = node[id].ch;
                for (auto cur : node[id].cells) {
                    ans[cur.first][cur.second] = ch + 'A';
                }
            }
			for (int i = 1; i <= 10; i++) {
				for (int j = 1; j <= i; j++) {
					printf("%c", ans[i][j]);
				}
				printf("\n");
			}
			exit(0);
		}
		int c = R[0];
		for (int i = R[0]; i; i = R[i]) if (siz[i] < siz[c]) c = i;
		Remove(c);
		for (int i = D[c]; i != c; i = D[i]) {
			stk[dep] = row[i];
			for (int j = R[i]; j != i; j = R[j]) Remove(col[j]);
			Dance(dep + 1);
			for (int j = L[i]; j != i; j = L[j]) Recover(col[j]);
		}
		Recover(c);
	}
} using namespace DLX;

bool Check(int x, int y) {return 1 <= x && x <= 10 && 1 <= y && y <= x;}
void Dfs(int x, int y, char ch) {
	vis[x][y] = true;
	#ifdef __Debug
	// cerr<<"x y: " << x << " " << y << endl;
	#endif
	pos.emplace_back(make_pair(x, y));
	for (int i = 0; i < 4; i++) {
		int xx = x + dx[i];
		int yy = y + dy[i];
		if (Check(xx, yy) && c[xx][yy] == ch && !vis[xx][yy]) {
			#ifdef __Debug
			// cerr<<"xx yy: " << xx << " " << yy << "\n";
			#endif
			Dfs(xx, yy, ch);
		}
	}
}
pair<int, int> Rotate(pair<int, int> p, int t) {
	int x = p.first, y = p.second;
	for(int i = 0; i < t; i++) {
		int nx = y;
		int ny = -x;
		x = nx, y = ny;
	}
	return make_pair(x, y);
}
pair<int, int> Flip(pair<int, int> p, int f) {
	if(!f) return p;
	return {p.first, -p.second};
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= i; j++) {
			cin >> c[i][j];
			// change[GetPos(i, j)] = make_pair(i, j);
			#ifdef __Debug
			// printf("change[%d]={%d, %d}\n", GetPos(i, j), i, j);
			#endif
		}
	}
	Build(67);
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= i; j++) {
			if (c[i][j] >= 'A' && c[i][j] <= 'L' && !vis[i][j]) {
				pos.clear(); flag[c[i][j] - 'A'] = true; // 小优化1
				Dfs(i, j, c[i][j]);
				node[++top] = (Node){c[i][j] - 'A', pos};
				for (pair<int, int> cur : pos) Update(top, GetPos(cur.first, cur.second));
				Update(top, 55 +  c[i][j] - 'A' + 1);
			}
		}
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= i; j++) {
			if (c[i][j] == '.') {
				for(int ch = 0; ch < 12; ch++) {
					if (flag[ch]) continue; // 小优化1
					for(int r = 0; r < 4; r++) {
						for(int f = 0; f <= 1; f++) {
							vector<pair<int, int>> q;
                            bool ok = true;
                            for (int k = 0; k < 5; k++) {
                                int x = table[ch][k][0];
                                int y = table[ch][k][1];
                                if (x == 0 && y == 0 && k > 0) break;
                                pair<int, int> pt = {x, y};
                                pt = Flip(pt, f);
                                pt = Rotate(pt, r);
                                int nx = i + pt.first;
                                int ny = j + pt.second;
                                if (!Check(nx, ny) || c[nx][ny] != '.') {
                                    ok = false;
                                    break;
                               	}
                                q.emplace_back(nx, ny);
                            }
                            if (ok) {
                                sort(q.begin(), q.end());
                                if (st[ch].find(q) == st[ch].end()) {
                                    st[ch].insert(q);
                                    node[++top] = (Node){ch, q};
                                    for (auto cur : q) Update(top, GetPos(cur.first, cur.second));
                                    Update(top, 55 + ch + 1);
                                }
                            }
						}
					}
				}
			}
		}
	}
	Dance(1);
	printf("No solution\n");
	return 0;
}