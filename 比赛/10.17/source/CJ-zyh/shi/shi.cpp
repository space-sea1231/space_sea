#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e6 + 10;
const int kMaxV = (1 << 10) + 10;
const int kInf = 1e9;

int T;

int n;

string s;

int a[kMaxN];

vector<pair<int, int>> G[kMaxV];
int dis[kMaxV];
pair<int, int> fr[kMaxV];

int calc(int x, int y) {
	return (!x) & (!y);
}

void init() {
	int len = 7;
	for (int i = 0; i < (1 << len); ++i) {
		for (int j = 1; j < len - 1; ++j) {
			int k = i & ((1 << len) - 1 - (1 << j - 1) - (1 << j + 1));
			k |= calc((i >> j) & 1, (i >> j - 1) & 1) << j - 1;
			k |= calc((i >> j) & 1, (i >> j + 1) & 1) << j + 1;
			G[k].emplace_back(i, j);
		}
	}
	memset(dis, 0x3f, sizeof(dis));
	queue<int> que;
	for (int i = 0; i < len; ++i) {
		dis[(1 << len) - 1 - (1 << i)] = 0;
		que.emplace((1 << len) - 1 - (1 << i));
	}
	while (!que.empty()) {
		int x = que.front(); que.pop();
		for (auto it : G[x]) {
			int y = it.first;
			if (dis[y] > dis[x] + 1) {
				dis[y] = dis[x] + 1; 
				fr[y] = make_pair(x, it.second);
				que.emplace(y);
			}
		}
	}
	for (int i = 0; i < (1 << len); ++i) {
		//cerr << i << ' ' << dis[i] << '\n';
		assert(dis[i] < len * 13);
	}
}

int ans1;
vector<int> ans2;

namespace Task2 {

vector<pair<int, int>> G[kMaxV];
int dis[kMaxV];
pair<int, int> fr[kMaxV];

void main() {
	for (int i = 0; i < (1 << n); ++i) G[i].clear();
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 1; j < n - 1; ++j) {
			int k = i & ((1 << n) - 1 - (1 << j - 1) - (1 << j + 1));
			k |= calc((i >> j) & 1, (i >> j - 1) & 1) << j - 1;
			k |= calc((i >> j) & 1, (i >> j + 1) & 1) << j + 1;
			G[i].emplace_back(k, j + 1);
		}
	}
	//memset(dis, 0x3f, sizeof(dis));
	fill(dis, dis + (1 << n), kInf);
	queue<int> que;
	int s = 0;
	for (int i = 1; i <= n; ++i) s |= a[i] << i - 1;
	dis[s] = 0, que.emplace(s);
	while (!que.empty()) {
		int x = que.front(); que.pop();
		for (auto it : G[x]) {
			int y = it.first;
			if (dis[y] > dis[x] + 1) {
				dis[y] = dis[x] + 1; 
				fr[y] = make_pair(x, it.second);
				que.emplace(y);
			}
		}
	}
	ans1 = -1;
	int t = 0;
	for (int i = 0; i < (1 << n); ++i) {
		if (dis[i] <= 13 * n && __builtin_popcount(i) > ans1) {
			ans1 = __builtin_popcount(i);
			t = i;
		}
	}
	while (t != s) {
		ans2.emplace_back(fr[t].second);
		t = fr[t].first;
	}
	reverse(ans2.begin(), ans2.end());
}

}

int main() {
	freopen("shi.in", "r", stdin);
	freopen("shi.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	init();
	
	cin >> T;
	while (T--) {
		cin >> s; n = s.size(); s = " " + s;
		bool flg = 1;
		for (int i = 1; i <= n; ++i) a[i] = s[i] - '0', flg &= a[i];
		if (flg) {
			cout << n << " 0\n";
			continue;
		}
		else {
			ans1 = n - 1, ans2.clear();
			if (n >= 7) {
				for (int i = 1; i <= n - 2; ++i) {
					if (a[i]) {
						ans2.emplace_back(i + 1);
						a[i] = calc(a[i], a[i + 1]);
						a[i + 2] = calc(a[i + 1], a[i + 2]);
					}
				}
				int cur = 1; // 第一个 0 的位置
				while (n - cur + 1 > 7) {
					//cerr << "cur1 : " << cur << '\n';
					if (a[cur]) ++cur;
					else if (!a[cur + 1]) {
						ans2.emplace_back(cur + 1);
						a[cur] = calc(a[cur], a[cur + 1]);
						a[cur + 2] = calc(a[cur + 1], a[cur + 2]);
					}
					else {
						ans2.emplace_back(cur + 2);
						a[cur + 1] = calc(a[cur + 1], a[cur + 2]);
						a[cur + 3] = calc(a[cur + 3], a[cur + 2]);
						ans2.emplace_back(cur + 1);
						a[cur] = calc(a[cur], a[cur + 1]);
						a[cur + 2] = calc(a[cur + 1], a[cur + 2]);
					}
				}
				/*
				for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
				cout << '\n';
				*/
				cur = 0;
				for (int i = 0; i < 7; ++i) {
					cur |= a[n - 6 + i] << i;
				}
				while (dis[cur]) {
					//cerr << "cur2: " << cur << ' ' << dis[cur] << '\n';
					int p = fr[cur].second + n - 6;
					ans2.emplace_back(p);
					a[p - 1] = calc(a[p - 1], a[p]);
					a[p + 1] = calc(a[p], a[p + 1]);
					cur = fr[cur].first;
				}
			}
			else {
				Task2::main();
			}
			cout << ans1 << ' ' << ans2.size() << '\n';
			for (auto it : ans2) cout << it << ' ';
			cout << '\n';
			//for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
			//cout << '\n';
		}
	}
	return 0;
}
