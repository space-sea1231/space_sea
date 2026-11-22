#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e4 + 10;

int a[N], b[N], tmp[N], q[N];
ll c[N];
int lena, lenb;

void Add() {
	memset(c, 0, sizeof(c));
	int lenc = max(lena, lenb);
	int x = 0;
	for (int i = 1; i <= lenc; i++) {
		c[i] = a[i] + b[i] + x;
		x = c[i] / 10;
		c[i] %= 10;
	}
	while (x) {
		c[++lenc] = x % 10;
		x /= 10;
	}
	for (int i = lenc; i; i--) printf("%d", c[i]); printf("\n");
}
void Sub() {
	memset(c, 0, sizeof(c));
	bool flag = true;
	int lenc = max(lena, lenb);
	for (int i = lenc; i; i--) {
		if (a[i] < b[i]) flag = false;
		if (a[i] > b[i]) break;
	}
	for (int i = 1; i <= lenc; i++) {
		c[i] += a[i] - b[i];
		if (flag && c[i] < 0) {
			c[i] += 10;
			c[i + 1]--;
		}
		if (!flag && c[i] > 0) {
			c[i] -= 10;
			c[i + 1]++;
		}
	}
	while (lenc > 1 && !c[lenc]) lenc--;
	if (!flag) printf("-");
	for (int i = lenc; i; i--) printf("%d", abs(c[i])); printf("\n");
}
void Mul() {
	memset(c, 0, sizeof(c));
	int lenc = lena + lenb - 1;
	for (int i = 1; i <= lena; i++) {
		for (int j = 1; j <= lenb; j++) {
			c[i + j - 1] += a[i] * b[j];
		}
	}
	ll x = 0;
	for (int i = 1; i <= lenc; i++) {
		c[i] += x;
		x = c[i] / 10;
		c[i] %= 10;
	}
	while (x) {
		c[++lenc] = x % 10;
		x /= 10;
	}
	for (int i = lenc; i; i--) printf("%d", c[i]); printf("\n");
}
void Div() {
	memset(c, 0, sizeof(c));
	int l = 1, r = 0, top = 0;
	for (int i = lena; i; i--) {
		c[++r] = a[i];
		while (l < r && !c[l]) l++;
		int L = 0, R = 9, d = 0;
		while (L <= R) {
			int mid = (L + R) >> 1, x = 0;
			int lent = lenb;
			for (int j = 1; j <= lenb; j++) {
				tmp[j] = b[j] * mid + x;
				x = tmp[j] / 10;
				tmp[j] %= 10;
			}
			while (x) {
				tmp[++lent] = x % 10;
				x /= 10;
			}
			int lenc = r - l + 1;
			bool flag = (lent <= lenc);
			// cerr << c[i] << "\n";
			if (lent == lenc) {
				for (int i = l; i <= r; i++) {
					if (tmp[r - i + 1] > c[i]) {
						flag = false;
						break;
					} else if (tmp[r - i + 1] < c[i]) break;
				}
			}
			if (flag) {
				d = mid;
				L = mid + 1;
			} else R = mid - 1;
		}
		q[++top] = d;
		if (d) {
			int lent = lenb, x = 0;
			for (int j = 1; j <= lenb; j++) {
				tmp[j] = b[j] * d + x;
				x = tmp[j] / 10;
				tmp[j] %= 10;
			}
			while (x) {
				tmp[++lent] = x % 10;
				x /= 10;
			}
			// if (i == 2) {
			// 	for (int i = 1; i <= lent; i++) cerr << tmp[i]; cerr<<"\n";
			// 	for (int i = r; i >= l; i--) cerr << c[i]; cerr<<"\n";
			// }
			for (int i = r; i >= l; i--) {
				if (r - i + 1 <= lent) c[i] -= tmp[r - i + 1];
				if (c[i] < 0) {
					c[i] += 10;
					c[i - 1]--;
				}
			}
		}
	}
	
	int lpos = 0;
	while (lpos < top && !q[lpos]) lpos++;
	for (int i = lpos; i <= top; i++) printf("%d", q[i]); printf("\n");
	while (l < r && !c[l]) l++;
	for (int i = l; i <= r; i++) printf("%d", c[i]); printf("\n");
	return ;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	string sa, sb;
	cin >> sa >> sb;
	lena = sa.size(), lenb = sb.size();
	for (int i = 0; i < lena; i++) a[lena - i] = sa[i] - '0';
	for (int i = 0; i < lenb; i++) b[lenb - i] = sb[i] - '0';
	Add(), Sub(), Mul(), Div();
	return 0;
}
/*

再见，太阳系
Goodbye, solar system
Au revoir, système solaire.
До свидания, солнечная система
وداعا النظام الشمسي
Auf Wiedersehen, Sonnensystem
さよなら太陽系
*/