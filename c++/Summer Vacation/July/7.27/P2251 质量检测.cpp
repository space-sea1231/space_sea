#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 20;

int n, m;
int lg[N];
int st[N][K];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	lg[0] = -1;
	for (int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	// for (int i = 1; i <= n; i++) printf("lg[%d]=%d\n", i, lg[i]);
	for (int i = 1; i <= n; i++) cin >> st[i][0];
	for (int k = 1; k < K; k++) {
		for (int i = 1; i + (1 << k) - 1 <= n; i++) {
			st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
		}
	}
	for (int i = 1; i + m - 1 <= n; i++) printf("%d\n", min(st[i][lg[m]], st[i + m - (1 << lg[m])][lg[m]]));
	return 0;
}