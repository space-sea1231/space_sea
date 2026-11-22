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

int T;
int n, m;
int a[N], b[N], c[N];
vector<int> pos[N];
pair<pair<int, int>, pair<int, int> > lst[N];

namespace SegmentTree {
    struct Node {
        int maxn;
        int cnt, vis;
    }; Node node[N << 2];

    void Down(int p) {
        node[p << 1].maxn += node[p].vis;
        node[p << 1].vis += node[p].vis;
        node[p << 1 | 1].maxn += node[p].vis;
        node[p << 1 | 1].vis += node[p].vis;
        node[p].vis = 0;
    }
    Node Up(const Node &a, const Node &b) {
        Node res; res.cnt = res.vis = 0;
        res.maxn = max(a.maxn, b.maxn);
        if (res.maxn == a.maxn) res.cnt += a.cnt;
        if (res.maxn == b.maxn) res.cnt += b.cnt;
        return res;
    }
    void Build(int p, int l, int r) {
        if (l == r) {
            node[p].maxn = 0;
            node[p].cnt = 1;
            node[p].vis = 0;
            return ;
        }
        int mid = l + r >> 1;
        Build(p << 1, l, mid);
        Build(p << 1 | 1, mid + 1, r);
        node[p] = Up(node[p << 1], node[p << 1 | 1]);
    }
    void Update(int p, int l, int r, int L, int R, int val) {
        if (L > R) return ;
        if (L <= l && r <= R) {
            node[p].maxn += val;
            node[p].vis += val;
            return ;
        }
        // cerr << "Debug1: " << p << " " << l << " " << r << " " << L << " " << R << '\n';
        Down(p);
        int mid = l + r >> 1;
        if (L <= mid) Update(p << 1, l, mid, L, R, val);
        if (mid < R) Update(p << 1 | 1, mid + 1, r, L, R, val);
        node[p] = Up(node[p << 1], node[p << 1 | 1]);
    }
    Node Query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return node[p];
        // cerr << "Debug2: " << p << " " << l << " " << r << " " << L << " " << R << '\n';
        Down(p);
        int mid = l + r >> 1;
        if (R <= mid) return Query(p << 1, l, mid, L, R);
        if (mid < L) return Query(p << 1 | 1, mid + 1, r, L, R);
        return Up(Query(p << 1, l, mid, L, R), Query(p << 1 | 1, mid + 1, r, L, R));
    }
} using namespace SegmentTree;
pair<pair<int, int> , pair<int, int> > Get(int p, int color) {
    if (pos[color].empty()) return make_pair(make_pair(1, 2 * n + 1), make_pair(2, 1));
    
    vector<int>::iterator it = lower_bound(pos[color].begin(), pos[color].end(), p);
	int u = it - pos[color].begin() - 1;
	
	if (a[color] == 0) {
		int idx = u + b[color] + 1;
		if (idx >= pos[color].size()) idx = 2 * n + 1;
		else idx = pos[color][idx] - 1;
		return make_pair(make_pair(p, idx), make_pair(2, 1));
	} else {
		pair<pair<int, int>, pair<int, int> > res;
		res.first.first = p;
		if (it == pos[color].end()) res.first.second = 2 * n + 1;
		else res.first.second = *it - 1;
		
		if (u + a[color] >= pos[color].size()) res.second.first = 2 * n + 1;
		else res.second.first = pos[color][u + a[color]];
		
		if (u + b[color] + 1 >= pos[color].size()) res.second.second = 2 * n + 1;
		else res.second.second = pos[color][u + b[color] + 1] - 1;
		
		return res;
	}
}
void Solve(int cur) {
    cin >> n >> m;
    Build(1, 1, (n << 1) + 1);
    for (int i = 1; i <= m; i++) pos[i].clear();
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) {
        cin >> c[i]; c[i + n] = c[i];
        pos[c[i]].emplace_back(i);
        pos[c[i]].emplace_back(i + n);
    }
    for (int i = 1; i <= m; i++) sort(pos[i].begin(), pos[i].end());
    for (int i = 1; i <= m; i++) {
        lst[i] = Get(1, i);
        if (lst[i].first.first <= lst[i].first.second) Update(1, 1, (n << 1) + 1, lst[i].first.first, lst[i].first.second, 1);
        if (lst[i].second.first <= lst[i].second.second) Update(1, 1, (n << 1) + 1, lst[i].second.first, lst[i].second.second, 1);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        Node u = Query(1, 1, (n << 1) + 1, i + 1, i + n - 2);
        if (u.maxn == m) ans += u.cnt;
        if (lst[c[i]].first.first <= lst[c[i]].first.second) Update(1, 1, n * 2 + 1, lst[c[i]].first.first, lst[c[i]].first.second, -1);
		if (lst[c[i]].second.first <= lst[c[i]].second.second) Update(1, 1, n * 2 + 1, lst[c[i]].second.first, lst[c[i]].second.second, -1);
		lst[c[i]] = Get(i + 1, c[i]);
		if (lst[c[i]].first.first <= lst[c[i]].first.second) Update(1, 1, n * 2 + 1, lst[c[i]].first.first, lst[c[i]].first.second, 1);
		if (lst[c[i]].second.first <= lst[c[i]].second.second) Update(1, 1, n * 2 + 1, lst[c[i]].second.first, lst[c[i]].second.second, 1);
    }
    printf("Case #%d: %lld\n", cur, ans);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) Solve(_);
    return 0;
}
/*

我穿越 这一片劫后蛮荒
任时间 在废墟之中流淌
我还记得
文明曾经的形状
如今被谁遗忘
尘埃直上
阴暗滋长
我失重的灵魂在游荡
遍体鳞伤却又执着顽强
躲过饥荒与病毒窥望
终于搁浅在你的手掌
不再流亡
是你的眼睛有扇窗
我看到往昔景象
旷野麦田金黄
想为你拾起希望
重饰斑驳的信仰
未至的远方 未明的方向
未能被治愈的创伤
借你的目光 赤诚的心脏
我才能无恙
末世的悲壮
沉重与绝望
是因为有你 一个肩膀
深埋进心房
生出玫瑰绽放
我失重的灵魂在游荡
遍体鳞伤却又执着顽强
幸而你站在废土之上
发出微光
跌跌撞撞
到你身旁
曾几近覆亡
仍热泪盈眶
明日之后 我们共同前往
世界的终章 或新生启航
我的影子被黑暗封藏
找到一点萤火当作月亮
幸而你站在废土之上
发出微光
跌跌撞撞
到你身旁
明日之后 并肩守望
你手掌 铭刻着家园的模样
*/