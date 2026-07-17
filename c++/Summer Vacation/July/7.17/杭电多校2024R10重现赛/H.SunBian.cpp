#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int t;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	ll n, k;
	while (t--) {
		cin >> n >> k;
		if (n == k) printf("A");
		else if (k == 1 && n & 1) printf("A");
		else printf("B");
	}
	return 0;
}