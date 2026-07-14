#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <map>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int t;
int a, b, c;
map<pair<int, int> , int> q;
int Dfs(int len, int k) {
	if (len <= 0 || k < 0) return 0;
	if (q.find(make_pair(len, k)) != q.end()) return q[make_pair(len, k)];
	int lenl = len / 2, lenr = len / 2;
	if (len % 2 == 0) lenl--;
	return q[make_pair(len, k)] = Dfs(lenl, k - 1) + Dfs(lenr, k) + 1;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		int l, r, k;
		cin >> l >> r >> k;
		if (r - l + 1 <= k) printf("%lld\n", r - l + 1);
		else printf("%lld\n", Dfs(r - l + 1, k));
	}
	return 0;
}