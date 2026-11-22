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

ll Mod;
ll n, m;
int p, q, r, t;
int u, v, w;
int x, y, z;

ll Mul(ll a, ll b) {
	ll res = 0;
	while (b) {
		if (b & 1) res = (res + a) % Mod;
		a = (a + a) % Mod;
		b >>= 1;
	}
	return res;
}
struct Matrix {
	int n, m;
	vector<ll> mat;
	Matrix(int _n, int _m) : n{_n}, m{_m}, mat(n * m, 0) {}

	ll *operator[](int i) {
		return &mat[i * m];
	}
	const ll *operator[](int i) const {
		return &mat[i * m];
	}
	Matrix operator*(const Matrix &s) const {
		int x = n, y = s.m, z = m;
		Matrix res(x, y);
		for (int k = 0; k < z; k++) {
			for (int i = 0; i < x; i++) {
				if ((*this)[i][k] == 0) continue;
				for (int j = 0; j < y; j++) {
					res[i][j] = (res[i][j] + Mul((*this)[i][k], s[k][j])) % Mod;
				}
			}
		}
		return res;
	}
}; Matrix a(1, 15), T(15, 15);

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m; n -= 2;
	cin >> p >> q >> r >> t;
	cin >> u >> v >> w;
	cin >> x >> y >> z;
	Mod = m;
	T[0][1] = T[0][2] = T[0][3] = T[1][0] = T[1][2] = T[1][4] = T[2][0] = T[2][1] = T[2][5] = T[6][6] = T[7][2] = T[7][7] = T[8][0] = T[8][6] = T[8][7] = T[8][8] = T[9][1] = T[10][2] = 1;
	T[7][6] = T[8][2] = 2;
	T[0][0] = p;
	T[3][0] = q;
	T[6][0] = r;
	T[7][0] = t;
	T[1][1] = u;
	T[4][1] = v;
	T[9][9] = w;
	T[2][2] = x;
	T[5][2] = y;
	T[10][10] = z;

	a[0][0] = a[0][1] = a[0][2] = 3;
	a[0][3] = a[0][4] = a[0][5] = a[0][6] = a[0][7] = a[0][8] = 1;
	a[0][9] = w;
	a[0][10] = z;

	while (n) {
		if (n & 1) a = a * T;
		T = T * T;
		n >>= 1;
	}
	printf("nodgd %lld\n", a[0][0]);
	printf("Ciocio %lld\n", a[0][1]);
	printf("Nicole %lld\n", a[0][2]);
	return 0;
}
/*
The north wind sorts the leaves from the strong branches.
北风把落叶和强劲的枝干分开

喵喵喵,气死我了大猩猩(╬◣д◢)，以后再也不惯着他了，直接怼回去！
*/