#include <iostream>
#include <stdio.h>
#define __Debug
#define Mod(x) ((ll)x % mod + mod) % mod

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, mod;
int f[N];
int lg[N];
int sum[N];

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  cin >> n >> mod;
  f[0] = 1;
  lg[0] = -1;
  for (int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1];
    for (int j = 0; j < lg[i]; j++) {
      if (i >> j & 1) f[i] = Mod(f[i] - sum[j]);
    }
    sum[lg[i]] = Mod(sum[lg[i]] + f[i]);
    ans = Mod(ans + f[i]);
    f[i] = Mod(f[i] + f[i - 1]);
  }
  printf("%d\n", ans);
  return 0;
}