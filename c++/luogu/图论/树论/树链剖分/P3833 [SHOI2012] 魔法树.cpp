#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10;
int n, m;
int cnt;
int head[N], to[N << 1], nxt[N << 1];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
struct Segment_Tree {
    struct Node {
        int sum, vis;
    } e[N << 2];
    void Down(int x, int l, int r) {
        int mid = (l + r) >> 1;
        e[x << 1].vis += e[x].vis;
        e[x << 1 | 1].vis += e[x].vis;
        e[x << 1].sum += (mid - l + 1) * e[x].vis;
        e[x << 1 | 1].sum += (r - mid) * e[x].vis;
        e[x].vis = 0;
    }
    void Add(int x, int l, int r, int L, int R, int w) {
        if (L <= l && r <= R) {
            e[x].vis += w;
            e[x].sum += (r - l + 1) * w;
            return;
        }
        Down(x, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid)
            Add(x << 1, l, mid, L, R, w);
        if (mid + 1 <= R)
            Add(x << 1 | 1, mid + 1, r, L, R, w);
        e[x].sum = e[x << 1].sum + e[x << 1 | 1].sum;
    }
    int Query(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R)
            return e[x].sum;
        Down(x, l, r);
        int mid = (l + r) >> 1, ans = 0;
        if (L <= mid)
            ans += Query(x << 1, l, mid, L, R);
        if (mid + 1 <= R)
            ans += Query(x << 1 | 1, mid + 1, r, L, R);
        return ans;
    }
};
struct Chain_Tree {
    Segment_Tree Seg;
    int num = 1, root;
    int father[N], son[N], top[N];
    int size[N], dep[N];
    int seg[N], rev[N];
    void Dfs1(int u, int fa) {
        father[u] = fa;
        dep[u] = dep[fa] + 1;
        size[u] = 1;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa)
                continue;
            Dfs1(v, u);
            size[u] += size[v];
            if (size[v] > size[son[u]])
                son[u] = v;
        }
    }
    void Dfs2(int u, int fa) {
        if (son[u]) {
            int v = son[u];
            top[v] = top[u];
            seg[v] = ++num;
            rev[num] = v;
            Dfs2(v, u);
        }
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa || v == son[u])
                continue;
            top[v] = v;
            seg[v] = ++num;
            rev[num] = v;
            Dfs2(v, u);
        }
    }
    void Add_Line(int x, int y, int z) {
        int fx = top[x], fy = top[y];
        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                swap(fx, fy);
                swap(x, y);
            }
            Seg.Add(1, 1, n, seg[fx], seg[x], z);
            x = father[top[x]], fx = top[x];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        Seg.Add(1, 1, n, seg[x], seg[y], z);
    }
    int Query_Tree(int x) {
        return Seg.Query(1, 1, n, seg[x], seg[x] + size[x] - 1);
    }
    void Init() {
        root = 1;
        seg[root] = 1;
        top[root] = root;
        rev[1] = root;
        Dfs1(root, 0);
        Dfs2(root, 0);
    }
} Tree;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        u ++, v ++;
        Add(u, v), Add(v, u);
    }
    Tree.Init();
    cin >> m;
    for (int i = 1; i <= m; i ++) {
        char opt;
        cin >> opt;
        if (opt == 'A') {
            int x, y, z;
            cin >> x >> y >> z;
            Tree.Add_Line(x + 1, y + 1, z);
        }
        if (opt == 'Q') {
            int x;
            cin >> x;
            printf("%lld\n", Tree.Query_Tree(x + 1));
        }
    }
    return 0;
}