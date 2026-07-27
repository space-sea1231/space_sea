#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;
const int K = 20;

int n, m, Mod;
int lg[N];
int st[N][K];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> m >> Mod;
	lg[0] = -1;
	for (int i = 1; i <= m; i++) lg[i] = lg[i >> 1] + 1;
	int last = 0;
	for (int i = 1; i <= m; i++) {
		char opt;
		int x;
		cin >> opt >> x;
		if (opt == 'A') {
			x = ((ll)x + last) % Mod;
			st[++n][0] = x;
			for (int k = 1; k <= lg[n]; k++) st[n - (1 << k) + 1][k] = max(st[n - (1 << k) + 1][k - 1], st[n - (1 << (k - 1)) + 1][k - 1]);
		}
		if (opt == 'Q') {
			last = max(st[n - x + 1][lg[x]], st[n - (1 << lg[x]) + 1][lg[x]]);
			printf("%d\n", last);
			
		}
	}
	return 0;
}