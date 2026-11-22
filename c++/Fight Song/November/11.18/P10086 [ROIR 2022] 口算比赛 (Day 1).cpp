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

int n, m;
int a[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	ll ans = 0;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) ans += a[i];
	cin >> m;
	int pos = 1;
	for (int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, y;
			cin >> x >> y;
			ans = ans - a[(pos + x - 2) % n + 1] + y;
			a[(pos + x - 2) % n + 1] = y;
		}
		if (opt == 2) {
			int k;
			cin >> k;
			pos = (pos - k + n - 1) % n + 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
/*
您好，10086为您服务...
*/