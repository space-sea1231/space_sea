#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m, d;
int cnt;
int mo[N];
int prime[N], tot[N];
bool vis[N], flag[N];

void Mo() {
	mo[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!vis[i]) {
			prime[++cnt] = i;
			mo[i] = -1;
		}
		for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
			int cur = i * prime[j];
			vis[cur] = true;
			mo[cur] = -mo[i];
			if (i % prime[j] == 0) {
				mo[cur] = 0;
				break;
			}
		}
	}
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	Mo();
	cin >> n >> m >> d;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		// printf("mo[%d]=%d  %d\n", i, mo[i], flag[i]);
		ans += mo[i] * ((n / (d * i)) * (m / (d * i)));
	}
	printf("%lld\n", ans);
	return 0;
}