#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 19;

int T;
int n;
int top;
int ans[N];
vector<int> q[K];

int Count(int x){
	int cnt = 0;
	for (int i = K - 1; ~i; i--) cnt += ((x >> i) & 1);
	return cnt;
}
bool Check() {
	for (int i = 1; i < top; i++) {
		if ((ans[i] ^ ans[i + 1]) <= abs(ans[i] - ans[i + 1])) {
			return false;
		}
	}
	return true;
}
bool Cmp1(int a, int b) { return a < b; }
bool Cmp2(int a, int b) { return a > b; }
void Solve() {
	top = 0;
	cin >> n;
	int siz = __lg(n + 1);
	for (int i = 1; i <= siz; i++) q[i].clear();
	// cerr << siz << "\n";
	for (int i = 1; i <= n; i++) {
		// cerr << i << " " << Count(i) << "\n";
		q[Count(i)].emplace_back(i);
	}

	swap(q[siz].front(), q[siz].back());
	for (int p : q[siz]) ans[++top] = p;
	swap(q[1].front(), q[1].back());
	sort(q[1].begin() + 1, q[1].end());
	for (int i = 1; i < siz; i++) {
		for (int p : q[i]) {
			ans[++top] = p;
			// cerr << i << " " << p << "\n";
		}
	}
	if (Check()) for (int i = 1; i <= top; i++) printf("%d ", ans[i]);
	else printf("-1");
	printf("\n");
}
signed main() {
	freopen("recall.in", "r", stdin);
	freopen("recall.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) Solve();
	return 0;
}
/*
是你衣白衫如初 我红裳如故
是我尝相思味苦 我为你起舞
是我贪恋却踟蹰 你原地痴伫
还在水榭畔 画楼处
*/