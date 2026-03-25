#include <iostream>
#include <stdio.h>
#define __Debug
#define Mod(x) ((ll)x%MOD+MOD)%MOD

using namespace std;
typedef long long ll;

const int N = 1e7 + 10;
const int MOD = 1e4;

int n;
int f[N][3];

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  /*Init*/
  f[0][1] = 1;
  f[1][1] = 1;
  /*Solve*/
  for (int i = 2; i <= n; i++) {
    f[i][0] = Mod(f[i - 1][0] + (f[i - 2][1] << 1));
    f[i][1] = Mod(f[i - 1][1] + f[i - 2][1] + f[i - 1][0]);
  }
  /*Output*/
  printf("%d\n", f[n][1]);

  return 0;
}