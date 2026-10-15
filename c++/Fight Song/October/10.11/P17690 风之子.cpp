#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int T;
ll a, b;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> a >> b;
		printf("%lld\n", a + b + a / __gcd(a, b) * b);
	}
	return 0;
}