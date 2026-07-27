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
stack<int> s;
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	int a;
	char c;
	cin >> a; s.push(a);
	while (cin >> c >> a) {
		if (c == '+') s.push(a % 10000);
		else {	
			int b = s.top(); s.pop();
			a %= 10000;
			b = b * a % 10000;
			s.push(b);
		}
	}
	int ans = 0;
	while (!s.empty()) {
		int a = s.top(); s.pop();
		ans = (ans + a) % 10000;
	}
	printf("%d\n", ans);
	return 0;
}