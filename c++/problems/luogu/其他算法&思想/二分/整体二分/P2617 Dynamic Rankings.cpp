#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m;

struct Operate {
  int type;
  int x, y;
  int k;
};

struct Binary {
  int sum[N];
  
  int Lowbit(int x) {
    return x&-x;
  }

  void Add(int pos, int val) {
    for (int i = pos; i <= n; i += Lowbit(i)) {
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
Operate opr[N<<2];
Operate lopr[N<<2], ropr[N<<2];
int ans[N];

void Cdq(int vall, int valr, int l, int r) {
  /*Solve*/
  if (l > r) return;
  if (vall == valr) {
    for (int i = l; i <= r; i++) {
      if (opr[i].type > 0) {
        ans[opr[i].type] = vall;
      }
    }
    return;
  }
  int mid = (vall+valr)>>1;
  int lcnt = 0, rcnt = 0;
  for (int i = l; i <= r; i++) {
    if (opr[i].type == -1) {
      if (opr[i].y <= mid) {
        bin.Add(opr[i].x, -1);
        lopr[++lcnt] = opr[i];
      }
      else ropr[++rcnt] = opr[i];
    }
    else if (opr[i].type == 0) {
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
    if (opr[i].y <= mid) {
      if (opr[i].type == 0) bin.Add(opr[i].x, -1);
      else if (opr[i].type == -1) bin.Add(opr[i].x, 1);
    }
  }
  for (int i = 1; i <= lcnt; i++) opr[l+i-1] = lopr[i];
  for (int i = 1; i <= rcnt; i++) opr[l+lcnt+i-1] = ropr[i];
  /*Solve*/
  Cdq(vall, mid, l, l+lcnt-1);
  Cdq(mid+1, valr, l+lcnt, r);
  return;
}

int top;
int a[N];

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    opr[++top] = (Operate){0, i, a[i], 0};
  }
  for (int i = 1; i <= m; i++) {
    char opt;
    cin >> opt;
    if (opt == 'Q') {
      int  x, y, k;
      cin >> x >> y >> k;
      opr[++top] = (Operate){i, x, y, k};
    }
    if (opt == 'C') {
      int x, y;
      cin >> x >> y;
      opr[++top] = (Operate){-1, x, a[x], 0};
      opr[++top] = (Operate){0, x, y, 0};
      a[x] = y;
    }
  }
  /*Init*/
  for (int i = 1; i <= m; i++) ans[i] = -1;
  /*Solve*/
  Cdq(0, INF, 1, top);
  for (int i = 1; i <= m; i++) {
    if (ans[i] > -1) printf("%d\n", ans[i]);
  }
  return 0;
}