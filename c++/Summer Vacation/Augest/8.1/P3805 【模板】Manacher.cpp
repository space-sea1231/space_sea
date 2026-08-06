#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1.1e7 + 10;

string c, s;
int f[N << 1];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> c;
	s = "$#";
	for (char ch:c) {
		s += ch; 
		s += "#";
	}
	s += "@";
	int n = s.size();
	int l = 0, r = -1, ans = 0;
	for (int i = 0; i < n; i++) {
		int k = (i > r) ? 1 : min(f[l + r - i], r - i + 1);
		while (s[i - k] == s[i + k]) k++;
		// printf("f[%d]=%d\n", i, f[i]);
		ans = max(ans, f[i] = k--);
		if (r < i + k) l = i - k, r = i + k;
	}
	#ifdef __Debug
	printf("%s\n", s.c_str());
	#endif
	printf("%d\n", ans - 1);
	return 0;
}