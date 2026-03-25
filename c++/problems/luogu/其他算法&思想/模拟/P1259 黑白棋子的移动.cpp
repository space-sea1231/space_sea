#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 20;

int n;
char c[][N] = {
  {"ooo*o**--*"},
  {"o--*o**oo*"},
  {"o*o*o*--o*"},
  {"--o*o*o*o*"},
};

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  /*Output*/
  for (int i = 1; i <= ((n - 3) << 1); i++) {
    if (i % 2 == 1) {
      for (int j = 1; j <= n - (i >> 1); j++) printf("o");
      for (int j = 1; j <= n - (i >> 1); j++) printf("*");
      printf("--");
      for (int j = 1; j <= (i >> 1); j++) printf("o*");
      printf("\n");
    }
    if (i % 2 == 0) {
      for (int j = 1; j <= n - (i >> 1); j++) printf("o");
      printf("--");
      for (int j = 1; j <= n - (i >> 1); j++) printf("*");
      for (int j = 1; j <= (i >> 1); j++) printf("o*");
      printf("\n");
    }
  }
  for (int i = 0; i < 4; i++) {
    printf("%s", c[i]);
    for (int j = 1; j <= n - 4; j++) printf("o*");
    printf("\n");
  }
  return 0;
}
/*
ooooooo*******--
oooooo--******o*
oooooo******--o*
ooooo--*****o*o*
ooooo*****--o*o*
oooo--****o*o*o*
oooo****--o*o*o*
ooo--***o*o*o*o*
ooo*o**--*o*o*o*
o--*o**oo*o*o*o*
o*o*o*--o*o*o*o*
--o*o*o*o*o*o*o*

*/