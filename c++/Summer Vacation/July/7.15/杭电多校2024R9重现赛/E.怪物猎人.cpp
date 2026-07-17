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
	while (t--) {
		int k, x, y;
		cin >> k >> x >> y;
		int a = (k + x - 1) / x;
		int b = (k + y - 1) / y;
		if (a != b) printf("Yes\nYes\n");
		else if (a & 2) printf("Yes\nNo\n");
		else printf("No\nYes\n");
	}
	return 0;
}