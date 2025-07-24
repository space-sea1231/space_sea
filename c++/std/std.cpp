#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 70;
const int M = 1e2 + 10;

int ans;
int n, m, k, q;

struct Node { // 格子信息
  int color; // 颜色
  int effect; // 特殊效果
  bool exist; // 存在标记
  bool flag; // 消除标记
};

Node node[N][N];
vector<pair<int, int> > del;

int Pow(int a, int b) {
  int sum = 1;
  while (b > 0) {
    if (b & 1 == true) {
      sum = sum * a;
    }
    a = a * a;
    b = b >> 1;
  }
  return sum;
}

bool Over() {// 当前局面稳定
  /*Solve*/
  bool flag = true; // 未出现可消除方块
  for (int i = 1; i <= n; i++) {
    int l = 1;
    for (int r = 1; r <= m; r++) {
      if (node[i][r].exist == false) {
        l = r + 1;
        continue;
      }
      if (node[i][r].color != node[i][r + 1].color || node[i][r + 1].exist == false) {
        if (r - l + 1 >= 3) {
          for (int k = l; k <= r; k++) {
            del.push_back(make_pair(i, k));
            node[i][k].flag = true;
            flag = false;
          }
        }
        l = r + 1;
      }
    }
  }
  for (int j = 1; j <= m; j++) {
    int l = 1;
    for (int r = 1; r <= n; r++) {
      if (node[r][j].exist == false) {
        l = r + 1;
        continue;
      }
      if (node[r][j].color != node[r + 1][j].color) {
        if (r - l + 1 >= 3) {
          for (int k = l; k <= r; k++) {
            if (node[k][j].flag == false) {
              del.push_back(make_pair(k, j));
            }
            node[k][j].flag = true;
            flag = false;
          }
        }
        l = r + 1;
      }
    }
  }
  return flag;
}

bool vis[N][N];
int cnt, sum;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
vector<pair<int, int> > eff;


bool Check(int x, int y) {
  return x >= 1 && x <= n && y >= 1 && y <= m
      && vis[x][y] == false && node[x][y].exist == true
      && node[x][y].flag == true;
}

void Dfs(int x, int y) {
  if (node[x][y].effect > 0) {
    eff.push_back(make_pair(x, y));
  }
  sum += node[x][y].color;
  cnt++;
  node[x][y].exist = false;
  vis[x][y] = true;
  for (int i = 0; i < 4; i++) {
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (Check(xx, yy) && node[xx][yy].color == node[x][y].color) {
      Dfs(xx, yy);
    }
  }
  return;
}

