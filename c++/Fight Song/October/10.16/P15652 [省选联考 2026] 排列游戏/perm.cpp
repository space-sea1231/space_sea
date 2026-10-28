#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int query(int, int);
void init(int c, int t) {}
vector<int> perm(int n) {// 177	
	vector<int> ans(n, -1);
	vector<bool> vis(n + 1);
	set<int> st;

	int lst = INF, zero_pos = n - 1;
	for (int i = 1; i < n; i++) {
		int res = query(i, n - 1);
		if (res < lst) {
			ans[i - 1] = res;
			vis[res] = true;
			lst = res;
		} else ans[i - 1] = -res;	
		if (res == 0) { zero_pos = i - 1; break; }
	}
	lst = INF;
	for (int i = n - 2; i >= zero_pos; i--) {
		int res = query(0, i);
		if (res < lst) {
			ans[i + 1] = res;
			vis[res] = true;
			lst = res;
		} else ans[i + 1] = -res;
	}
	if (zero_pos == n - 1) ans[n - 1] = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) st.insert(i);
	for (int i = 0; i < n; i++) {
		if (ans[i] < 0) {
			set<int>::iterator it = st.upper_bound(-ans[i]);
			ans[i] = *it;
			st.erase(it);
		}
	}
	return ans;
}