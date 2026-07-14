#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

double n;
double a[10];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	double ans = 1;
	for (int i = 1; i <= 7; i++) {
		cin >> a[i];
		n += a[i];
	}
	for (int i = 1; i <= 6; i++) {
		ans *= a[i] / (n - i + 1) * i; 
	}
	ans *= a[7] * 7;
	printf("%.3lf\n", ans);
	return 0;
}