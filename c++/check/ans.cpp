#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 10;
const int M = 10;
const int K = 10;

int n, m, k;
int ans[N + 1][N + 1][N + 1];
int stk[N * N];

bool Check() {
	int cnt = 0;
	for (int i = 1; i < n + m; i++) {
		if (stk[i] ^ stk[i + 1]) cnt++;
	}
	return cnt == k;
}
void Dfs(int cur, int lst1, int lst0) {
	if (cur > n + m) {
		ans[n][m][k] += Check();
		return ;
	}
	if (lst1) {
		stk[cur] = 1;
		Dfs(cur + 1, lst1 - 1, lst0);
	}
	if (lst0) {
		stk[cur] = 0;
		Dfs(cur + 1, lst1, lst0 - 1);
	}
}
void Solve(int _n, int _m, int _k) {
	n = _n, m = _m, k = _k;
	Dfs(1, n, m);
	printf("%d %d %d %d\n", n, m, k, ans[n][m][k]);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			for (int k = 1; k <= K; k++) {
				Solve(i, j, k);
			}
		}
	}
	return 0;
}
