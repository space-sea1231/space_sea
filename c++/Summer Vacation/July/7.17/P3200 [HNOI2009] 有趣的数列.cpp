#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;

int n, p;
int tot;
int cnt[N];
int vis[N], prime[N];

void Prime() {
	for (int i = 2; i <= n * 2; i++) {
		if (!vis[i]) {
			prime[++tot] = i;
			vis[i] = i;
		}
		for (int j = 1; j <= tot && i * prime[j] <= n * 2; j++) {
			vis[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}
int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = (sum * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return sum;
} 
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> p;
	Prime(); 
	for (int i = 1; i <= n; i++) cnt[i] = -1; 
	for (int i = n + 2; i <= n * 2; i++) cnt[i] = 1; 
	for (int i = n * 2; i >= 2; i--) {
		if (vis[i] != i) {
			cnt[vis[i]] += cnt[i];
			cnt[i / vis[i]] += cnt[i];
		}
	}
	int ans = 1;
	for (int i = 2; i <= n * 2; i++) {
		if (vis[i] == i) {
			ans = ans * Pow(i, cnt[i]) % p;
		}
	}
	printf("%lld\n", ans);
	return 0;
}