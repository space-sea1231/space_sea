#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <random>
#include <chrono>
#define __Debug
#define down 0.996
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;
const int M = 1e4;
const double Eps = 1e-15;
const double Down = 0.997;

int n;
double ansx, ansy, answ;
struct Node {
	int x, y, w;
}; Node node[N];

ll Random() {
	return Rand() % RAND_MAX + 1;
}
double Calc(double x, double y) {
	double res = 0;
	for (int i = 1; i <= n; i++) {
		double dx = x - node[i].x;
		double dy = y - node[i].y;
		res += sqrt(dx * dx + dy * dy) * node[i].w;
	}
	return res;
}
void Sa() {
	double T = 3000;
	while (T > 1e-15) {
		double ex = ansx + (Random() * 2 - RAND_MAX) * T;
		double ey = ansy + (Random() * 2 - RAND_MAX) * T;

		double ew = Calc(ex, ey);
		double dw = ew - answ;
		if (dw < 0) ansx = ex, ansy = ey, answ = ew;
		// else if (exp(-dw / T) * M > Random(1, M)) ansx = ex, ansy = ey;
		else if (exp(-dw / T) * RAND_MAX > Random()) ansx = ex, ansy = ey;
		T *= down;
	}
}
signed main() {
	srand(time(NULL));
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> node[i].x >> node[i].y >> node[i].w;
		ansx += node[i].x, ansy += node[i].y;
	}
	ansx /= n, ansy /= n, answ = Calc(ansx, ansy);
	for (int i = 1; i <= 5; i++) Sa();
	printf("%.3lf %.3lf\n", ansx, ansy);
	return 0;
}