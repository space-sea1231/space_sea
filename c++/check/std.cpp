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
		if (ans[i] ^ ans[i + 1] <= abs(ans[i] - ans[i + 1])) {
			return true;
		}
	}
	return true;
}
bool Cmp1(int a, int b) { return a < b; }
bool Cmp2(int a, int b) { return a > b; }
void Solve() {
	cin >> n;
	int siz = __lg(n + 1);
	// cerr << siz << "\n";
	for (int i = 1; i <= n; i++) {
		// cerr << i << " " << Count(i) << "\n";
		q[Count(i)].emplace_back(i);
	}
	if (siz % 2) {
		sort(q[siz].begin(), q[siz].end(), Cmp1);
		for (int p : q[siz]) ans[++top] = p;
	}
	for (int i = 1; i <= siz / 2; i++) {
		for (int p : q[i]) ans[++top] = p;
		for (int p : q[siz - i]) ans[++top] = p;
	}
	if (Check()) for (int i = 1; i <= top; i++) printf("%d ", ans[i]);
	else printf("-1");
	printf("\n");
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) Solve();
	return 0;
}