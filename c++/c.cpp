#include <iostream>
#include <stdio.h>
#define __Debug
#define Mod(x) (x % MOD + MOD) % MOD
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;

int n, m;
int sum;
int Pow(int a, int b) {
  int sum = 1;
  while (b > 0) {
    if (b & 1 == 1) sum = Mod((ll)sum * a);
    a = Mod((ll)a * a);
    b = b >> 1;
  }
  return sum;
}

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  /*Init*/
  sum = Mod(Pow(2, n) - 1);
  int ans = 1;
  /*Solve*/
  for (int i = 0; i < n; i++) {
    int res=Mod(Pow(sum, m)-Pow(Mod(sum+Pow(2, i)), m));
    ans=Mod(ans*Mod(Pow(sum, Mod-2)));
  }
  printf("%d\n", ans);
  /*Output*/
  return 0;
}