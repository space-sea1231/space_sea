#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <random>
#include <chrono>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 40;
const double down = 0.997;
const double eps = 1e-6;

int t, n;
vector<ll> a;
ll ans, tot;

inline double Time() { return (double)clock() / CLOCKS_PER_SEC; }
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
inline int Random(int l, int r) { return Rand() % (r - l + 1) + l; }

ll Calc() {
	ll sum = 0;
	for (int i = 1; (i << 1) <= n; i++) sum += a[i];
	ans = min(ans, abs((sum << 1) - tot));
	return abs((sum << 1) - tot);
	// ll rev = (n & 1) ? abs(abs(sum1 - sum2) - a[(n >> 1) + 1]) : abs(sum1 - sum2);
	// return rev;
}
void SA() {
	double T = 5000;
	ll cur = Calc();
	while (T > eps) {
		int x = Random(0, n - 1);
		int y = Random(0, n - 1);
		// while (x == y) x = Random(1, n);
		swap(a[x], a[y]);
		ll rev = Calc();
		if (cur >= rev || exp((double)(cur - rev) / T) > ((double)Rand() / RAND_MAX)) cur = rev;
		else swap(a[x], a[y]);
		T *= down;
	}
}
signed main() {
	srand(time(nullptr));
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		ans = INF, tot = 0;
		cin >> n;
		a.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			tot += a[i];
		}
		for (int i = 1; i <= 80; i++) {
			shuffle(a.begin(), a.end(), Rand);
			SA();
		}
		for (int i = 1; i <= 2000; i++) {
			int x = Random(0, n - 1);
			int y = Random(0, n - 1);
			// while (n != 1 && x == y) x = Random(0, n - 1);
			swap(a[x], a[y]);
			Calc();
			swap(a[x], a[y]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}