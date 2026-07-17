#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e4 + 10;

int t;
int tot;
int prime[N];
int cnt[N];
int mu[N];
bool vis[N];

void Prime() {
	mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!vis[i]) {
			mu[i] = -1;
			prime[++tot] = i;
		}
		for (int j = 1; j <= tot && i * prime[j] < N; j++) {
			vis[i * prime[j]] = true;
			if (i % prime[j]) mu[i * prime[j]] = -mu[i];
			else break;
		}
	}
	for (int i = 1; i < N; i++) mu[i] += mu[i - 1];
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	Prime();
	cin >> t;
	while (t--) {
		int a, b, d;
		cin >> a >> b >> d;
		int ans = 0;
		for (int l = 1, r, lim = min(a, b) / d; l <= lim; l = r + 1) {
			r = min(a / (a / l), b / (b / l));
			ans += (a / (l * d)) * (b / (l * d)) * (mu[r] - mu[l - 1]);
		}
		printf("%d\n", ans);
	}
	return 0;
}