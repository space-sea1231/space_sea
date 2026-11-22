#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int Mod = 998244353;

int n;
int ans;
int a[N];
int pw[N];
bool sta[N], vis[30][30];

void Check() {
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= n + 1; j++) {
			vis[i][j] = false;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int y = 1; y <= a[i]; y++) {
			if (sta[i]) {
				for (int x = 1; x <= i; x++) {
					vis[x][y] = true;
				}
			} else {
				for (int x = i + 1; x <= n + 1; x++) {
					vis[x][y] = true;
				} 
			}
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 1; j <= n + 1; j++) {
			cnt += vis[i][j];
		}
	}
	ans = ((ll)ans + pw[cnt]) % Mod;
}
void Dfs(int u) {
	if (u == n + 1) {
		Check();
		return ;
	}
	sta[u] = false;
	Dfs(u + 1);
	sta[u] = true;
	Dfs(u + 1);
}
signed main() {
	freopen("god.in", "r", stdin);
	freopen("god.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	pw[0] = 1; for (int i = 1; i < N; i++) pw[i] = (ll)pw[i - 1] * 2 % Mod;
	if (n <= 18) {
		for (int i = 1; i <= n; i++) cin >> a[i];
		Dfs(1);
		printf("%d\n", ans);
	} else {
		for (int i = 1; i <= n; i++) {
			int a;
			cin >> a;
		}
		int sum = 0;
		for (int i = n; i; i--) {
			ans = ((ll)ans + ((ll)(sum + (ll)i * i % Mod) * pw[i - 1] % Mod)) % Mod;
			sum = ((ll)sum + i) % Mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}