#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e4 + 10;

int n;
int ans[N], mul[N], tmp[N];
int lena, lenm;

void Mul(int a[], int &lena, int b[], int lenb) {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 1; i <= lena; i++) {
		for (int j = 1; j <= lenb; j++) {
			tmp[i + j - 1] += a[i] * b[j];
		}
	}
	int x = 0, len = lena + lenb - 1;
	for (int i = 1; i <= len; i++) {
		tmp[i] += x;
		x = tmp[i] / 10;
		tmp[i] %= 10;
	}
	while (x) {
		tmp[++len] = x % 10;
		x /= 10;
	}
	for (int i = 1; i <= len; i++) a[i] = tmp[i];
	lena = len;
}
void Pow(int a, int b) {
	mul[1] = a;
	lena = lenm = 1;
	while (b) {
		if (b & 1) Mul(ans, lena, mul, lenm);
		Mul(mul, lenm, mul, lenm);
		b >>= 1;
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	ans[1] = 1;
	Pow(2, n);
	ans[1]--;
	for (int i = lena; i; i--) printf("%d", ans[i]);
	return 0;
}
/*


*/