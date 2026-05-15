#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;
const double Eps = 1e-7;

int n;
double a[N][N];
double ans[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n + 1; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		int cur = i;
		for (int j = i + 1; j <= n; j++) {
			if (fabs(a[cur][i]) < fabs(a[j][i])) cur = j;
		}
		if (fabs(a[cur][i]) < Eps) {
			printf("No Solution\n");
			return 0;
		}
		swap(a[i], a[cur]);
		double div = a[i][i];
		for (int j = i; j <= n + 1; j++) a[i][j] /= div;
		for (int j = i + 1; j <= n; j++) {
			div = a[j][i];
			for (int k = i; k <= n + 1; k++) {
				a[j][k] -= a[i][k] * div;
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		ans[i] = a[i][n + 1];
		for (int j = i + 1; j <= n; j++) {
			ans[i] -= a[i][j] * ans[j];
		}
	}
	for (int i = 1; i <= n; i++) printf("%.2lf\n", ans[i]);

	return 0;
}