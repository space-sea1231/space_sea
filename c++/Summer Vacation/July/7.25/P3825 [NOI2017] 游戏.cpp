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
const int N = 1e5 + 10;

int n, d, m;
int num, cnt, top, col;
int id[N];
int dfn[N], low[N];
int stk[N], color[N];
char s[N];
int a1[N], b1[N];
char a2[N], b2[N];
bool vis[N];
vector<int> e[N * 2];

int Trans (int pos, char car) {
	char venue = s[pos];
	if (venue == 'c') {
		if (car == 'A') return 0;
		else return 1;
	}
	if (venue == 'b') {
		if (car == 'A') return 0;
		else return 1;
	}
	if (venue == 'a') {
		if (car == 'B') return 0;
		else return 1;
	}
	if (car == 'C') return 1;
	else return 0;
}
void Tarjan(int u) {
	dfn[u] = low[u] = ++num;
	stk[++top] = u; vis[u] = true;
	for (auto v:e[u]) {
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int cur; col++;
		do {
			cur = stk[top--];
			color[cur] = col;
			vis[cur] = false;
		} while(cur != u);
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		if (s[i] == 'x') id[i] = cnt++;
	}
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> a1[i] >> a2[i] >> b1[i] >> b2[i];
	for (int sta = 0, lim = (1 << d); sta < lim; sta++) {
		//0 AC    1 BC
		for (int i = 1; i <= n * 2; i++) {
			dfn[i] = low[i] = 0;
			// color[i] = vis[i] = 0;
			// top = 0;
			col = num = 0;
			e[i].clear();
		}
		for (int i = 1; i <= m; i++) {
			if (s[a1[i]] == 'x' && s[b1[i]] == 'x') {
				bool flaga = (sta & (1 << id[a1[i]]));
				bool flagb = (sta & (1 << id[b1[i]]));
				if (!flaga && a2[i] == 'B') continue;
				if (flaga && a2[i] == 'A') continue;
				int reva = Trans(a1[i], a2[i]), revb = Trans(b1[i], b2[i]);
				if (!flagb && b2[i] == 'B') e[a1[i] + n * reva].emplace_back(a1[i] + n * (reva ^ 1));
				else if (flagb && b2[i] == 'A') e[a1[i] + n * reva].emplace_back(a1[i] + n * (reva ^ 1));
				else {
					e[a1[i] + n * reva].emplace_back(b1[i] + n * revb);
					e[b1[i] + n * (revb ^ 1)].emplace_back(a1[i] + n * (reva ^ 1));
				}
			} else if (s[a1[i]] == 'x') {
				bool flag = (sta & (1 << id[a1[i]]));
				if (!flag && a2[i] == 'B') continue;
				if (flag && a2[i] == 'A') continue;
				int reva = Trans(a1[i], a2[i]), revb = Trans(b1[i], b2[i]);
				if ((int)s[b1[i]] - 32 == b2[i]) e[a1[i] + n * reva].emplace_back(a1[i] + n * (reva ^ 1));
				else {
					e[a1[i] + n * reva].emplace_back(b1[i] + n * revb);
					e[b1[i] + n * (revb ^ 1)].emplace_back(a1[i] + n * (reva ^ 1));
				}
			} else if (s[b1[i]] == 'x') {
				bool flag = (sta & (1 << id[b1[i]]));
				int reva = Trans(a1[i], a2[i]), revb = Trans(b1[i], b2[i]);
				if ((int)s[a1[i]] - 32 == a2[i]) continue;
				if (!flag && b2[i] == 'B') e[a1[i] + n * reva].emplace_back(a1[i] + n * (reva ^ 1));
				else if (flag && b2[i] == 'A') e[a1[i] + n * reva].emplace_back(a1[i] + n * (reva ^ 1));
				else {
					e[a1[i] + n * reva].emplace_back(b1[i] + n * revb);
					e[b1[i] + n * (revb ^ 1)].emplace_back(a1[i] + n * (reva ^ 1));
				}
			} else {
				int reva = Trans(a1[i], a2[i]), revb = Trans(b1[i], b2[i]);
				if ((int)s[a1[i]] - 32 == a2[i]) continue;
				if ((int)s[b1[i]] - 32 == b2[i]) e[a1[i] + n * reva].emplace_back(a1[i] + n * (reva ^ 1));
				else {
					e[a1[i] + n * reva].emplace_back(b1[i] + n * revb);
					e[b1[i] + n * (revb ^ 1)].emplace_back(a1[i] + n * (reva ^ 1));
				}
			}
		}
		for (int i = 1; i <= n * 2; i++) if (!dfn[i]) Tarjan(i);
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			if (color[i] == color[i + n]) {
				flag = false;
				break;
			}
		}
		if (!flag) continue;
		for (int i = 1; i <= n; i++) {
			int opt = (color[i] < color[i + n]);
			if (s[i] == 'x') {
				bool flag = sta & (1 << id[i]);
				if (!flag) {
					if (opt) printf("A");
					else printf("C");
				} else {
					if (opt) printf("B");
					else printf("C");
				}
			} else {
				if (s[i] == 'a') {
					if (opt) printf("B");
					else printf("C");
				}
				if (s[i] == 'b') {
					if (opt) printf("A");
					else printf("C");
				}
				if (s[i] == 'c') {
					if (opt) printf("A");
					else printf("B");
				}
			}
		}
		return 0;
	}
	printf("-1\n");
	return 0;
}