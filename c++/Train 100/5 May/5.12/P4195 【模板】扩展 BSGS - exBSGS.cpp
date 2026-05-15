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

int Gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}
unordered_map<int, int> hsh;

int BSGS(int a, int b, int p, int s) {
	if (a == 0) return b == 0 ? 1 : -1;
	hsh.clear();
	int siz = sqrt(p) + 1;
	int sum = 1;
	for (int i = 0; i < siz; i++) {
		hsh[b * sum % p] = i;
		sum = (ll)sum * a % p;
	}
	a = Pow(a, siz, p);
	sum = s;
	for (int i = 1; i <= siz; i++) {
		sum = (ll)sum * a % p;
		if (hsh.find(sum) != hsh.end()) return i * siz - hsh[sum];
	}
	return -1;
}

int ExBSGS(int a, int b, int p) {
	a %= p, b %= p;
	if (b == 1 || p == 1) return 0;
	int cnt = 0, sum = 1;
	int d;
	while ((d = Gcd(a, p)) ^ 1) {
		if (b % d) return -1;
		cnt++;
		b /= d, p /= d;
		sum = (ll)sum * a / d % p;
		if (sum == b) return cnt;
	}
	int res = BSGS(a, b, p, sum);
	cerr << a << " " << b << " " << p << " " << res << "\n";
	return (res == -1) ? -1 : res + cnt;
}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	int a, p, b;
	while (cin >> a >> p >> b, a && p && b) {
		int res = ExBSGS(a, b, p);
		if (~res) printf("%lld\n", res);
		else printf("No Solution\n");
	}
	return 0;
}