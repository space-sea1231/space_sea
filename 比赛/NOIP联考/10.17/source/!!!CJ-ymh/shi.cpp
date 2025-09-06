#include <bits/stdc++.h>
using namespace std;
string s;
vector<int> ans;
int t, n, a[1000005];
int calc() {
	int res = 0;
	for(int i = 1; i <= n; i++)
		res += a[i];
	return res;
}
void f(int x) {
	a[x - 1] = !a[x - 1] && !a[x], a[x + 1] = !a[x + 1] && !a[x], ans.push_back(x);
	return;
}
void print() {
	cout << calc() << ' ' << ans.size() << '\n';
	for(int i : ans)
		cout << i << ' ';
	cout << '\n';
	return;
}
int main() {
	freopen("shi.in", "r", stdin);
	freopen("shi.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--) {
		cin >> s, n = s.size(), s = ' ' + s, ans.clear();
		for(int i = 1; i <= n; i++)
			a[i] = s[i] - '0';
		if(n == 3 && !a[1] && !a[2] && !a[3]) {
			f(2);
			goto f;
		}
		if(n == 4 && calc() < 2) {
			if(!a[1] && !a[2] && !a[3])
				f(2);
			else if(!a[2] && !a[3] && !a[4])
				f(3);
			else if(a[2])
				f(3), f(2);
			else
				f(2), f(3);
			goto f;
		}
		if(n < 5 || calc() > n - 2)
			goto f;
		for(int i = n - 1; i > 1; i--)
			if(a[i + 1])
				f(i);
		if(a[1] && a[2])
			f(2);
		if(calc())
			if(a[1])
				f(3), f(2), f(3);
			else
				f(4), f(3), f(4);
		f(2), f(4), f(3);
		for(int i = 6; i <= n; i++)
			f(i - 2), f(i - 1), f(i - 2);
		f:;
		print();
	}
	return 0;
}