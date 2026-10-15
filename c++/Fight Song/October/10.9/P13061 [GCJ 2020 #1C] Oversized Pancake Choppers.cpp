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
const int N = 1e4 + 10;
const int M = 5e5 + 10;

int T;
int n, m;
ll a[N];
vector<int> q[M];

struct Node {
	ll a, b;
	int id;
	bool operator<(const Node &s) const { return a * s.b < s.a * b; }
	bool operator!=(const Node &s) const { return a != s.a || b != s.b; }
}; Node node[M];

bool Check(int mid) {
	ll cnt = 0;
	for (int i = 1; i <= n; i++) cnt += a[i] * node[mid].b / node[mid].a;
	return cnt >= m;
}
int Solve() {
	cin >> n >> m;
	int tot = 0, idx = 1;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int g = __gcd(a[i], (ll)j);
			node[++tot] = (Node){a[i] / g, j / g, j};			
		}
	}
	sort(node + 1, node + tot + 1);
	for (int i = 1; i <= tot; i++) q[i].clear();
	for (int i = 1; i <= tot; i++) {
		if (i != 1 && node[i] != node[i - 1]) node[++idx] = node[i];
		q[idx].emplace_back(node[i].id);
	}
	tot = idx;
	int l = 1, r = tot, lim = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (Check(mid)) {
			lim = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	int ans = INF;
	for (int i = 1; i <= lim; i++) {
		sort(q[i].begin(), q[i].end());
		int res = 0, rest = m;
		for (int w : q[i]) {
			if (rest >= w) res += w - 1, rest -= w;
			else break;
		}
		ans = min(ans, res + rest);
	}
	return ans;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	for (int _ = 1; _ <= T; _++) {
		int res = Solve();
		printf("Case #%d: %d\n", _, res);
	}
	return 0;
}
/*
A good book is a door you can open every where 
好书是一扇随处可开的门

重重疑点 步步危险
是谁将谜局深埋书页间
当我翻开这残卷
冥冥之中就与你有了关联
续续断断 或醒或眠
难逃这宿命游离人世间
怕我匆匆看一眼
就捡得天光撞入渺渺风烟
狂沙怒海 大路肩并肩
天高地远 相视而笑 我们直往无前
我看过 无数山峦 于这双眸中浮现
是你共我驻足人间
多少回 还似从前 有我有你在身边
漫漫旅途不曾完结
天真已随 风雪消减
哪一缕春风才与你擦肩
千年深村雨不歇
十年难捱也不过盼再相见
茫茫长白 忽近忽远
斑驳后独自抵抗着时间
待我交还你无邪
所有轮回将归于故事起点
惊雷骤起 沸腾了荒夜
不用语言 心跳它懂 我们还热的血
我踏过 碧落黄泉 来时路曲折蜿蜒
是你陪我生死历遍
多少回 慷慨赴约 有我有你在身边
后来传奇都将续写
原来一生还不够
能有几人 共岁月不朽
这条道 是兄弟就一直走
梦还长 从没有 尽头
我看过 无数山峦 于这双眸中浮现
是你共我驻足人间
多少回 还似从前 有我有你在身边
漫漫旅途不曾完结
我踏过 碧落黄泉 来时路曲折蜿蜒
是你共我生死历遍
多少回 慷慨赴约 有我有你在身边
后来传奇都将续写
*/