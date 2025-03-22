#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
int n, m, r, q;
int cnt;
int a[N];
int head[N], to[N << 1], nxt[N << 1];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
struct Segment_Tree {
    struct Node {
        int sum, vis;
    } e[N << 1];
    void Build(int x, int l, int r, int rev[]) {
        if (l == r) {
            e[x].sum = a[rev[l]] % q;
            return;
        }
        int mid = (l + r) >> 1;
        Build(x << 1, l, mid, rev);
        Build(x << 1 | 1, mid + 1, r, rev);
        e[x].sum = (e[x << 1].sum + e[x << 1 | 1].sum) % q;
    }
    void Down(int x, int l, int r) {
        int mid = (l + r) >> 1;
        e[x << 1].vis = (e[x << 1].vis + e[x].vis) % q;
        e[x << 1 | 1].vis = (e[x << 1 | 1].vis + e[x].vis) % q;
        e[x << 1].sum = (e[x << 1].sum + (mid - l + 1) * e[x].vis) % q;
        e[x << 1 | 1].sum = (e[x << 1 | 1].sum + (r - mid) * e[x].vis) % q;
        e[x].vis = 0;
    }
    void Add(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            e[x].vis ++;
            e[x].sum += r - l + 1;
            return;
        }
        Down(x, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) {
            Add(x << 1, l, mid, L, R);
        }
        if (mid + 1 <= R) {
            Add(x << 1 | 1, mid + 1, r, L, R);
        }
        e[x].sum = (e[x << 1].sum + e[x << 1 | 1].sum) % q;
    }
    int Query(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return e[x].sum;
        }
        Down(x, l, r);
        int mid = (l + r) >> 1, ans = 0;
        if (L <= mid) {
            ans = (ans + Query(x << 1, l, mid, L, R)) % q;
        }
        if (mid + 1 <= R) {
            ans = (ans + Query(x << 1 | 1, mid + 1, r, L, R)) % q;
        }
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
            if (v == fa) continue;
            Dfs1(v, u);
            size[u] += size[v];
            if (size[v] > size[son[u]]) {
                son[u] = v;
            }
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
            if (v == fa || v == son[u]) continue;
            top[v] = v;
            seg[v] = ++num;
            rev[num] = v;
            Dfs2(v, u);
        }
    }
    void Add_Line(int x, int y) {
        int fx = top[x], fy = top[y];
        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                swap(fx, fy);
                swap(x, y);
            }
            Seg.Add(1, 1, n, seg[fx], seg[x]);
            x = father[top[x]], fx = top[x];
        }
        if (dep[x] > dep[y]) swap(x, y);
        Seg.Add(1, 1, n, seg[x], seg[y]);
    }
    void Add_Tree(int x, int z) {
        Seg.Add(1, 1, n, seg[x], seg[x] + size[x] - 1, z);
    }
    int Query_Tree(int x) {
        return Seg.Query(1, 1, n, seg[x], seg[x] + size[x] - 1);
    }
    int Query_Line(int x, int y) {
        int fx = top[x], fy = top[y], ans = 0;
        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                swap(fx, fy);
                swap(x, y);
            }
            ans = (ans + Seg.Query(1, 1, n, seg[fx], seg[x])) % q;
            x = father[top[x]], fx = top[x];
        }
        if (dep[x] > dep[y]) {
            swap(x, y);
        }
        ans = (ans + Seg.Query(1, 1, n, seg[x], seg[y])) % q;
        return ans;
    }
    void Init() {
        root = r;
        seg[root] = 1;
        top[root] = root;
        rev[1] = root;
        Dfs1(root, 0);
        Dfs2(root, 0);
        Seg.Build(1, 1, n, rev);
    }
} Tree;
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Tree.Init();
    for (int i = 1; i <= n; i++) {
        Tree.Add_Line(a[i - 1], a[i]);
    }
    for (int i = 1; i <= n; i ++) {
        printf("%d\n", Tree.)
    }
    return 0;
}