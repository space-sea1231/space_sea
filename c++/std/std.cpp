
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
const int N = 2e5 + 10;

int t, n;
vector<int> a(N), b(N), c(N);

struct BinaryTree {
	ll val[N];
	BinaryTree() {
		memset(val, 0, sizeof(val));
	}
	int Lowbit(int x) {
		return x & -x;
	}
	void Add(int x, ll y) {
		for (int i = x; i <= n; i += Lowbit(i)) val[i] += y;
	}
	ll Query(int x) {
		ll sum = 0;
		for (int i = x; i; i -= Lowbit(i)) sum += val[i];
		return sum;
	}
};
struct Node2 {
	int a, b;
	int id;

	bool operator<(const Node2 &s) const {
		return a > s.a;
	}
};
struct Node3 {
	int a, b, c;
	int id;

	bool operator<(const Node3 &s) const {
		return a > s.a;
	}
};

bool Cmpb(Node3 &a, Node3 &b) {
	return a.b > b.b;
}
void Cdq(int l, int r, vector<Node3> &q, BinaryTree &tree, vector<ll> &res) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	Cdq(l, mid, q, tree, res);
	Cdq(mid + 1, r, q, tree, res);
	sort(q.begin() + l, q.begin() + mid + 1, Cmpb);
	sort(q.begin() + mid + 1, q.begin() + r + 1, Cmpb);
	int p = l;
	for (int i = mid + 1; i <= r; i++) {
		while (p <= mid && q[p].b > q[i].b) {tree.Add(q[p].c + 1, 1); p++;}
		res[q[i].id] += tree.Query(n) - tree.Query(q[i].c + 1);
	}
	for (int i = l; i < p; i++) tree.Add(q[i].c + 1, -1);
}
vector<ll> Sort3(vector<int> &a, vector<int> &b, vector<int> &c) {
	vector<Node3> q(n);
	for (int i = 0; i < n; i++) q[i] = (Node3){a[i], b[i], c[i], i};
	sort(q.begin(), q.end());
	BinaryTree tree;
	vector<ll> res(n, 0);
	Cdq(0, n - 1, q, tree, res);
	return res;
}
vector<ll> Sort2(vector<int> &a, vector<int> &b) {
	vector<Node2> q(n);
	for (int i = 0; i < n; i++) q[i] = (Node2){a[i], b[i], i};
	sort(q.begin(), q.end());
	BinaryTree tree;
	vector<ll> res(n, 0);
	for (int i = 0; i < n; i++) {
		res[q[i].id] = tree.Query(n) - tree.Query(q[i].b + 1);
		tree.Add(q[i].b + 1, 1);
	}
	return res;
}
ll C2(ll x) {
	return x < 2 ? 0 : x * (x - 1) / 2;
}
ll C3(ll x) {
	return x < 3 ? 0 : x * (x - 1) * (x - 2) / 6;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n;
		// a.clear(), b.clear(), c.clear();
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) cin >> b[i];
		for (int i = 0; i < n; i++) cin >> c[i];
		vector<ll> AB = Sort2(a, b);
		vector<ll> AC = Sort2(a, c);
		vector<ll> BC = Sort2(b, c);
		vector<ll> ABC = Sort3(a, b, c);
		ll sum2 = 0, sumC2 = 0;
		for (int i = 0; i < n; i++) {
			sum2 += AB[i] + AC[i] + BC[i];
			// printf("Debug: %d %d %d\n", AB[i], AC[i], BC[i]);
			sumC2 += C2(AB[i]) + C2(AC[i]) + C2(BC[i]);
			// cerr<<sumC2 << endl; 
		}
		ll sum3 = 0, sumC3 = 0;
		for (int i = 0; i < n; i++) {
			sum3 += ABC[i];
			// printf("Debug: %d\n", ABC[i]);
			sumC3 += C2(ABC[i]); 
			// cerr<<sumC3 << endl; 
		}
		ll ans = 1;
		ans += n;
		ans += (sum2 - 3 * sum3);              
		ans += C3(n) - sumC2 + 2 * sumC3;    
		printf("%lld\n", ans);
	}
	return 0;
}
