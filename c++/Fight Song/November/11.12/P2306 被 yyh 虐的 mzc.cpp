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
const int M = 1e6 + 10;
const int V = 11;
const int K = 21;

int n, m, k;
int f[N];
int cnt[K][K];

vector<pair<int, int> > q;
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		cnt[a][b]++;
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			for (int k = 1; k <= cnt[i][j]; k <<= 1) {
				cnt[i][j] -= k;
				q.emplace_back(make_pair(i * k, j * k));
			}
			if (cnt[i][j]) q.emplace_back(make_pair(i * cnt[i][j], j * cnt[i][j]));
		}
	}
	for (auto [w, v] : q) {
		for (int i = m; i >= w; i--) {
			if (f[i] < f[i - w] + v) f[i] = f[i - w] + v;
		}
	}
	printf("%s\n%d\n", (f[m] >= k ? "yes":"no"), f[m]);
	return 0;
}
/*
Old soldiers never die, they just fade away
老兵不死，只会逐渐凋零
*/