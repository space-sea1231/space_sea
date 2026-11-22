#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 18;

int n, m;
int siz;
int a[N];
ll ans[N];

// 栈
int top;
int stk[N];

// 笛卡尔树
namespace Tree {
    int root;
    int f[N][K];
    ll g[N][K];

    struct Node {
        int siz, dep;
        int lson, rson;
    }; Node node[N];

    void Dfs(int u, int fa) {
        node[u].dep = node[fa].dep + 1;
        f[u][0] = fa;
        for (int i = 1; i < K; i++) f[u][i] = f[f[u][i - 1]][i - 1];
        if (node[u].lson) Dfs(node[u].lson, u);
        if (node[u].rson) Dfs(node[u].rson, u);
        node[u].siz = node[node[u].lson].siz + node[node[u].rson].siz + 1;
    }
    void Dfs1(int u, int fa) {
        g[u][0] = (ll)(node[node[u].rson].siz + 1) * a[u];
        // if (u == 1) cerr << g[u][0] << " " << g[f[u][0]][0] << "\n";
        for (int i = 1; i < K; i++) g[u][i] = g[u][i - 1] + g[f[u][i - 1]][i - 1];
        if (node[u].lson) Dfs1(node[u].lson, u);
        if (node[u].rson) Dfs1(node[u].rson, u);
    }
    ll Lca(int x, int y) {
        int X = x, Y = y;
        ll sum = 0;
        bool flag = false;
        if (node[X].dep < node[Y].dep) { swap(X, Y); flag = true; }
        for (int i = K - 1; ~i; i--) {
            if (node[f[X][i]].dep >= node[Y].dep) {
                // cerr << x << " " << node[f[x][i]].dep << " " << i << "\n";
                if (!flag) sum += g[X][i];
                X = f[X][i];
            }
        }
        // cerr << sum << " " << X << " " << Y << "\n";
        if (X == Y) return sum + a[X] + (flag ? abs(x - y) * a[X] : 0);
        for (int i = K - 1; ~i; i--) {
            if (f[X][i] != f[Y][i]) {
                if (!flag) sum += g[X][i];
                else sum += g[Y][i];
                X = f[X][i];
                Y = f[Y][i];
            }
        }
        // cerr << "Debug:" << sum << " " << g[Y][0] << " " << sum + (ll)a[f[X][0]] * (abs(y - f[X][0]) + 1) + (flag ? g[Y][0] : g[X][0]) << "\n";
        return sum + (ll)a[f[X][0]] * (abs(y - f[X][0]) + 1) + (flag ? g[Y][0] : g[X][0]);
    }
} using namespace Tree;

// 莫队
namespace Mo {
    ll cur;

    struct Query {
        int l, r;
        int id;

        bool operator<(const Query &s) const {
            if (l / siz != s.l / siz) return l < s.l;
            return (s.l / siz & 1 ? r < s.r : r > s.r);
        }
    }; Query q[N];

    void Add(int l, int r) { cur += Lca(l, r); } //cerr << l << " " << r << " " << Lca(l, r) << "\n";}
    void Del(int l, int r) { cur -= Lca(l, r); }

} using namespace Mo;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    siz = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k && a[stk[k]] > a[i]) k--;
        if (k) node[stk[k]].rson = i;
        if (k < top) node[i].lson = stk[k + 1];
        stk[++k] = i; top = k;
    }
    Dfs(root = stk[1], 0); Dfs1(root, 0);
    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    int L = 1, R = 0;
    for (int i = 1; i <= m; i++) {
        while (L > q[i].l) Add(--L, R);
        while (R < q[i].r) Add(++R, L);
        while (L < q[i].l) Del(L++, R);
        while (R > q[i].r) Del(R--, L);
        ans[q[i].id] = cur;
    }
    // cerr << Lca(1, 4);
    // cerr << g[1][0];
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    return 0;
}
/*
钟声响起归家的讯号
在他生命里 仿佛带点唏嘘
黑色肌肤给他的意义
是一生奉献 肤色斗争中
年月把拥有变做失去
疲倦的双眼带着期望
今天只有残留的躯壳
迎接光辉岁月
风雨中抱紧自由
一生经过彷徨的挣扎
自信可改变未来
问谁又能做到
可否不分肤色的界限
愿这土地里 不分你我高低
缤纷色彩闪出的美丽
是因它没有 分开每种色彩
年月把拥有变做失去
疲倦的双眼带着期望
今天只有残留的躯壳
迎接光辉岁月
风雨中抱紧自由
一生经过彷徨的挣扎
自信可改变未来
问谁又能做到
今天只有残留的躯壳
迎接光辉岁月
风雨中抱紧自由
一生经过彷徨的挣扎
自信可改变未来
问谁又能做到
今天只有残留的躯壳
迎接光辉岁月
风雨中抱紧自由 +
一生经过彷徨的挣扎
自信可改变未来
问谁又能做到
今天只有残留的躯壳
迎接光辉岁月
风雨中抱紧自由
一生经过彷徨的挣扎
自信可改变未来
*/