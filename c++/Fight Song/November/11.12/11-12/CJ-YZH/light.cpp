#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <stack>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int n;
int a[N];
int nxt[N];
int ans[N];
int tmp[N];

namespace BinaryTree {
	int tree[N];

	int Lowbit(int x) {
		return x & -x;
	}
	void Update(int x, int y) {
		for (int i = x; i <= n; i += Lowbit(i)) tree[i] += y;
	}
	int Query(int x) {
		int rev = 0;
		for (int i = x; i; i -= Lowbit(i)) rev += tree[i];
		return rev;
	}
} using namespace BinaryTree;
signed main() {
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	bool flagA = true;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		tmp[i] = a[i];
		if (a[i] < 0) flagA = false;
	}
	sort(tmp + 1, tmp + n + 1);
	int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
	if (flagA) {
		ll ans = 0;
		for (int i = 2; i <= n; i++) {
			ans = ans + (ll)(i - 1) * a[i];
		}
		printf("%lld\n", ans);
		for (int i = 1; i <= n; i++) printf("%d ", n - i + 1);
		return 0;
	}
	int lstdown = 1, lstup = 1;
	int down = 0, up = 0;
	for (int i = 2; i <= n; i++) {
		if (a[i] < 0) { 
			if (lstup == 1) up = i;
			nxt[lstup] = i;
			lstup = i;
		}
		if (a[i] >= 0) { 
			if (lstdown == 1) down = i;
			nxt[lstdown] = i;
			lstdown = i;
		}
	}
	stack<int> stk;
	while (down) {
		stk.push(down);
		down = nxt[down];
	}
	int num = 0;
	while (!stk.empty()) {
		ans[stk.top()] = ++num;
		stk.pop();
	}
	num = n;
	while (up) {
		stk.push(up);
		up = nxt[up];
	}
	while (!stk.empty()) {
		ans[stk.top()] = num--;
		stk.pop();
	}
	ans[1] = num;
	ll tot = 0;
	for (int i = 1; i <= n; i++) {
		int pos = lower_bound(tmp + 1, tmp + len + 1, a[i]) - tmp;
		tot += (ll)a[i] * Query(pos - 1);
		Update(n - pos + 1, 1);
	}
	printf("%lld\n", tot);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}
/*
我与你建构
光的行宫 光的行宫
让四散的尘埃汇入
胸腔之中
聆听它的鼓动
我与你建构
光的行宫 光的行宫
静待或许你愿驻足
瞬息之中
窥见烙印往昔的瞳孔
*/