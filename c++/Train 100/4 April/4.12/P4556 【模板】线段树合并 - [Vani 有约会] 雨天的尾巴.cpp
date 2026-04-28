#include <iostream>
#include <stdio.h>
#define __Debug
#define lson node[x].son[0]
#define rson node[x].son[1]

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int LEN = 1e5;

int n, m;
int ans[N];

namespace LCA {
    int cnt;
    int head[N], to[N << 1], nxt[N << 1];
    int father[N][20], dep[N];

    void Add(int u, int v) {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }
    void Init(int u, int fa) {
        father[u][0] = fa;
        dep[u] = dep[fa] + 1;
        for (int i = 1; i <= 19; i++) father[u][i] = father[father[u][i - 1]][i - 1];
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa) continue;
            Init(v, u);
        }
    }
    int Lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = 19; i >= 0; i--) {
            if (dep[father[x][i]] >= dep[y]) x = father[x][i];
        }
        if (x == y) return x;
        for (int i = 19; i >= 0; i--) {
            if (father[x][i] != father[y][i]) {
                x = father[x][i];
                y = father[y][i];
            }
        }
        return father[x][0];
    }
} using namespace LCA;

namespace SegmentTree {
    int num;
    int root[N];
    struct Node {
        int sum, opt;
        int son[2];
    };
    Node node[N * 80];
    void PushUp(int x) {
        if (lson == 0 || rson == 0) {
            node[x].sum = node[lson + rson].sum;
            node[x].opt = node[lson + rson].opt;
            return;
        }
        int son = (node[lson].sum >= node[rson].sum) ? lson:rson;
        node[x].sum = node[son].sum;
        node[x].opt = node[son].opt;
    }
    void Change(int &x, int l, int r, int opt, int val) {
        if (!x) x = ++num;
        if (l == r) {
            node[x].sum += val;
            node[x].opt = opt;
            return;
        }
        int mid = l + r >> 1;
        if (opt <= mid) Change(lson, l, mid, opt, val);
        if (opt > mid) Change(rson, mid + 1, r, opt, val);
        PushUp(x);
    }
    int Merge(int x, int y, int l, int r) {
        if (x == 0 || y == 0) return x + y;
        if (l == r) {
            node[x].sum += node[y].sum;
            node[x].opt = l;
            return x;
        }
        int mid = l + r >> 1;
        node[x].son[0] = Merge(node[x].son[0], node[y].son[0], l, mid);
        node[x].son[1] = Merge(node[x].son[1], node[y].son[1], mid + 1, r);
        PushUp(x);
        return x;
    }
    void Cacl(int u, int fa) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa) continue;
            Cacl(v, u);
            root[u] = Merge(root[u], root[v], 1, LEN);
        }
        if (node[root[u]].sum == 0) ans[u] = 0;
        else ans[u] = node[root[u]].opt;
    }
} using namespace SegmentTree;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
    }
    Init(1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        Change(root[x], 1, LEN, z, 1);
        Change(root[y], 1, LEN, z, 1);
        Change(root[Lca(x, y)], 1, LEN, z, -1);
        Change(root[father[Lca(x, y)][0]], 1, LEN, z, -1);
    }
    Cacl(1, 0);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}