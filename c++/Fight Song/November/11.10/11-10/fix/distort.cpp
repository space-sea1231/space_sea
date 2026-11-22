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
const int N = 4e5 + 10;

int n, m;
int mnsiz, root;
int siz[N], mxsiz[N], dep[N];
int a[N], ans[N];
bool vis[N];

vector<int> e[N];

struct Node {
    int u, dep;
    int n1, n2;
};
vector<Node> q;

namespace BinaryTree {
    int tree[N << 1];

    int Lowbit(int x) { return x & -x; }
    void Update(int x, int y) {
        for (int i = x; i < (N << 1); i += Lowbit(i)) tree[i] += y;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i; i -= Lowbit(i)) rev += tree[i];
        return rev;
    }
} using namespace BinaryTree;

void Dfs(int u, int fa, int num) {
    siz[u] = 1; mxsiz[u] = 0;
    for (int v : e[u]) {
        if (v == fa || vis[v]) continue;
        Dfs(v, u, num);
        mxsiz[u] = max(mxsiz[u], siz[v]);
        siz[u] += siz[v];
    }
    mxsiz[u] = max(mxsiz[u], num - siz[u]);
    if (mnsiz > mxsiz[u]) {
        mnsiz = mxsiz[u];
        root = u;
    }
}
void Dfs1(int u, int fa, int n1, int n2) { // n1=min(a[u] - dep[u]), n2=min(a[u]+dep[u])
    dep[u] = dep[fa] + 1; siz[u] = 1;
    n1 = min(n1, a[u] - dep[u]);
    n2 = min(n2, a[u] + dep[u]);
    q.emplace_back((Node){u, dep[u], n1, n2});
    
    for (int v : e[u]) {
        if (v == fa || vis[v]) continue;
        Dfs1(v, u, n1, n2);
        siz[u] += siz[v];
    }
}
void Calc(int flag) {
    if (q.empty()) return ;
    sort(q.begin(), q.end(), [&](Node a, Node b) {
        return a.dep < b.dep;
    });
    for (Node p : q) Update(p.n1 + N, 1);

    int r = q.size() - 1;
    for (int l = 0, lim = q.size(); l < lim; l++) {
        while (r >= 0 && q[l].dep + q[r].dep > m) Update(q[r--].n1 + N, -1);
        if (r < 0) break;
        if (q[l].n2 <= q[l].dep) ans[q[l].u] += flag * (r + 1);
        else ans[q[l].u] += flag * Query(q[l].dep + N);
    }
    while (r >= 0) Update(q[r--].n1 + N, -1);
}
void Solve(int u, int fa, int num) {
    mnsiz = INF;
    Dfs(u, fa, num); u = root; 
    vis[u] = true; dep[0] = -1; q.clear();
    Dfs1(u, 0, INF, INF);
    Calc(1);

    for (int v : e[u]) {
        if (vis[v]) continue;
        q.clear();
        Dfs1(v, u, a[u] - dep[u], a[u] + dep[u]);
        Calc(-1);
    }
    for (int v : e[u]) {
        if (vis[v]) continue;
        Solve(v, u, siz[v]);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    Solve(1, 0, n);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}
/*


🌌 星空知识卡片 01：猎户座（Orion）
【📍 基础档案】

排名：全天88星座面积第26位。

位置：横跨天赤道，北半球冬季夜空绝对的主角，最佳观测期为12月至2月。

最亮星：参宿七（视星等约 0.13）。

【📖 文科浪漫与神话】
在希腊神话中，猎户俄里翁是个狂妄的巨人，他扬言要杀尽天下野兽，
大地女神盖亚便派出一只毒蝎（天蝎座）将其蛰死。宙斯把他们都放上星空，
但安排他们永不相见——所以每当猎户座从东方升起，天蝎座便正从西方落下。

星空里的猎户正举着棍棒和盾牌，腰间佩着宝剑，带着两只猎犬（大犬座与小犬座），
永远在冬季的夜空中追逐着前方的金牛。

【🔭 硬核数据与地标】

猎户腰带：参宿一、二、三，这三颗几乎等距排成一线的亮星，是全天最容易辨认的星象。

猎户配剑：腰带下方的三颗暗星，中间那颗（M42）是猎户座大星云——距离地球约 1344 光年。
它不是单颗恒星，而是孕育新恒星的巨大“产房”，肉眼即可看到一团朦胧的光晕。

【🧭 寻星导航】

找天狼星（大犬座）：顺着腰带向左下延伸，碰到全天最亮的恒星——天狼星（视星等 -1.46）。

找金牛座：顺着腰带向右上延伸，会撞见金牛座的“V”字形牛脸（最亮星为毕宿五）。
*/