#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 50;

ll n, m;
ll ans;
int a[N];

void Check(int len) {
  if (len == 0) return;
  for (int i = 1; i <= len-2; i++) {
    if ((a[i]^a[i+1]^a[i+2]) == 0) return;
  }
  #ifdef __Debug
  if (n == 5) {
    for (int i = 1; i <= len; i++) {
      printf("%d ", a[i]);
    }
    printf("\n");
  }
  #endif
  ans++;
  return;
}

void Dfs(int dep, int last) {
  Check(dep-1);
  if (dep == n+1) return;
  for (int i = last+1; i <= n; i++) {
    a[dep] = i;
    Dfs(dep+1, i);
  }
  return;
}
signed main() {
  freopen("xor.in", "r", stdin);
  freopen("xor.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  /*Solve*/
  Dfs(1, 0);
  /*Output*/
  printf("%d\n", ans%m);
  return 0;
}