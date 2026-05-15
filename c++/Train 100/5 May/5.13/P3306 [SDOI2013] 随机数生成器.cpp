#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <unordered_map>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

int Pow(int a, int b, int p) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = sum * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return sum;
}

unordered_map<int, int> hsh;

int BSGS(int a, int b, int p) {
	a %= p, b %= p;
	if (b == 1) return 0;
	if (a == 0) return b == 0 ? 1 : -1;
	hsh.clear();
	int siz = sqrt(p) + 1;
	int sum = 1;
	for (int i = 0; i < siz; i++) {
		hsh[b * sum % p] = i;
		sum = sum * a % p;
	}
	a = Pow(a, siz, p);
	sum = 1;
	for (int i = 1; i <= siz; i++) {
		sum = sum * a % p;
		if (hsh.find(sum) != hsh.end()) return i * siz - hsh[sum];
	}
	return -1;
}

int Exgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	int d = Exgcd(b, a % b, x, y);
	int z = x; x = y; y = z - y * (a / b);
	return d;
}

int T;
int p, a, b, g, t;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> p >> a >> b >> g >> t;
		// cerr<<"Debug:"<<p<<' '<<a<<' '<<b<<' '<<g<<' '<<t<<'\n';
		t %= p, a %= p, b %= p, g %= p;
		if (g == t) {
			printf("1\n");
			continue;
		}
		if (a == 0) {
			printf("%d\n", b == t ? 2 : -1);
			continue;
		}
		if (a == 1) {
			t = (t - g + p) % p;
			int x, y;
			// printf("b = %d p = %d\n", b, p);
			int d = Exgcd(b, p, x, y);
			if (t % d) {
				printf("-1\n");
				continue;
			}
			// cerr << x << " " << y << " " << d << "   ";

			x = x * (t / d) % p;
			x = x % (p / d) + (p / d);
			// cerr << (x % (p / d) >= 0 ? x % (p / d) : x) << " " << (x % (p / d) >= 0 ? x % (p / d) : x) + 1 << "\n";
			printf("%lld\n", (x % (p / d) >= 0 ? x % (p / d) : x) + 1);
			continue;
		}
		int tmp = b * Pow(a - 1, p - 2, p) % p;
		int res = BSGS(a, (t + tmp) % p * Pow(g + tmp, p - 2, p) % p, p);
		printf("%lld\n", res == -1 ? -1 : res + 1);
	}
	return 0;
}