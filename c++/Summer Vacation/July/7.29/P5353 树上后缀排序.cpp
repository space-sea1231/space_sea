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
const int N = 5e5 + 10;
const int K = 20;

int n;
int a[N];
int urk[N], rk[N], rk2[N];
int pos[N], sa[N];
int fa[N][K];
char c[N];
vector<int> e[N];

void Dfs(int u) {
	for (auto v:e[u]) {
		fa[v][0] = u;
		for (int k = 1; k < K; k++) fa[v][k] = fa[fa[v][k - 1]][k - 1];
		Dfs(v);
	}
}
int cnt[N];
void Sort(int *sa, int *rk, int *pos, int m) {
	for (int i = 0; i <= m; i++) cnt[i] = 0;
	for (int i = 1; i <= n; i++) cnt[rk[i]]++;
	for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
	for (int i = n; i; i--) sa[cnt[rk[pos[i]]]--] = pos[i];
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 2; i <= n; i++) {
		int fa;
		cin >> fa;
		e[fa].emplace_back(i);
	}
	Dfs(1);
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		a[i] = c[i] - 'a' + 1;
		pos[i] = i;
	}
	Sort(sa, a, pos, n);
	int p = 0;
	urk[sa[1]] = rk[sa[1]] = p = 1;
	for (int i = 2; i <= n; i++) {
		urk[sa[i]] = (a[sa[i]] == a[sa[i - 1]]) ? p : ++p;
		rk[sa[i]] = i;
	}
	for (int k = 0; (1 << k) < n; k++) {
		for (int i = 1; i <= n; i++) rk2[i] = rk[fa[i][k]];
		Sort(pos, rk2, sa, n);
		Sort(sa, urk, pos, p);
		swap(urk, pos);
		urk[sa[1]] = rk[sa[1]] = p = 1;
		for (int i = 2; i <= n; i++) {
			urk[sa[i]] = (pos[sa[i]] == pos[sa[i - 1]] && pos[fa[sa[i]][k]] == pos[fa[sa[i - 1]][k]]) ? p : ++p;
			rk[sa[i]] = i;
		}
	}
	for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
	return 0;
}