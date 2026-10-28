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

int n, k;
int root, maxn;
bool flag;
int dep[N], cnt[N];
vector<int> e[N];
vector<int> dis1, dis2;

void Dfs1(int u, int fa) {
	if (maxn < dep[u]) { root = u, maxn = dep[u]; }
	for (int v : e[u]) {
		if (v == fa) continue;
		dep[v] = dep[u] + 1;
		Dfs1(v, u);
	}
}
void Dfs2(int u, int fa) {
	dis1.emplace_back(u);
	if (!flag && dep[u] == maxn) {
		dis2 = dis1;
		flag = true;
	}
	for (int v : e[u]) {
		if (v == fa) continue;
		dep[v] = dep[u] + 1;
		Dfs2(v, u);
	}
	dis1.pop_back();
}
void Dfs3(int u, int fa) {
	dep[u] = 0;
	for (int v : e[u]) {
		if (v == fa) continue;
		Dfs3(v, u);
		dep[u] = max(dep[v] + 1, dep[u]);
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for (int i = 1; i <= n; i++) dep[i] = INF; dep[1] = 0;
	Dfs1(1, 0);
	// Debug(root);
	for (int i = 1; i <= n; i++) dep[i] = INF; dep[root] = 0; maxn = 0;
	Dfs1(root, 0);
	for (int i = 1; i <= n; i++) dep[i] = INF; dep[root] = 0;
	Dfs2(root, 0);
	// for (int v : dis2) printf("%d ", v); printf("\n");
	if (dis2.size() & 1) {
		int rt = dis2[(dis2.size() - 1) / 2];
		for (int i = 1; i <= n; i++) dep[i] = 0;
		Dfs3(rt, 0);
	} else {
		int rt1 = dis2[(dis2.size() - 1) / 2], rt2 = dis2[(dis2.size() - 1) / 2 + 1];
		// Debug(rt1); Debug(rt2);
		for (int i = 1; i <= n; i++) dep[i] = 0;
		Dfs3(rt1, 0);
		// for (int i = 1; i <= n; i++) printf("%d ", dep[i]); printf("\n");
		int tmp[n + 10];
		for (int i = 1; i <= n; i++) tmp[i] = dep[i], dep[i] = 0;
		Dfs3(rt2, 0);
		for (int i = 1; i <= n; i++) dep[i] = min(dep[i], tmp[i]);
	}
	for (int i = 1; i <= n; i++) cnt[dep[i]]++;
	// for (int i = 1; i <= n; i++) printf("%d ", cnt[i]); printf("\n");
	for (int i = n; ~i; i--) {
		if (k - cnt[i] < 0) {
			printf("%d ", i + 1);
			return 0;
		}
		k -= cnt[i];
	}
	return 0;
}
/*
I've been reading books of old
The legends and the myths
Achilles and his gold
Hercules and his gifts
Spiderman's control
And Batman with his fists
And clearly I don't see myself upon that list
But she said where'd you wanna go
How much you wanna risk
I'm not looking for somebody
With some Superhuman gifts
Some Superhero
Some fairytale bliss
Just something I can turn to
Somebody I can kiss
I want something just like this
Oh I want something just like this
Oh I want something just like this
I want something just like this
I've been reading books of old
The legends and the myths
The testaments they told
The moon and its eclipse
And Superman unrolls
A suit before he lifts
But I'm not the kind of person that it fits
She said where'd you wanna go
How much you wanna risk
I'm not looking for somebody
With some Superhuman gifts
Some Superhero
Some fairytale bliss
Just something I can turn to
Somebody I can miss
I want something just like this
I want something just like this
Oh I want something just like this
Oh I want something just like this
Where'd you wanna go
How much you wanna risk
I'm not looking for somebody
With some Superhuman gifts
Some Superhero
Some fairytale bliss
Just something I can turn to
Somebody I can kiss
I want something just like this
Oh I want something just like this
*/