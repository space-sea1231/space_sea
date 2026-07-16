#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	ll ans = 1;
	for (int i = 1; i <= n; i++) ans = ans * (i * 4 - 2) / (i + 1);
	printf("%lld\n", ans);
	return 0;
}