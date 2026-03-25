#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int k;
int n, m;

void Dfs(int x, int y, int gx, int gy, int siz) {
  if (siz == 0) return;
  if (gx-x+1 <= (1<<(siz-1))) { // 上
    if (gy-y+1 <= (1<<(siz-1))) { // 左上
      printf("%d %d %d\n", x+(1<<(siz-1)), y+(1<<(siz-1)), 1);
      Dfs(x, y, gx, gy, siz-1);
      Dfs(x, y+(1<<(siz-1)), x+(1<<(siz-1))-1, y+(1<<(siz-1)), siz-1);
      Dfs(x+(1<<(siz-1)), y, x+(1<<(siz-1)), y+(1<<(siz-1))-1, siz-1);
      Dfs(x+(1<<(siz-1)), y+(1<<(siz-1)), x+(1<<(siz-1)), y+(1<<(siz-1)), siz-1);
    }
    if (gy-y+1 > (1<<(siz-1))) { // 右上
      printf("%d %d %d\n", x+(1<<(siz-1)), y+(1<<(siz-1))-1, 2);
      Dfs(x, y+(1<<(siz-1)), gx, gy, siz-1);
      Dfs(x, y, x+(1<<(siz-1))-1, y+(1<<(siz-1))-1, siz-1);
      Dfs(x+(1<<(siz-1)), y, x+(1<<(siz-1)), y+(1<<(siz-1))-1, siz-1);
      Dfs(x+(1<<(siz-1)), y+(1<<(siz-1)), x+(1<<(siz-1)), y+(1<<(siz-1)), siz-1);
    }
  }
  if (gx-x+1 > (1<<(siz-1))) { // 下
    if (gy-y+1 <= (1<<(siz-1))) { // 左下
      printf("%d %d %d\n", x+(1<<(siz-1))-1, y+(1<<(siz-1)), 3);
      Dfs(x+(1<<(siz-1)), y, gx, gy, siz-1);
      Dfs(x, y, x+(1<<(siz-1))-1, y+(1<<(siz-1))-1, siz-1);
      Dfs(x, y+(1<<(siz-1)), x+(1<<(siz-1))-1, y+(1<<(siz-1)), siz-1);
      Dfs(x+(1<<(siz-1)), y+(1<<(siz-1)), x+(1<<(siz-1)), y+(1<<(siz-1)), siz-1);
    }
    if (gy-y+1 > (1<<(siz-1))) { // 右下
      printf("%d %d %d\n", x+(1<<(siz-1))-1, y+(1<<(siz-1))-1, 4);
      Dfs(x+(1<<(siz-1)), y+(1<<(siz-1)), gx, gy, siz-1);
      Dfs(x, y, x+(1<<(siz-1))-1, y+(1<<(siz-1))-1, siz-1);
      Dfs(x, y+(1<<(siz-1)), x+(1<<(siz-1))-1, y+(1<<(siz-1)), siz-1);
      Dfs(x+(1<<(siz-1)), y, x+(1<<(siz-1)), y+(1<<(siz-1))-1, siz-1);
    }
  }
}
signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> k >> n >> m;
  /*Solve*/
  Dfs(1, 1, n, m, k);
  return 0;
}
/*
(1,1)(1,2)(1,3)(1,4)
(2,1)(2,2)(2,3)(1,4)
(3,1)(3,2)(3,3)(1,4)
(4,1)(4,2)(4,3)(4,4)
Dfs(x, y, gx, gy, siz-1);
Dfs(x, y+(1<<siz), x+(1<<siz)-1, y+(1<<siz), siz-1);
Dfs(x+(1<<siz), y, x+(1<<siz), y+(1<<siz)-1, siz-1);
Dfs(x+(1<<siz), y+(1<<siz), x+(1<<siz), y+(1<<siz), siz-1);
*/