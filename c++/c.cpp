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
const int N = 1e5 + 10;
const int M = 10;
const int e[] = {6, 6, 6, 6, 6, 6, 6,  6, 6, 6, 7, 7, 7, 7, 7, 7, 7,
				 6, 6, 7, 8, 8, 8, 8,  8, 7, 6, 6, 7, 8, 9, 9, 9, 8,
				 7, 6, 6, 7, 8, 9, 10, 9, 8, 7, 6, 6, 7, 8, 9, 9, 9,
				 8, 7, 6, 6, 7, 8, 8,  8, 8, 8, 7, 6, 6, 7, 7, 7, 7,
				 7, 7, 7, 6, 6, 6, 6,  6, 6, 6, 6, 6, 6};

int n, m;
int ans 
int a[M][M];

namespace DLX {
	int num;
	int head[N], siz[N];
	int L[N], R[N], D[N], U[N];
	int col[N], row[N];
	
	void Build(int r, int c) {
		n = r, m = c;
		for (int i = 0; i <= c; i++) {
			L[i] = i - 1, R[i] = i + 1;
			D[i] = U[i] = i;
		}
		L[0] = c, R[c] = 0, num = c;
	}
	int GetID(int row, int col, int num) {return (row - 1) * 9 * 9 + (col - 1) * 9 + num;}
	void Update(int r, int c) {
		col[++num] = c, row[num] = r, siz[c]++;
		D[num] = D[c], U[D[c]] = num, U[num] = c, D[c] = num;
		if (!head[r]) head[r] = L[num] = R[num] = num;
		else {
			R[num] = R[head[r]], L[R[head[r]]] = num;
			L[num] = head[r], R[head[r]] = num;
		}
	}
	void Insert(int row, int col, int num) {
		int dx = (row - 1) / 3 + 1;
		int dy = (col - 1) / 3 + 1;
		int room = (dx - 1) * 3 + dy;
		int id = GetID(row, col, num);
		int f1 = (row - 1) * 9 + num;
		int f2 = 81 + (col - 1) * 9 + num;
		int f3 = 81 * 2 + (room - 1) * 9 + num;
		int f4 = 81 * 3 + (row - 1) * 9 + col;
		Update(id, f1);
		Update(id, f2);
		Update(id, f3);
		Update(id, f4);
	}
	int GetW(int row, int col, int num) {return num * e[(row - 1) * 9 + (col - 1)];}
	void Remove(int col) {
		
	}
	void Dance(int dep) {
		int c = R[0];
		if (!R[0]) {
			int cur_ans = 0;
			for (int i = 1; i < dep; i++) {
				int cur_row = (stk[i] - 1) / 9 / 9 + 1;
				int cur_col = (stk[i] - 1) / 9 + 1;
				int cur_num = (stk[i] - 1) % 9 + 1;
				cur_ans += GetW(cur_row, cur_col, cur_num);
			}
			ans = max(ans, cur_ans);
			return;
		}
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
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	Build(729, 324);
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> a[i][j];
			for (int k = 1; k <= 9; k++) {
				if (!a[i][j] || k == a[i][j]) Insert(i, j, k);
			}
		}
	}
	Dance(1);
	printf("%d\n", ans == -INF ? -1 : ans);
	return 0;
}