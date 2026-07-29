#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e3 + 10;

int n, m;
int f[N][N];

void Floyd() {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      if (i == k) continue;
      for (int j = 1; j <= n; j++) {
        if (k == j) continue;
        f[i][j]=min(f[i][j], f[i][k]+f[k][j]);
      }
    }
  }
}
signed main() {
  freopen("happybean.in", "r", stdin);
  freopen("happybean.out", "w", stdout);
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  cin >> n >> m;
  if (m == 0) {
    printf("%lld\n", (ll)n*(n+1)/2*(n-1));
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    for (int j = 1; j <= n; j++){
      if (i == j) f[i][j] = 0;
      else f[i][j] = x;
    }
  }
  for (int i = 1; i <= m; i++){
    int x, y, z;
    cin >> x >> y >> z;
    f[x][y]=z;
  }
  Floyd();
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      ans += f[i][j];
    }
  }
  printf("%d\n", ans);

  return 0;
}