void Remove() {// 移除方块
  /*Init*/
  eff.clear();
  eff.reserve(1e6);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      vis[i][j] = false;
    }
  }
  /*Solve*/
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (vis[i][j] == true) continue;
      if (node[i][j].flag == false) continue;
      cnt = 0;
      Dfs(i, j);
      ans += 50 * Pow((cnt - 3), 2);
      #ifdef __Debug
        printf("Score from #3: %d sum=%d\n", 50 * Pow((cnt - 3), 2), ans);
      #endif
    }
  }
  int siz = eff.size();
  for (int i = 0; i < siz; i++) {
    pair<int,int> idx = eff[i];
    int x = idx.first;
    int y = idx.second;
    Node tmp = node[x][y];
    if (tmp.effect == 1) {
      for (int j = 1; j <= m; j++){
        if (node[x][j].exist == true) {
          if (node[x][j].effect > 0) {
            eff.push_back(make_pair(x, j));
          }
          node[x][j].exist = false;
          sum += node[x][j].color;
        }
      }
    }
    if (tmp.effect == 2) {
      for (int i = 1; i <= n; i++){
        if (node[i][y].exist == true) {
          if (node[i][y].effect > 0) {
            eff.push_back(make_pair(i, y));
          }
          node[i][y].exist = false;
          sum += node[i][y].color;
        }
      }
    }
    if (tmp.effect == 3) {
      for (int i = 1; i <= n; i++){
        if (node[i][y].exist == true) {
          if (node[i][y].effect > 0) {
            eff.push_back(make_pair(i, y));
          }
          node[i][y].exist = false;
          sum += node[i][y].color;
        }
      }
      for (int j = 1; j <= m; j++){
        if (node[x][j].exist == true) {
          if (node[x][j].effect > 0) {
            eff.push_back(make_pair(x, j));
          }
          node[x][j].exist = false;
          sum += node[x][j].color;
        }
      }
    }
    if (tmp.effect == 4) {
      for (int i = max(1, x - 1); i <= min(n, x + 1); i++) {
        for (int j = max(1, y - 1); j <= min(m, y + 1); j++) {
          if (node[i][j].exist == true) {
            if (node[i][j].effect > 0) {
              eff.push_back(make_pair(i, j));
            }
            node[i][j].exist = false;
            sum += node[i][j].color;
          }
        }
      }
    }
    if (tmp.effect == 5) {
      for (int i = max(1, x - 2); i <= min(n, x + 2); i++) {
        for (int j = max(1, y - 2); j <= min(m, y + 2); j++) {
          if (node[i][j].exist == true) {
            if (node[i][j].effect > 0) {
              eff.push_back(make_pair(i, j));
            }
            node[i][j].exist = false;
            sum += node[i][j].color;
          }
        }
      }
    }
    if (tmp.effect == 6) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          if (node[i][j].color == tmp.color) {
            if (node[i][j].exist == true) {
              if (node[i][j].effect > 0) {
                eff.push_back(make_pair(i, j));
              }
              node[i][j].exist = false;
              sum += node[i][j].color;
            }
          }
        }
      }
    }
  }
  return;
}

void Fall() {
  for (int j = 1; j <= m; j++) {
    for (int i = n; i >= 1; i--) {
      if (node[i][j].exist == true) {
        int tmp = i;
        while (tmp <= n - 1 && node[tmp + 1][j].exist == false) {
          swap(node[tmp][j], node[tmp + 1][j]);
          tmp++;
        }
      }
    }
  }
  return;
}

int tmp;
int combo[5];
int bucket[M];

void Count() {
  int cnt1 = 0, cnt2 = 0;
  int id1 = 0, id2_1 = 0, id2_2, id3 = 0, id4 = 0, id5 = 0;
  for (int i = 0; i < 5; i++) {
    bucket[combo[i]]++;
  }
  for (int i = 1; i <= 100; i++) {
    if (bucket[i] == 1) {
      id1 = max(id1, i);
      cnt1++;
    }
    if (bucket[i] == 2) {
      if (id2_1 == 0) id2_1 = i;
      else id2_2 = i;
      cnt2++;
    }
    if (bucket[i] == 3) {
      id3 = i;
    }
    if (bucket[i] == 4) {
      id4 = i;
    }
    if (bucket[i] == 5) {
      id5 = i;
    }
    bucket[i] = 0;
  }
  if (cnt1 == 5) tmp = max(tmp, 50 + id1);
  if (cnt1 == 3 && cnt2 == 1) tmp = max(tmp, 100 + (id2_1 << 1));
  if (cnt1 == 1 && cnt2 == 2) tmp = max(tmp, 200 + (id2_2 << 1) + id2_1);
  if (cnt1 == 2 && id3 > 0) tmp = max(tmp, 300 + id3 * 3);
  if (cnt2 == 1 && id3 > 0) tmp = max(tmp, 500 + id3 * 3 + (id2_1));
  if (cnt1 == 1 && id4 > 0) tmp = max(tmp, 750 + id4 * 5);
  if (id5 > 0) tmp = max(tmp, 1000 + id5 * 10);
  return;
}

int id[5][2];

void Dfs1(int dep) {
  if (dep == 5) { Count(); return; }
  if (id[dep][0] > 0) { combo[dep] = id[dep][0]; Dfs1(dep + 1); }
  if (id[dep][1] > 0) { combo[dep] = id[dep][1]; Dfs1(dep + 1); }
  return;
}

void Init() {
  for (pair<int, int> idx:del) {
    int x = idx.first;
    int y = idx.second;
    node[x][y].flag = false;
  }
  del.clear();
  return;
}

