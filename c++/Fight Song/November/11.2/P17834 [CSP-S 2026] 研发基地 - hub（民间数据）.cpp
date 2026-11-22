#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int c, T, n, m;
int ans, root;
int ru[N], dep[N], sum[N], son[N];
int f[N];
bool ed[N];
vector<int> e[N];

// void Dfs(int u, int fa, int mid) {
// 	// if (mid == 0) cerr << u << " " << fa << "\n";
// 	for (int v : e[u]) {
// 		if (dep[v] <= mid) {
// 			if (dep[v] == mid) ed[u] = true;
// 			continue;
// 		}
// 		ru[u]++;
// 		if (v == fa) continue;
// 		Dfs(v, u, mid);
// 	}
// }
// void Dfs1(int u, int fa, int mid) {
// 	int max1 = 0, max2 = 0;
// 	for (int v : e[u]) {
// 		if (v == fa || dep[v] <= mid) continue;
// 		Dfs1(v, u, mid);
// 		if (ru[u] == 2 && !ed[u]) {
// 			f[u] = max(f[u], f[v] + 1);
// 			if (max1 < f[v]) max2 = max1, max1 = f[v];
// 			else if (max2 < f[v]) max2 = f[v];
// 		}
// 	}
// 	if (ru[u] == 2 && !ed[u]) ans = max(ans, max1 + max2 + 1);
// }
// bool Check(int mid) {
// 	ans = 0;
// 	int len = sum[mid] - m; // 删len个
// 	if (len <= 0) return true;
// 	if ((len + 1 >> 1) > mid) return false;
// 	// if ((len >> 1) > mid) return false;
// 	for (int i = 1; i <= n; i++) ed[i] = ru[i] = f[i] = 0;
// 	Dfs(root, 0, mid);
// 	Dfs1(root, 0, mid);
// 	// if (mid == 2) {
// 	// 	printf("root=%d\n", root);
// 	// 	for (int i = 1; i <= n; i++) {
// 	// 		printf("f[%d]=%d\n", i, f[i]);
// 	// 	}
// 	// }
// 	// if (mid == 1) cerr << root << " " << ans << "\n";
// 	return ans >= len;
// }

int top;
vector<int> line[N], tmp;

void Dfs(int u, int fa, int mid) {
	// if (mid == 0) cerr << u << " " << fa << "\n";
	for (int v : e[u]) {
		if (dep[v] <= mid) {
			son[u] = max(son[u], dep[v]);
			if (dep[v] == mid) ed[u] = true;
			continue;
		}
		ru[u]++;
		if (v == fa) continue;
		Dfs(v, u, mid);
	}
}
void Dfs1(int u, int fa, int mid) {
	if (ru[u] == 2 && !ed[u]) tmp.emplace_back(u);
	else {
		if (tmp.size() >= sum[mid] - m) {
			line[++top].resize(tmp.size());
			line[top] = tmp;
		}
		tmp.clear();
	}
	for (int v : e[u]) {
		if (v == fa || dep[v] <= mid) continue;
		Dfs1(v, u, mid);
	}
}
bool Check(int mid) {
	ans = top = 0;
	int len = sum[mid] - m;
	if (len <= 0) return true;
	if ((len + 1 >> 1) > mid) return false;

	for (int i = 1; i <= n; i++) son[i] = ed[i] = ru[i] = f[i] = 0;
	Dfs(root, 0, mid);
	// 重选 root（你原来的逻辑：找 ru==1 的点，这里保留）
	int tmp_root;
	for (int i = 1; i <= n; i++) {
		if (ru[i] == 1) { tmp_root = i; break; }
	}
	Dfs1(tmp_root, 0, mid);

	int half = (len + 1) >> 1;   // 左半长度

	for (int id = 1; id <= top; id++) {
		auto &L = line[id];
		int Ln = (int)L.size();
		if (Ln < len) continue;

		// 左半：max(son[i] + i) - l + 1，i in [l, l+half-1]
		// 右半：max(son[i] - i) + l + len，i in [l+half, l+len-1]
		deque<int> q1, q2;   // 存下标 i
		int r1 = 0, r2 = half - 1;  // 当前窗口 [l, l+len-1]，左半结束 l+half-1，右半开始 l+half

		// 初始化第一个窗口 l = 0（0-indexed 链上位置）
		for (int i = 0; i < half; i++) {
			int val = son[L[i]] + i;
			while (!q1.empty() && son[L[q1.back()]] + q1.back() <= val) q1.pop_back();
			q1.push_back(i);
		}
		for (int i = half; i < len; i++) {
			int val = son[L[i]] - i;
			while (!q2.empty() && son[L[q2.back()]] - q2.back() <= val) q2.pop_back();
			q2.push_back(i);
		}

		for (int l = 0; l + len - 1 < Ln; l++) {
			// 窗口内最大值
			int mx = 0;
			if (!q1.empty()) mx = max(mx, son[L[q1.front()]] + q1.front() - l + 1);
			if (!q2.empty()) mx = max(mx, son[L[q2.front()]] - q2.front() + l + len);
			if (mx <= mid) return true;

			// 滑到 l+1：左半移除 l，加入 l+half；右半移除 l+half，加入 l+len
			// 移除
			if (q1.front() == l) q1.pop_front();
			if (q2.front() == l + half) q2.pop_front();
			// 加入左半新元素 l+half
			if (l + half < Ln) {
				int val = son[L[l + half]] + (l + half);
				while (!q1.empty() && son[L[q1.back()]] + q1.back() <= val) q1.pop_back();
				q1.push_back(l + half);
			}
			// 加入右半新元素 l+len
			if (l + len < Ln) {
				int val = son[L[l + len]] - (l + len);
				while (!q2.empty() && son[L[q2.back()]] - q2.back() <= val) q2.pop_back();
				q2.push_back(l + len);
			}
		}
	}
	return false;   // 没有任何链存在满足条件的区间
}



