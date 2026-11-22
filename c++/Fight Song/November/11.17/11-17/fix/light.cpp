#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e3 + 10;
const int Mod = 998244353;

int n;
int f[N], g[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		memset(g, 0, sizeof(g));
		for (int j = 0; j < i; j++) {
			if (f[j] == 0) continue;
			if (a == 0) g[j + 1] = (g[j + 1] + f[j]) % Mod;
			if (a <= 1) g[j] = (g[j] + 2LL * j * f[j]) % Mod;
			if (j >= 2) g[j - 1] = (g[j - 1] + (ll)j * (j - 1) * f[j]) % Mod;
		}
		memcpy(f, g, sizeof(f));
	}
	printf("%d\n", f[1]);
	return 0;
}