#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e3 + 10;

int n;

int Pow(int a, int b) {
  int sum = 1;
  while (b > 0) {
    if (b & 1 == 1) sum = sum * a;
    a = a * a;
    b = b >> 1;
  }
  return sum;
}

char c[N][N << 1];

void Dfs(int x, int y, int dep) {
  if (dep == 1) {
    c[x][y] = '/';
    c[x][y + 1] = '\\';
    c[x + 1][y - 1] = '/';
    c[x + 1][y + 2] = '\\';
    c[x + 1][y] = '_';
    c[x + 1][y + 1] = '_';
    return ;
  }
  Dfs(x, y, dep - 1);
  Dfs(x + Pow(2, dep - 1), y - Pow(2, dep - 1), dep - 1);
  Dfs(x + Pow(2, dep - 1), y + Pow(2, dep - 1), dep - 1);
  return ;
}
signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  /*Init*/
  for (int i = 1; i <= Pow(2, n); i++) {
    for (int j = 1; j <= Pow(2, n + 1); j++) {
      c[i][j] = ' ';
    }
  }
  /*Solve*/
  Dfs(1, Pow(2, n), n);
  /*Output*/
  for (int i = 1; i <= Pow(2, n); i++) {
    for (int j = 1; j <= Pow(2, n + 1); j++) {
      printf("%c", c[i][j]);
    }
    printf("\n");
  }
  return 0;
}
/*
   /\
  /__\
 /\  /\
/__\/__\

*/