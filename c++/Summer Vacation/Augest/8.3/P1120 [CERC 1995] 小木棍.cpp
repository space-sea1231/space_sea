#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 70;

int n, m;
int sum, cur;
int a[N], nxt[N];
bool flag;
bool vis[N];

void Dfs(int k, int last, int rest) {
	if (!rest) {
		if (k == m) {flag = true; return;}
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				vis[i] = true;
				Dfs(k + 1, i, cur - a[i]);
				vis[i] = false;
				if (flag) return;
				break;
			}
		}
	}
	int l = last + 1, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (a[mid] <= rest) r = mid;
		else l = mid + 1;
	}
	for (int i = l; i <= n; i++) {
		if (!vis[i]) {
			vis[i] = true;
			Dfs(k, i, rest - a[i]);
			vis[i] = false;
			if (flag) return;
			if (rest == a[i] || rest == cur) return;
			i = nxt[i];
			if (i == n) return;
		}
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	// int tmp = n; n = 0;
	for (int i = 1; i <= n; i++) {
		// int x;
		// cin >> x;
		// if (x > 50) continue;
		// a[++n] = x;
		// sum += a[n];
		cin >> a[i];
		sum += a[i];
	}
	sort(a + 1, a + n + 1, [&](int a, int b) {
		return a > b;
	});
	nxt[n] = n;
	for (int i = n - 1; i; i--) {
		if (a[i] == a[i + 1]) nxt[i] = nxt[i + 1];
		else nxt[i] = i;
	}
	for (int i = a[1]; i <= sum / 2; i++) {
		if (sum % i) continue;
		m = sum / i; cur = i;
		flag = false;
		Dfs(0, 0, 0);
		// vis[1] = true;
		// Dfs(1, 1, cur - a[1]);
		// vis[1] = false;
		if (flag) { printf("%d\n", i); return 0;}
	}
	printf("%d\n", sum);
	return 0;
}