#include <iostream>
#include <stdio.h>
#define __Debug
#define Mod(x) (x % MOD + MOD) % MOD
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;

ll n, m;
ll sum;

ll Pow(ll a, ll b) {
  ll sum = 1;
  while (b > 0) {
    if (b & 1 == 1) sum = Mod(sum * a);
    a = Mod(a * a);
    b = b >> 1;
  }
  return sum;
}

signed main() {
  freopen("glass.in", "r", stdin);
  freopen("glass.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  /*Init*/
  sum = Mod(Pow(2, n) - 1);
  ll ans = 1;
  /*Solve*/
  for (int i = 0; i < n; i++) {
    int res = (Pow(sum, m) - Pow(((sum - Pow(2, i))+MOD)%MOD, m)+MOD)%MOD;
    ans = Mod((ll)ans * Mod((ll)res * Pow(sum, MOD - 2)));
  }
  printf("%lld\n", Mod(ans * Pow(sum, m)));
  /*Output*/
  return 0;
}