void Debug(int x) {
  printf("-----Round:%d---------\n", x);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      printf("%d", node[i][j].flag);
    }
    printf("\n");
  }
}
signed main() {
  freopen("std.in","r",stdin);
  freopen("std.out","w",stdout);
  // cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m >> k >> q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> node[i][j].color;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> node[i][j].effect;
    }
  }
  /*Init*/
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      node[i][j].exist = true;
    }
  }
  #ifdef __Debug
    printf("### round = %d; score = %d\n", q, ans);
    for (int i = 1; i <= n; i++) {
      for (int j  = 1; j <= m; j++) {
        if (node[i][j].exist == true) {
          printf("(%3d,%3d,%3d)", node[i][j].exist, node[i][j].color, node[i][j].effect);
        }
        else printf("             ");
      }
      printf("\n");
    }
  #endif
  /*Solve*/
  bool flag = true; // 均为有效操作
  int tot = 0;
  for (int k = 1; k <= q; k++) {
    int sx, sy, fx, fy;
    cin >> sx >> sy >> fx >> fy;
    if (abs(sx - fx) + abs(sy - fy) > 1) {
      flag = false;
      continue;
    }
    if (node[sx][sy].exist == false || node[fx][fy].exist == false){
      flag = false;
      continue;
    }
    swap(node[sx][sy], node[fx][fy]);
    int num = 0;
    while (Over() == false){
      num++;
      #ifdef __Debug
      Debug(num);
      #endif
      if (num == 1) {
        if (node[sx][sy].flag == true) id[tot % 5][0] = node[sx][sy].color;
        if (node[fx][fy].flag == true) id[tot % 5][1] = node[fx][fy].color;
      }
      Remove();
      Init(), Fall();
      ans += num * sum;
      #ifdef __Debug
        printf("Score from #1: %d sum=%d\n", num * sum, ans);
      #endif
      sum = 0;
    }
    if (num == 0){
      swap(node[sx][sy], node[fx][fy]);
      flag = false;
      continue;
    }
    ans += 80 * Pow((num - 1), 2);
    #ifdef __Debug
      printf("Score from #2: %d sum=%d\n", 80 * Pow((num - 1), 2), ans);
    #endif
    tot++;
    if (tot % 5 == 0){
      /*Init*/
      tmp = 0;
      /*Solve*/
      Dfs1(0);
      for (int j = 0; j <= 4; j++) {
        id[j][0] = id[j][1] = 0;
      }
      ans += tmp;
      #ifdef __Debug
        printf("Score from #4: %d sum=%d\n",tmp, ans);
      #endif
    }
    #ifdef __Debug
      printf("### round = %d; score = %d\n", k, ans);
      for (int i = 1; i <= n; i++) {
        for (int j  = 1; j <= m; j++) {
          if (node[i][j].exist == true) {
            printf("(%3d,%3d,%3d)", node[i][j].color, node[i][j].effect, node[i][j].exist);
          }
          else printf("             ");
        }
        printf("\n");
      }
    #endif
  }
  if (flag == true) ans += 1000;
  bool flag1 = true; // 所有方块均已消除
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (node[i][j].exist == true) {
        flag1 = false;
        i = n, j = m;
      }
    }
  }
  if (flag1 == true) ans += 10000;
  printf("%d\n", ans);

  return 0;
}
/*
### id = 0
1 1 5 1 5 4 5 3
2 1 2 2 5 4 3 2
1 4 1 4 2 1 5 4
2 1 5 5 2 1 4 4
2 3 5 2 3 4 2 2
4 2 4 3 3 2 4 5
1 3 4 3 5 2 4 3
3 4 2 5 2 1 1 2

### id = 1
0 0 0 1 5 4 5 3
0 0 5 2 5 4 3 2
0 0 2 4 2 1 5 4
0 4 5 5 2 1 4 4
0 3 5 2 3 4 2 2
0 2 4 3 3 2 4 5
0 3 4 3 5 2 4 3
0 4 2 5 2 1 1 2

0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
2 0 0 0 5 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 6 0 0 3 1
0 0 0 0 3 0 0 0
0 0 0 0 0 0 1 4

*/