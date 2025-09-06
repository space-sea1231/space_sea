#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
int a[N][4];
int f[N];

signed main() {
  freopen("coin.in", "r", stdin);
  freopen("coin.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i][1];
  for (int i = 1; i <= n; i++) cin >> a[i][2];
  /*Init*/
  for (int i = 1; i <= n; i++) {
    a[i][2] = a[i][1] + a[i][2];
    a[i][3] = a[i][2] + a[i][1];
  }
  /*Solve*/
  int tmp = min(m, n * 3);
  for (int i = 1; i <= n; i++) {
    for (int j = tmp; j >= 1; j--) {
      f[j] = max(f[j], f[j - 1] + a[i][1]);
      if (j >= 2) f[j] = max(f[j], f[j - 2] + a[i][2]);
      if (j >= 3) f[j] = max(f[j], f[j - 3] + a[i][3]);
    }
    #ifdef __Debug
    printf("i:%d\n", i);
    for (int i = 1; i <= m; i++) {
      printf("f[%d]=%d\n", i, f[i]);
    }
    printf("\n");
    #endif
  }
  for (int i = tmp + 1; i <= m; i++) {
    f[i] = f[tmp];
  }
  /*Output*/
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    ans = ans ^ f[i];
    #ifdef __Debug
    printf("f[%d]=%d\n", i, f[i]);
    #endif
  }
  printf("%d\n", ans);
  return 0;
}
/*
100 1 100
99 1 99
*/