void Solve() {
	cin >> n >> m;
	for (int i = 0; i <= n; i++) {
		e[i].clear();
		sum[i] = ru[i] = 0;
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
		ru[u]++, ru[v]++;
	}
	int maxn = 0;
	queue<pair<int, int> > q;
	for (int i = 1; i <= n; i++) if (ru[i] == 1) q.push(make_pair(i, 1));
	while (!q.empty()) {
		int u = q.front().first, w = q.front().second; q.pop();
		dep[u] = w;
		if (maxn < w) { maxn = w, root = u; }
		sum[w - 1]++;
		for (int v : e[u]) {
			ru[v]--;
			if (ru[v] == 1) q.push(make_pair(v, w + 1));
		}
	} 
	for (int i = maxn - 1; ~i; i--) sum[i] += sum[i + 1];
	int l = 0, r = maxn;
	while (l < r) {
		// cerr << l << " " << r << "\n";
		int mid = l + r >> 1;
		if (Check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", r);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> c >> T;
	while (T--) Solve();
	return 0;
}
/*
排出5个问题了
Dedicate 奉献
hell 地狱
chest 胸膛

Will.I.am：Yeah you could be the greatest
You can be the best
You can be the King Kong banging on your chest
You could beat the world
You could beat the war
You could talk to God go banging on his door
The Script：You can throw your hands up
You can beat the clock
You can move a mountain
You can break rocks
Will.I.am：You can be a master
Don't wait for luck
Dedicate yourself and you gon' find yourself
The Script：Standing in the hall of fame
Yeah
And the world's gonna know your name
Yeah
'Cause you burn with the brightest flame
Yeah
And the world's gonna know your name
Yeah
And you'll be on the walls of the hall of fame
Will.I.am：You can go the distance
You can run the mile
You can walk straight through hell with a smile
You can be a hero
You can get the gold
Breaking all the records they thought never could be broke
The Script：Do it for your people
Do it for your pride
How are you ever gonna know if you never even try
The Script/will.I.am：
Do it for your country
Do it for your name
'Cause there's gon' be a day when you're
The Script：Standing in the hall of fame
Yeah
And the world's gonna know your name
Yeah
'Cause you burn with the brightest flame
Yeah
And the world's gonna know your name
Yeah
And you'll be on the walls of the hall of fame
The Script/will.I.am：
Be a champion
Be a champion
Be a champion
Be a champion
Walls of the hall of fame
Be students
Be teachers
Be politicians
Be preachers
Be believers
Be leaders
Be astronauts
Be champions
Be truth seekers
Be students
Be teachers
Be politicians
Be preachers
Be believers
Be leaders
Be astronauts
Be champions
The Script：Standing in the hall of fame
Yeah
And the world's gonna know your name
Yeah
'Cause you burn with the brightest flame
Yeah
And the world's gonna know your name
Yeah
And you'll be on the walls of the hall of fame
Will.I.am：
You could be the greatest
You can be the best
You can be the King Kong banging on your chest
You could beat the world
You could beat the war
You could talk to God go banging on his door
The Script：You can throw your hands up
You can beat the clock
You can move a mountain
You can break rocks
Will.I.am：You can be a master
Don't wait for luck
Dedicate yourself and you gon' find yourself
The Script：
Standing in the hall of fame
*/