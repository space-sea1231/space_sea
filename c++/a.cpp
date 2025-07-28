#include <iostream>
#include <stdio.h>
#define __Debug
#define MOD(x) (x % MOD + MOD) % MOD
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;

int Pow(int a, int b) {
  int sum = 1;
  while (b > 0) {
    if (b & 1 == 1) sum = MOD((ll)sum * a);
    a = MOD((ll)a * a);
    b = b >> 1;
  }
  return sum;
}

signed main()
 {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  printf("%lld\n", MOD((ll)24 * Pow(5, MOD - 2)));
  /*Input*/
  /*Init*/
  /*Solve*/
  /*Output*/
  return 0;
}