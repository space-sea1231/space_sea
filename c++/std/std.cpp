#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <set>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int T, n, k, m;
int fa[N];
int pos[N];
ll ans[N];
vector<int> e[N];

struct Person {
	int x, v;
	Person() {v = INF; x = 0;}
	bool operator<(const Person &s) const {return v < s.v;}
}; Person a[N];

namespace SGT_A {
	struct Node {
		int id;
		bool operator<(const Node &s) const {
			if (a[id].v != a[s.id].v) return a[id] < a[s.id];
			return id < s.id;
		}
	};
	set<Node> s[N];
	int node[N << 2];

	inline void Down(int p) {
		if (a[node[p << 1]] < a[node[p << 1 | 1]]) node[p] = node[p << 1];
		else node[p] = node[p << 1 | 1];
	}
	void Update(int p, int l, int r, int pos, int k) {
		if (l == r) {node[p] = k; return;}
		int mid = l + r >> 1;
		if (pos <= mid) Update(p << 1, l, mid, pos, k);
		if (mid > pos) Update(p << 1 | 1, mid + 1, r, pos, k);
		Down(p);
	}
	void Insert(int id, int dfn[]) {
		int x = a[id].x;
		s[x].insert((Node){id});
		Update(1, 1, n, dfn[x], (*s[x].begin()).id);
	}
	void Del(int id, int dfn[]) {
		int x = a[id].x;
		s[x].erase((Node){id});
		Update(1, 1, n, dfn[x], s[x].empty() ? 0 : (*s[x].begin()).id);
	}
}
namespace SGT_M{
	int Query(int p, int l, int r, int L, int R);
	int Get(int p, int l, int r, int L, int R);
}
namespace HLD {
	int num;
	int siz[N], son[N];
	int top[N], dfn[N];
	int seg[N];
	
	void Dfs1(int u) {
		siz[u] = 1;
		int maxn = 0;
		for (auto v:e[u]) {
			Dfs1(v);
			siz[u] += siz[v];
			if (maxn < siz[v]) {
				maxn = siz[v];
				son[u] = v;
			}
		}
	}
	void Dfs2(int u, int tp) {
		top[u] = tp;
		dfn[u] = ++num; seg[num] = u;
		if (son[u]) Dfs2(son[u], tp);
		for (auto v:e[u]) if (v != son[u]) Dfs2(v, v);
	}
	int Query(int p) {
		while (p) {
			int f = top[p];
			if (SGT_M::Query(1, 1, n, dfn[f], dfn[p]) > 0) p = fa[f];
			else return SGT_M::Get(1, 1, n, dfn[f], dfn[p]);
		}
		return 0;
	}
	void Update(int p, int k) {
		while (p) {
			int f = top[p];
			SGT_M::
		}
	}
} using namespace HLD;

namespace SGT_M {
	struct Node {
		int vis, minn;
		Node() {minn = INF; vis = 0;}
		void Up(int x) {vis += x, minn += x;}
	}; Node node[N << 2];
	
	inline void Up(int p) {node[p].minn = min(node[p << 1].minn, node[p << 1 | 1].minn);}
	inline void Down(int p) {
		node[p << 1].Up(node[p].vis);
		node[p << 1 | 1].Up(node[p].vis);
	}
	void Build(int p, int l, int r) {
		if (l == r) {
			node[p].minn = HLD::siz[HLD::seg[l]];
			return ;
		}
		int mid = l + r >> 1;
		Build(p << 1, l, mid);
		Build(p << 1 | 1, mid + 1, r);
		Up(p);
	}
	void Update(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			
		}
	}
	int Query(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) return node[p].minn;
		Down(p);
		int mid = l + r >> 1;
		if (R <= mid) return Query(p << 1, l, mid, L, R);
		if (L > mid) return Query(p << 1 | 1, mid + 1, r, L, R);
		return min(Query(p << 1, l, mid, L, R), Query(p << 1 | 1, mid + 1, r, L, R));
	}
	int Get(int p, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			if (node[p].minn) return 0;
			while (l < r) {
				Down(p);
				int mid = l + r >> 1;
				if (node[p << 1 | 1].minn == 0) p = p << 1 | 1, l = mid + 1;
				else p = p << 1, r = mid;
			}
			return HLD::seg[l];
		}
		Down(p);
		int mid = l + r >> 1;
		if (R <= mid) return Get(p << 1, l, mid, L, R);
		if (L > mid) return Get(p << 1 | 1, mid + 1, r, L, R);
		int t = Get(p << 1 | 1, mid + 1, r, L, R);
		return t ? t : Get(p << 1, l, mid, L, R);
	}
}


namespace Company {
	ll ans;
	struct Roll {
		int id, pos;
	};
	stack<Roll> s;

	void Add(int id) {
		ans += a[id].v;
		SGT_A::Insert(id, HLD::dfn);

	}
	bool Update(int id) {
		int p = HLD::Query(a[id].x);
		if (!p) {
			s.push((Roll){id, 0});
			Add(id);
			return true;
		}
	}
}

namespace SGT_T {
	vector<int> node[N << 2];
	
	void Update(int p, int l, int r, int L, int R, int id) {
		if (L <= l && r <= R) {
			node[p].emplace_back(id);
			return ;
		}
		int mid = l + r >> 1;
		if (L <= mid) Update(p << 1, l, mid, L, R, id);
		if (mid < R) Update(p << 1 | 1, mid + 1, r, L, R, id);
	}
	void Dfs(int p, int l, int r) {
		int cnt = 0;
		for (auto x:node[p]) cnt += Company::Update(x);
		int mid = l + r >> 1;
		if (l == r) ans[l] = Company::ans;
		else Dfs(p << 1, l, mid), Dfs(p << 1 | 1, mid + 1, r);
		while (cnt--) Company::Roll();
	}
} 

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> k >> m;
	for (int i = 2; i <= n; i++) {
		cin >> fa[i];
		e[fa[i]].emplace_back(i);
	}

	Dfs1(1);
	Dfs2(1, 1);
	SGT_M::Build(1, 1, n);
	for (int i = 1; i <= k; i++) cin >> a[i].x >> a[i].v;
	for (int i = 1; i <= m; i++) {
		int opt, x;
		cin >> opt >> x;
		if (opt == 1) {
			a[++k].x = x;
			cin >> a[k].v;
			pos[k] = i;
		}
		if (opt == 2) {
			SGT_T::Update(1, 0, m, pos[x], i - 1, x);
			pos[x] = -1;
		}
	}
	for (int i = 1; i <= k; i++) if (pos[i] > -1) SGT_T::Update(1, 0, m, pos[i], m, i);
	SGT_T::Dfs(1, 0, m);
	return 0;
}