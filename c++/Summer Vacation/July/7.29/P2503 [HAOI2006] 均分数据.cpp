#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <random>
#include <chrono>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 21;
const int K = 1e4;
const double Eps = 1e-5;
const double Down = 0.997;

int n, m;
int a[N];
int sum[N];
double avr, ans = INF;
double f[N][N];

double Time() {return (double)clock() / CLOCKS_PER_SEC;}
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
int Random(int l, int r) {
	return Rand() % (r - l + 1) + l;
}
double Calc() {
	memset(f, 127, sizeof(f)); f[0][0] = 0;
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; i++) {
		for (int k = 1; k <= i; k++) {
			for (int j = 0; j < i; j++) {
				f[i][k] = min(f[i][k], f[j][k - 1] + (avr - sum[i] + sum[j]) * (avr - sum[i] + sum[j]));
			}
		}
	}
	ans = min(ans, f[n][m]);
	return f[n][m];
}
double Random_Max() {
	return Rand() % RAND_MAX + 1;
}
void Sa() {
	double T = 3000;
	double cur = ans;
	while (T > Eps) {
		int x = Random(1, n);
		int y = Random(1, n);
		while (x == y) x = Random(1, n);
		swap(a[x], a[y]); 
		int rev = Calc();
		if (rev < cur || exp((cur - rev) / T) * RAND_MAX > Random_Max()) cur = rev;
		else swap(a[x], a[y]);
		T *= Down;
	}
	for (int i = 1; i <= K; i++) {
		int x = Random(1, n);
		int y = Random(1, n);
		while (x == y) x = Random(1, n);
		swap(a[x], a[y]); 
		Calc();
		swap(a[x], a[y]); 
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {cin >> a[i]; avr += a[i];}
	avr /= m;
	while (Time() <= 0.8) Sa();
	Calc();
	printf("%.2lf\n", sqrt(ans / m));
	return 0;
}