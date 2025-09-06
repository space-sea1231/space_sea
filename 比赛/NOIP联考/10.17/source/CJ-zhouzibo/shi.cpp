#include<bits/stdc++.h>
using namespace std;
int nand(int x, int y) {
	return ((~a) ^ (~b));
}
void solve() {
	string s;
	cin >> s;
	int n = s.size();s = ' ' + s;
	cout << (n + 1) / 2 << ' ' << n / 2 << '\n';
	for (int i = 2; i <= n; i += 2) {
		cout << i << ' ';
	}
	puts("");
}
int main() {
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

