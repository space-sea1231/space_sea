#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 4e3 + 10;

int n;
int len;
int ans[N];

void Mul(int x) {
	int tmp = 0;
	for (int i = 1; i <= len; i++) {
		ans[i] = ans[i] * x + tmp;
		tmp = ans[i] / 10;
		ans[i] %= 10;
	}
	while (tmp) {
		ans[++len] = tmp % 10;
		tmp /= 10;
	}
}
void Div(int x) {
	int tmp = 0;
	for (int i = len; i >= 1; i--) {
		ans[i] += tmp * 10;
		tmp = ans[i] % x;
		ans[i] /= x;
	}
	while (!ans[len]) len--;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	ans[1] = 1, len = 1;
	for (int i = n + 1; i <= n * 2; i++) Mul(i);
	for (int i = 1; i <= n + 1; i++) Div(i);
	for (int i = len; i >= 1; i--) printf("%d", ans[i]);
	return 0;
}