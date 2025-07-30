#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 6e5 + 10;
const int LEN = 2e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m;

struct Operate {
  int x, y;
  int type;
  int id;
};

struct Binary {
  int sum[LEN];
  
  int Lowbit(int x) {
    return x&-x;
  }
  
  void Add(int pos, int val) {
    for (int i = pos; i < LEN; i += Lowbit(i)) {
      sum[i] = max(sum[i], val);
    }
    return;
  }
  
  int Query(int pos) {
    int rev = 0;
    for (int i = pos; i > 0; i -= Lowbit(i)) {
      rev = max(rev, sum[i]);
    }
    return (rev == 0 ? -INF : rev);
  }

  void Clear(int pos) {
    for (int i = pos; i < LEN; i += Lowbit(i)) {
      sum[i] = 0;
    }
    return;
  }
};

Binary bin;
Operate opr[N], cpy[N];
Operate tmp[N];
int ans[N];

void Cdq(int l, int r) {
  /*Solve*/
  if (l == r) return;
  int mid = (l+r)>>1;
  Cdq(l, mid), Cdq(mid+1, r);
  int i = l, j = mid+1;
  int top = l;
  while (j <= r) {
    while (i <= mid && cpy[i].x <= cpy[j].x) {
      if (cpy[i].type == 1) {
        bin.Add(cpy[i].y, cpy[i].x+cpy[i].y);
      }
      tmp[top++] = cpy[i++];
    }
    if (cpy[j].type == 2) {
      ans[cpy[j].id] = min(ans[cpy[j].id], cpy[j].x+cpy[j].y-bin.Query(cpy[j].y));
    }
    tmp[top++] = cpy[j++];
  }
  /*Init*/
  for (int k = l; k <= i-1; k++) {
    if (cpy[k].type == 1) bin.Clear(cpy[k].y);
  }
  while (i <= mid) tmp[top++] = cpy[i++];
  for (int k = l; k <= r; k++) cpy[k] = tmp[k]; 
  return;
}

void Solve(bool flag1, bool flag2) {
  /*Init*/
  for (int i = 1; i <= n+m; i++) {
    cpy[i] = opr[i];
    cpy[i].id = i;
    if (flag1 == true) cpy[i].x = LEN - cpy[i].x;
    if (flag2 == true) cpy[i].y = LEN - cpy[i].y;
  }
  /*Solve*/
  Cdq(1, n+m);
  return;
}

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> opr[i].x >> opr[i].y;
    opr[i].x++;
    opr[i].y++;
    opr[i].type = 1;
  }
  for (int i = n+1; i <= n+m; i++) {
    cin >> opr[i].type >> opr[i].x >> opr[i].y;
    opr[i].x++;
    opr[i].y++;
  }
  /*Init*/
  for (int i = n + 1; i <= n + m; i++) ans[i] = INF;
  /*Solve*/
  Solve(0, 0); Solve(1, 0); Solve(0, 1); Solve(1, 1);
  /*Output*/
  for (int i = 1; i <= n + m; i++) {
    if (opr[i].type == 2) printf("%d\n", ans[i]);
  }
  return 0;
}
/*
《送别》--城南旧事
长亭外，古道边，芳草碧连天
晚风拂柳笛声残，夕阳山外山
天之涯，地之角，知交半零落
一瓢浊酒尽馀欢，今宵别梦寒
长亭外，古道边，芳草碧连天
晚风拂柳笛声残，夕阳山外山
情千缕，酒一杯，声声离笛催
问君此去几时来，来时莫徘徊
草碧色，水绿波，南浦伤如何
人生难得是欢聚，惟有别离多
情千缕，酒一杯，声声离笛催
问君此去几时来，来时莫徘徊
*/