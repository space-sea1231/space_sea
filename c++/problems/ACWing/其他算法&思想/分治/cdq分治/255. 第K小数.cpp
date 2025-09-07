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
bool flag[N<<1];

void Cdq(int vall, int valr, int l, int r) {
  /*Solve*/
  if (l > r) return;
  if (vall == valr) {
    for (int i = l; i <= r; i++) {
      if (opr[i].type > 0) {
        ans[opr[i].type] = vall;
        // flag[opr[i].type] = true;
      }
    }
    return;
  }
  int mid = (vall+valr)>>1;
  int lcnt = 0, rcnt = 0;
  for (int i = l; i <= r; i++) {
    if (opr[i].type == 0) {
      if (opr[i].y <= mid) {
        bin.Add(opr[i].x, 1);
        lopr[++lcnt] = opr[i];
      }
      else ropr[++rcnt] = opr[i];
    }
    else {
      int cnt = bin.Query(opr[i].y)-bin.Query(opr[i].x-1);
      if (cnt >= opr[i].k) lopr[++lcnt] = opr[i];
      else {
        opr[i].k -= cnt;
        ropr[++rcnt] = opr[i];
      }
    }
  }
  /*Init*/
  for (int i = l; i <= r; i++) {
    if (opr[i].type == 0 && opr[i].y <= mid) {
      bin.Add(opr[i].x, -1);
    } 
  }
  for (int i = 1; i <= lcnt; i++) opr[l+i-1] = lopr[i];
  for (int i = 1; i <= rcnt; i++) opr[l+lcnt+i-1] = ropr[i];
  /*Solve*/
  Cdq(vall, mid, l, l+lcnt-1);
  Cdq(mid+1, valr, l+lcnt, r);
  return;
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
    // char opt;
    // cin >> opt;
    // if (opt == 'Q') {
      cin >> opr[i].x >> opr[i].y >> opr[i].k;
      opr[i].type = i;
    // }
    // if (opt == 'C') cin >> opr[i].x >> opr[i].y;
  }
  /*Solve*/
  Cdq(-INF, INF, 1, n+m);
  for (int i = n+1; i <= n+m; i++) {
    // if (flag[i] == true) printf("%d\n", ans[i]);
    printf("%d\n", ans[i]);
  }
  return 0;
}