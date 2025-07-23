#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010, P = 1000000007;
int n, fa[maxn], p[maxn], sz[maxn], fact[maxn], finv[maxn], rk[maxn], num[maxn];
bool used[maxn];

int qp(int x, int y) {
	int z = 1;
	for (; y; y >>= 1, x = 1LL * x * x % P) {
		if (y & 1) z = 1LL * z * x % P;
	}
	return z;
}

int main() {
	freopen("heap.in","r",stdin);
	freopen("heap.out","w",stdout);
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &fa[i]);
	}
	bool chk = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
		if (i > 1) chk &= p[i] > p[fa[i]];
	}
	for (int i = fact[0] = finv[0] = 1; i <= n; i++) {
		fact[i] = 1LL * i * fact[i - 1] % P;
		finv[i] = qp(fact[i], P - 2);
	}
	int cur = fact[n], ans = 0;
	for (int i = n; i; i--) {
		sz[i]++, sz[fa[i]] += sz[i];
		cur = 1LL * cur * qp(sz[i], P - 2) % P;
	}
	bool flag = 0;
	if (p[1] > 1) ans = cur, flag = 1;
	rk[1] = num[1] = used[1] = 1;
	auto C = [&](int x, int y) {
		if (x < y) return 0LL;
		return 1LL * fact[x] * finv[y] % P * finv[x - y] % P;
	};
	auto _C = [&](int x, int y) {
		if (x < y) return 0LL;
		return 1LL * finv[x] * fact[y] % P * fact[x - y] % P;
	};
	bool valid = 1;
	int lst0 = 0, lst1 = 0;
	for (int i = 2; i <= n; i++) {
		cur = 1LL * cur * _C(sz[fa[i]] - 1, sz[i]) % P;
		sz[fa[i]] -= sz[i];
		int ub = flag ? n : p[i], s = 0, tmp = 1;
		for (int j = 1; j < i; j++) {
			tmp = 1LL * tmp * C(n - s - num[rk[j]], sz[rk[j]] - 1) % P;
			s += sz[rk[j]];
		}
		for (int j = 1, k = i - 1; j <= ub; j++) if (!used[j]) {
			for (; k && num[rk[k]] < j; k--) {
				s -= sz[rk[k]];
				tmp = 1LL * tmp * _C(n - s - num[rk[k]], sz[rk[k]] - 1) % P;
				tmp = 1LL * tmp * C(n - s - num[rk[k]] - sz[i], sz[rk[k]] - 1) % P;
			}
			int mul = 1LL * tmp * C(n - s - j, sz[i] - 1) % P;
			if (mul) {
				num[i] = j;
				if (!flag && j < p[i] && j > num[fa[i]]) {
					ans = (ans + 1LL * cur * mul) % P;
					lst0 = i, lst1 = j;
				}
			} else break;
		}
		if (num[i] < p[i]) flag = 1;
		used[num[i]] = 1;
		for (int j = 1; j <= i; j++) {
			if (i == j || num[rk[j]] < num[i]) {
				for (int k = i; k > j; k--) rk[k] = rk[k - 1];
				rk[j] = i; break;
			}
		}
		if (num[fa[i]] > num[i]) { valid = 0; break; }
	}
	if (!valid) {
		memset(used, 0, sizeof(used));
		memset(rk, 0, sizeof(rk));
		num[lst0] = lst1, rk[1] = used[1] = 1;
		memset(sz, 0, sizeof(sz));
		for (int i = n; i; i--) {
			sz[i]++, sz[fa[i]] += sz[i];
		}
		fill(num + lst0 + 1, num + n + 1, 0);
		for (int i = 2; i <= lst0; i++) {
			sz[fa[i]] -= sz[i], used[num[i]] = 1;
			for (int j = 1; j <= i; j++) {
				if (i == j || num[rk[j]] < num[i]) {
					for (int k = i; k > j; k--) rk[k] = rk[k - 1];
					rk[j] = i; break;
				}
			}
		}
		for (int i = lst0 + 1; i <= n; i++) {
			sz[fa[i]] -= sz[i];
			int s = 0, cnt = 0;
			for (int j = 1; j < i; j++) {
				cnt += n - s - num[rk[j]] >= sz[rk[j]] - 1;
				s += sz[rk[j]];
			}
			for (int j = 1, k = i - 1; j <= n; j++) if (!used[j]) {
				for (; k && num[rk[k]] < j; k--) {
					s -= sz[rk[k]];
					cnt -= n - s - num[rk[k]] >= sz[rk[k]] - 1;
					cnt += n - s - num[rk[k]] - sz[i] >= sz[rk[k]] - 1;
				}
				if (cnt + (n - s - j >= sz[i] - 1) >= i) num[i] = j;
				else break;
			}
			used[num[i]] = 1;
			for (int j = 1; j <= i; j++) {
				if (i == j || num[rk[j]] < num[i]) {
					for (int k = i; k > j; k--) rk[k] = rk[k - 1];
					rk[j] = i; break;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d%c", num[i], " \n"[i == n]);
	}
	printf("%d\n", ans + chk);
	return 0;
}

