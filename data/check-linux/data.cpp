#include <iostream>
#include <cstring>

using namespace std;
typedef long long ll;

const int N = 100;
const int M = 20;

int player[N];
bool vis[N];
bool flag[N][N];

int Random(int l, int r){
  return rand()%(r - l + 1) + l;//生成随机数
}

void Init() {
  memset(vis, 0, sizeof(vis));
  memset(flag, 0, sizeof(flag));
  return ;
}

signed main() {
  srand(time(NULL));//随机种子
  int id = 0;
  int t = N;
  int n = M;
  printf("%d %d %d\n", id, t, n);
  for (int i = 1; i <= n; i++){
    printf("%c\n", 'A' + i - 1);
  }
  while (t--) {
    Init();
    for (int i = 1; i <= 3; i++) {
      while (vis[player[i] = Random(1, n)] == true);
      vis[player[i]] = true;
    }
    for (int i = 1; i <= 3; i++) {
      printf("%c\n", player[i] + 'A' - 1);
      for (int j = 1; j <= 5; j++) {
        int color, point;
        while (flag[color = Random(1, 4)][point = Random(1, 10)] == true);
        flag[color][point] = true;
        if (point == 1) printf("%c%c ", color + 'a' - 1, 'A');
        else printf("%c%d ", color + 'a' - 1, point);
      }
      printf("\n");
    }
  }
  return 0;
}