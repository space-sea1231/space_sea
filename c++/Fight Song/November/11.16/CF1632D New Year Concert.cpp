#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;
const int K = 19;

int n;
int a[N];
int lg[N];
int st[N][K];

int Gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}
int Query(int l, int r) {
	int len = lg[r - l + 1];
	return Gcd(st[l][len], st[r - (1 << len) + 1][len]);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	lg[0] = -1;
	for (int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		st[i][0] = a[i];
	}
	for (int k = 1; k < K; k++) {
		for (int i = 1; i + (1 << k) - 1 <= n; i++) {
			st[i][k] = Gcd(st[i][k - 1], st[i + (1 << k - 1)][k - 1]);
		}
	}
	// cerr << Query(2, 3) << "\n";
	int l = 1, ans = 0;;
	for (int i = 1; i <= n; i++) {
		int L = l, R = i;
		while (L < R) {
			int mid = L + R >> 1;
			if (Query(mid, i) >= i - mid + 1) R = mid;
			else L = mid + 1;
		}
		if (Query(R, i) == i - R + 1) {
			ans++;
			l = i + 1;
		}
		printf("%d ", ans);
	}
	return 0;
}
/*
A short walk can untangle a long worry.
一次短途散步，能化解一长串烦恼
*/