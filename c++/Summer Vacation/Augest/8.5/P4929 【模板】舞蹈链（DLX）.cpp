#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 4e5 + 10;

int n, m;

namespace DLX {
	int num;
	int stk[N];
	int head[N], siz[N];
	int L[N], R[N], D[N], U[N];
	int col[N], row[N];

	void Build(int r, int c) {
		for (int i = 0; i <= c; i++) {
			L[i] = i - 1, R[i] = i + 1;
			D[i] = U[i] = i;
		}
		L[0] = c, R[c] = 0; num = c;
	}
	void Update(int r, int c) {
		col[++num] = c, row[num] = r; siz[c]++;
		D[num] = D[c], U[D[c]] = num, U[num] = c, D[c] = num;
		if (!head[r]) head[r] = L[num] = R[num] = num;
		else {
			L[R[head[r]]] = num, L[num] = head[r];
			R[num] = R[head[r]], R[head[r]] = num;
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
			for (int i = 1; i < dep; i++) printf("%d ", stk[i]);
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
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	Build(n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			bool val;
			cin >> val;
			if (val) Update(i, j);
		}
	}
	Dance(1);
	printf("No Solution!\n");
	return 0;
}