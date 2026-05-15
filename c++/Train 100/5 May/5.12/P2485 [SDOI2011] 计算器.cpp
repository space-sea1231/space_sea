#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <cmath>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

int T, K;

int Pow(int a, int b, int p) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = ((ll)sum * a) % p;
		a = ((ll)a * a) % p;
		b >>= 1;
	}
	return sum;
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
		sum = (ll)sum * a % p;
	}
	a = Pow(a, siz, p);
	sum = 1;
	// cerr << a << " " <<  b << " " << siz << "\n";
	for (int i = 1; i <= siz; i++) {
		sum = (ll)sum * a % p;
		int pos = hsh.find(sum) == hsh.end() ? -1 : hsh[sum];
		if (pos >= 0) return i * siz - pos;
	}
	return -1;
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T >> K;
	while (T--) {
		int a, b, p;
		cin >> a >> b >> p;
		if (K == 1) printf("%lld\n", Pow(a, b, p));
		if (K == 2) {
			int x, y;
			int d = Exgcd(a, p, x, y);
			if (b % d) {
				printf("Orz, I cannot find x!\n");
				continue;
			}
			x = x * (b / d);
			x = (x % (p / d) + (p / d)) % (p / d);
			printf("%lld\n", x);
		}
		if (K == 3) {
			int res = BSGS(a, b, p);
			if (res == -1) printf("Orz, I cannot find x!\n");
			else printf("%lld\n", res);
		}
	}
	return 0;
}