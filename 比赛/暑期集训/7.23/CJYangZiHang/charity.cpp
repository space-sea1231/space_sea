#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int M = 1e3 + 10;
const int INF = 0x3f3f3f3f;

int cnt;
int head[N], to[N << 1], nxt[N << 1];

void Add(int u, int v) {
  to[++cnt] = v;
  nxt[cnt] = head[u];
  head[u] = cnt;
}

int dis[M][M][2];

void Dfs(int u, int fa, int root){
  for (int i = head[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) continue;
    dis[root][v][0] = max(dis[root][u][0], v);
    dis[root][v][1] = min(dis[root][u][1], v);
    Dfs(v, u, root);
  }
}

int n;
int ru[N];

signed main() {
  freopen("charity.in", "r", stdin);
  freopen("charity.out", "w", stdout);
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++){
    int v;
    cin >> v;
    ru[i]++;
    ru[v]++;
    if (v == 0) continue;
    Add(i, v);
    Add(v, i);
  }
  for (int i = 1; i <= n; i++){
    if (ru[i] == n - 1) {
      printf("%d\n", n - 1 + (i - 1) * (n - i));
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dis[i][j][0] = max(i, j);
      dis[i][j][1] = min(i, j);
    }
  }
  for (int i = 1; i <= n; i++) {
    Dfs(i, 0, i);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      int x = i, y = j;
      if (dis[x][y][0] == y && dis[x][y][1] == x) {
        // printf("Debug: %d %d\n", x, y);
        ans++;
      }
      // printf("dis[%d][%d] max=%d min=%d\n", x, y, dis[x][y][0], dis[x][y][1]);
    }
  }
  printf("%d\n", ans);

  return 0;
}