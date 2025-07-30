#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m;

struct Operate {
  int x, y;
  int type;
  int k;
};

struct Binary {
  int sum[N<<1];

  int Lowbit(int x) {
    return x&-x;
  }

  void Add(int pos, int val) {
    for (int i = pos; i < N; i += Lowbit(i)) {
      sum[i] += val;
    }
    return;
  }
  
  int Query(int pos) {
    int ans = 0;
    for (int i = pos; i > 0; i -= Lowbit(i)) {
      ans += sum[i];
    }
    return ans;
  }
};

Binary bin;
Operate opr[N<<1];
Operate lopr[N<<1], ropr[N<<1];
int ans[N<<1];

void Cdq(int vall, int valr, int l, int r) {
  if (l > r) return;
  if (vall == valr) {
    for (int i = l; i <= r; i++) {
      ans[i] = vall;
    }
    return;
  }
  int mid = (l+r)>>1;
  int lcnt = 0, rcnt = 0;
  for (int i = l; i <= r; i++) {
    if (opr[i].type == 0) {
      if (opr[i].y <= mid) {
        bin.Add(opr[i].x, 1);
        lopr[++lcnt] = opr[i];
      }
      ropr[++rcnt] = opr[i];
    }
    if (opr[i].type > 0) {
      int cnt = bin.query()
    }
  }
}

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> opr[i].y;
    opr[i].x = i;
  }
  for (int i = n+1; i <= n+m; i++) {
    char opt;
    cin >> opt;
    if (opt == 'Q') {
      cin >> opr[i].x >> opr[i].y >> opr[i].k;
      opr[i].type = i;
    }
    if (opt == 'C') cin >> opr[i].x >> opr[i].y;
  }
  /*Solve*/
  Cdq(-INF, INF, 1, n+m);

  return 0;
}