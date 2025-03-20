#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int MAXN = 500010;
constexpr int INF = 0x3f3f3f3f;

int Begin[MAXN], Next[MAXN], To[MAXN], e, n, m;
int sz[MAXN], son[MAXN], top[MAXN], fa[MAXN], dep[MAXN], seg[MAXN], rev[MAXN],
    End[MAXN];
// seg[i]表示i树剖后的编号，id[seg[i]] = i
int cnt, tot, a[MAXN], f[MAXN][2];

struct Node {
  int g[2][2];

  Node() { memset(g, 0, sizeof(g)); }

  Node operator*(const Node &b) const  // 重载矩阵乘
  {
    Node c;
    for (int i = 0; i <= 1; i++)
      for (int j = 0; j <= 1; j++)
        for (int k = 0; k <= 1; k++)
          c.g[i][j] = max(c.g[i][j], g[i][k] + b.g[k][j]);
    return c;
  }
} Tree[MAXN], g[MAXN];  // Tree[]是建出来的线段树，g[]是维护的每个点的矩阵

void PushUp(int root) { Tree[root] = Tree[root << 1] * Tree[root << 1 | 1]; }

void Build(int root, int l, int r) {
  if (l == r) {
    Tree[root] = g[rev[l]];
    return;
  }
  int Mid = (l + r) >> 1;
  Build(root << 1, l, Mid);
  Build(root << 1 | 1, Mid + 1, r);
  PushUp(root);
}

Node Query(int root, int l, int r, int L, int R) {
  if (L <= l && r <= R) return Tree[root];
  int Mid = (l + r) >> 1;
  if (R <= Mid) return Query(root << 1, l, Mid, L, R);
  if (Mid < L) return Query(root << 1 | 1, Mid + 1, r, L, R);
  return Query(root << 1, l, Mid, L, R) *
         Query(root << 1 | 1, Mid + 1, r, L, R);
  // 注意查询操作的书写
}

void Modify(int root, int l, int r, int pos) {
  if (l == r) {
    Tree[root] = g[rev[l]];
    return;
  }
  int Mid = (l + r) >> 1;
  if (pos <= Mid)
    Modify(root << 1, l, Mid, pos);
  else
    Modify(root << 1 | 1, Mid + 1, r, pos);
  PushUp(root);
}

void Update(int x, int val) {
  g[x].g[1][0] += val - a[x];
  a[x] = val;
  // 首先修改x的g矩阵
  while (x) {
    Node last = Query(1, 1, n, seg[top[x]], End[top[x]]);
    // 查询top[x]的原本g矩阵
    Modify(1, 1, n,
           seg[x]);  // 进行修改(x点的g矩阵已经进行修改但线段树上的未进行修改)
    Node now = Query(1, 1, n, seg[top[x]], End[top[x]]);
    // 查询top[x]的新g矩阵
    x = fa[top[x]];
    g[x].g[0][0] +=
        max(now.g[0][0], now.g[1][0]) - max(last.g[0][0], last.g[1][0]);
    g[x].g[0][1] = g[x].g[0][0];
    g[x].g[1][0] += now.g[0][0] - last.g[0][0];
    // 根据变化量修改fa[top[x]]的g矩阵
  }
}

void add(int u, int v) {
  To[++e] = v;
  Next[e] = Begin[u];
  Begin[u] = e;
}

void DFS1(int u) {
  sz[u] = 1;
  int Max = 0;
  f[u][1] = a[u];
  for (int i = Begin[u]; i; i = Next[i]) {
    int v = To[i];
    if (v == fa[u]) continue;
    dep[v] = dep[u] + 1;
    fa[v] = u;
    DFS1(v);
    sz[u] += sz[v];
    if (sz[v] > Max) {
      Max = sz[v];
      son[u] = v;
    }
    f[u][1] += f[v][0];
    f[u][0] += max(f[v][0], f[v][1]);
    // DFS1过程中同时求出f[i][0/1]
  }
}

void DFS2(int u, int t) {
  top[u] = t;
  seg[u] = ++cnt;
  rev[cnt] = u;
  End[t] = cnt;
  g[u].g[1][0] = a[u];
  g[u].g[1][1] = -INF;
  if (!son[u]) return;
  DFS2(son[u], t);
  for (int i = Begin[u]; i; i = Next[i]) {
    int v = To[i];
    if (v == fa[u] || v == son[u]) continue;
    DFS2(v, v);
    g[u].g[0][0] += max(f[v][0], f[v][1]);
    g[u].g[1][0] += f[v][0];
    // g矩阵根据f[i][0/1]求出
  }
  g[u].g[0][1] = g[u].g[0][0];
}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  dep[1] = 1;
  DFS1(1);
  DFS2(1, 1);
  for (int i=1; i<=n; i++){
    printf("%d %d %d %d\n", g[i].g[0][0], g[i].g[1][0], g[i].g[0][1], g[i].g[1][1]);
  }
  Build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    int x, val;
    cin >> x >> val;
    Update(x, val);
    Node ans = Query(1, 1, n, 1, End[1]);  // 查询1所在重链的矩阵乘
    // printf("%d %d %d %d\n", ans.g[0][0], ans.g[1][1], ans.g[1][0], ans.g[0][1]);
    cout << max(ans.g[0][0], ans.g[1][0]) << '\n';
  }
  return 0;
}