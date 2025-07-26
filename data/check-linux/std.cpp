#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <unordered_map>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int M = 20;

int id, t, n;
int table[M];
int bucket[N];
unordered_map<string, int> cor;

struct Player {
  string name;
  int score;
  int type;
  int mxpoint;
  int mxcolor;

  struct Card {
    int color;
    int point;
  };

  Card card[M];
};

Player player[N];
vector<int> vec;

int Check(Player *cur) {
  int sum = 0;
  for (int i = 1; i <= 5; i++) {
    if (i != vec[0] && i != vec[1] && i != vec[2]) {
      sum = sum + cur->card[i].point;
    }
  }
  sum = sum % 10;
  #ifdef __Debug
  if (cur->name == "D") {
    printf("Debug1: card[%d]=%d card[%d]=%d card[%d]=%d sum=%d\n", vec[0], cur->card[vec[0]].point, vec[1], cur->card[vec[1]].point, vec[2], cur->card[vec[2]].point, sum);
  }
  #endif
  if (cur->card[vec[0]].point == cur->card[vec[1]].point && cur->card[vec[1]].point == cur->card[vec[2]].point) { // 铁板
    if (sum == 0) return 1000 + (vec[0] * 10) - 1;
    if (sum > 0) return sum * 100 + vec[0] * 10 - 1; // 防撞衫炸弹&&牛牛
  }
  if ((cur->card[vec[0]].point + cur->card[vec[1]].point + cur->card[vec[2]].point) % 10 == 0) { // 十的倍数
    if (sum == 0) return 1000;
    if (sum > 0) return sum * 100;
  }
  return 0; // 无牛
}

int Search(Player *cur, int dep, int cnt) {
  if (dep == 6) {
    return Check(cur);
  }
  int sum = 0;
  if (cnt < 3) {
    vec.push_back(dep);
    sum = max(sum, Search(cur, dep + 1, cnt + 1));
    vec.pop_back();
  }
  if (6 - dep + cnt > 3) {
    sum = max(sum, Search(cur, dep + 1, cnt));
  }
  return sum;
}

bool Compare(Player *srca, Player *srcb) {
  if (srca->type != srcb->type) return srca->type > srcb->type;
  if (srca->mxpoint != srcb->mxpoint) return srca->mxpoint > srcb->mxpoint;
  if (srca->mxcolor != srcb->mxcolor) return srca->mxcolor < srcb->mxcolor; 
  return true;
}

void Duel(Player *srca, Player *srcb) {
  int sum = 10;
  if (Compare(srca, srcb) == true) {
    if (srca->type > 1100) { // 炸弹
      sum = sum * 10;
    }
    if (1000 <= srca->type && srca->type <= 1100) { // 牛牛
      sum = sum * 3;
    }
    if (700 <= srca->type && srca->type < 1000) { // 牛数1
      sum = sum * 2;
    }
    if (0 < srca->type && srca->type < 700) { // 牛数2
      sum = sum;
    }
    if (srca->type == 0) { // 无牛
      sum = sum;
    }
    if (srca->type % 10 > 0) sum = sum * 2;
    srca->score = srca->score + sum;
    srcb->score = srcb->score - sum;
  }
  if (Compare(srca, srcb) == false) {
    if (srcb->type > 1100) { // 炸弹
      sum = sum * 10;
    }
    if (1000 <= srcb->type && srcb->type <= 1100) { // 牛牛
      sum = sum * 3;
    }
    if (700 <= srcb->type && srcb->type < 1000) { // 牛数1
      sum = sum * 2;
    }
    if (0 < srcb->type && srcb->type < 700) { // 牛数2
      sum = sum;
    }
    if (srcb->type == 0) { // 无牛
      sum = sum;
    }
    if (srcb->type % 10 > 0) sum = sum * 2;
    srca->score = srca->score - sum;
    srcb->score = srcb->score + sum;
  }
  #ifdef __Debug
    printf("%s(%d) vs %s(%d): %d  winer is %s\n", srca->name.c_str(), srca->type, srcb->name.c_str(), srcb->type, sum, (Compare(srca, srcb)==1?srca->name.c_str():srcb->name.c_str()));
  #endif
  return ;
}

void Init(Player *src) {
  src->type = 0;
  src->mxpoint = 0;
  src->mxcolor = 0;
  return ;
}

signed main() {
  // freopen("std1.out", "w", stdout);
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  /*Input*/
  cin >> id >> t >> n;
  for (int i = 1; i <= n; i++) {
    cin >> player[i].name;
    cor[player[i].name] = i;
  }
  string name, card;
  while (t--) {
    for (int i = 1; i <= 3; i++) {
      cin >> name;
      table[i] = cor[name];
      Player *cur = &player[table[i]];
      for (int j = 1; j <= 5; j++) {
        cin >> card;
        cur->card[j].color = card[0] - 'a';
        if (card.substr(1) == "A") cur->card[j].point = 1;
        else cur->card[j].point = atoi(card.substr(1).c_str());
      }
    }
    /*Init*/
    // for (int i = 1; i <= 3; i++) Init(&player[table[i]]);
    #ifdef __Debug
      for (int i = 1; i <= 3; i++) {
        Player *cur = &player[table[i]];
        printf("%s\n", cur->name.c_str());
        for (int j = 1; j <= 5; j++) {
          printf("%d:%d\n", cur->card[j].color, cur->card[j].point);
        }
      }
      printf("\n");
    #endif
    /*Solve*/
    for (int i = 1; i <= 3; i++) {
      Player *cur = &player[table[i]];
      cur->type = Search(cur, 1, 0);
      for (int j = 1; j <= 5; j++) {
        if (cur->mxpoint < cur->card[j].point || (cur->mxpoint == cur->card[j].point && cur->mxcolor > cur->card[j].color)) { // 最大点数和最大花色
          cur->mxpoint = cur->card[j].point;
          cur->mxcolor = cur->card[j].color;
        }
        bucket[cur->card[j].point]++;
        if (bucket[cur->card[j].point] == 4) { // 炸弹
          cur->type = (cur->card[j].point + 1) * 1000;
        }
      }
      /*Init*/
      for (int j = 1; j <= 5; j++) bucket[cur->card[j].point]--;
    }
    Duel(&player[table[1]], &player[table[2]]);
    Duel(&player[table[2]], &player[table[3]]);
    Duel(&player[table[1]], &player[table[3]]);
    Init(&player[table[1]]);
    Init(&player[table[2]]);
    Init(&player[table[3]]);
    #ifdef __Debug
      printf("\n");
    #endif
  }
  /*Output*/
  for (int i = 1; i <= n; i++) {
    printf("%s %d\n", player[i].name.c_str(), player[i].score);
    #ifdef __Debug
      printf("%d\n", player[i].type);
      for (int j = 1; j <= 5; j++) {
        printf("%d ", player[i].card[j].point);
      }
      printf("\n");
    #endif
  }
  return 0;
}
/*
>=1100 炸弹
1000~1099 牛牛 (铁板*10)
700~999 牛1 (铁板*10)
100~699 牛2 (铁板*10)
0 无牛
*/