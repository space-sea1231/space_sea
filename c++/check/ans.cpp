#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int M = 50;

int t;
int a, b, c;
int ans, tot;
int cnt[M][4];

void Go(int x, int k, int pos) {
	int tmp = 0, sumk = 1;
	while (sumk * k <= x) {
		sumk *= k;
		tmp++;
	}
	tot = max(tot, tmp);
	for (int i = tmp; i >= 0; i--) {
		if (x >= sumk) {
			cnt[i][pos] = x / sumk;
			x = x - sumk * (x / sumk);
		}
		sumk /= k;
	}
}
void Calc(int k) {
	tot = 0;
	Go(a, k, 1); Go(b, k, 2); Go(c, k, 3);
	bool flag = true;
	for (int i = tot; i >= 0; i--) {
		if ((cnt[i][1] + cnt[i][2]) % k != cnt[i][3]) {
			flag = false;
		}
		cnt[i][1] = cnt[i][2] = cnt[i][3] = 0;
	}
	if (flag) {ans++;}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
        ans = 0;
		cin >> a >> b >> c;
		if (a + b < c) {
			printf("0\n");
			continue;
		}
		if (a + b == c) {
			printf("-1\n");
			continue;
		}
        for (int i = 2; i <= a + b + c; i++) {
            Calc(i);
        }
		printf("%d\n", ans);
	}
	return 0;
}