#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int n, m;

namespace Pts1_2 {
  const int N = 4e4+10;

  int a[N];

  inline int Change(int x, int y) {
    return (x-1)*n+y;
  }

  struct Node {
    int x, y;
    int up, down;
    int left, right;
  };

  int top[30];
  Node node[30][N];

  void Dfs(int x, int y) {
    int cnt = -1, color = a[Change(x, y)];
    top[color]++;
    node[color][top[color]].x = x;
    node[color][top[color]].y = y;
    for (int i = x; i <= n; i++) { // down
      if (a[Change(i, y)] != a[Change(x, y)]) break;
      cnt++;
    }
    node[color][top[color]].down = cnt;
    cnt = -1;
    for (int j = y; j <= m; j++) { // right
      if (a[Change(x, j)] != a[Change(x, j)]) break;
      cnt++;
    }
    node[color][top[color]].right = cnt;
    cnt = -1;
    for (int i = x; i >= 1; i--) { // up
      if (a[Change(i, y)] != a[Change(x, y)]) break;
      cnt++;
    }
    node[color][top[color]].up = cnt;
    cnt = -1;
    for (int j = y; j >= 1; j--) { // left
      if (a[Change(x, j)] != a[Change(x, y)]) break;
      cnt++;
    }
    node[color][top[color]].left = cnt;
    cnt = -1;
    return;
  }
}

signed main() {
  freopen("countcircle.in", "r", stdin);
  freopen("countcircle.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  if (n*m <= 4e4) {
    using namespace Pts1_2;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        char c;
        cin >> c;
        a[Change(i, j)] = c-'a'+1;
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        Dfs(i, j);
        #ifdef __Debug
          printf("a[%d][%d] down=%d up=%d\n", i, j, node[a[Change(i, j)]][top[a[Change(i, j)]]].down, node[a[Change(i, j)]][top[a[Change(i, j)]]].up);
        #endif
      }
    }
    int ans = 0;
    for (int color = 1; color <= 26; color++) {
      for (int i = 1; i <= top[color]; i++) {
        for (int j = i+1; j <= top[color]; j++) {
          if (node[color][i].x!=node[color][j].x&&node[color][i].y!=node[color][j].y) {
            if (node[color][i].x+node[color][i].down>=node[color][j].x) {
              if (node[color][i].y+node[color][i].right>=node[color][j].y) {
                if (node[color][j].x-node[color][j].up<=node[color][i].x) {
                  if (node[color][j].y-node[color][j].left<=node[color][i].y) {
                    ans++;
                    #ifdef __Debug
                      printf("a[%d][%d] a[%d][%d]\n", node[color][i].x, node[color][i].y, node[color][j].x, node[color][j].y);
                    #endif
                    printf("%d\n", ans);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else {
    ll ans = 0;
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        ans += (n-i)*(m-j);
      }
    }
    /*Output*/
    printf("%lld\n", ans);
  }
  /*Init*/
  /*Solve*/
  /*Output*/
  return 0;
}