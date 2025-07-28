#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
int num;
int ans[N];

struct Node {
  int a, b, c;
  int cnt, res;
  
  bool operator != (const Node srca)const {
    if (a != srca.a) return true;
    if (b != srca.b) return true;
    if (c != srca.c) return true;
    return false;
  }
};

namespace Binary {
  int sum[N << 1];
  
  int Lowbit(int x) { return x & -x; }
  
  void Add(int x, int y) {
    for (int i = x; i <= m; i += Lowbit(i)) {
      sum[i] += y;
    }
    return;
  }
  
  int Query(int x) {
    int tot = 0;
    for (int i = x; i > 0; i -= Lowbit(i)) {
      tot += sum[i];
    }
    return tot;
  }
}
using namespace Binary;

Node e[N], node[N];

bool CmpA(Node arca, Node arcb) {
  if (arca.a != arcb.a) return arca.a < arcb.a;
  if (arca.b != arcb.b) return arca.b < arcb.b;
  return arca.c < arcb.c;
}

bool CmpB(Node arca, Node arcb) {
  if (arca.b != arcb.b) return arca.b < arcb.b;
  return arca.c < arcb.c;
}

namespace CDQ {
  void Cdq(int l, int r) {
    // cerr << l << " " << r << "\n";
    if (l == r) return;
    int mid = (l + r) >> 1;
    Cdq(l, mid);
    Cdq(mid + 1, r);
    sort(node + l, node + mid + 1, CmpB);
    sort(node + mid + 1, node + r + 1, CmpB);
    int i = l, j = mid + 1;
    while (j <= r) {
      while (i <= mid && node[i].b <= node[j].b) {
        Add(node[i].c, node[i].cnt);
        i++;
      }
      node[j].res += Query(node[j].c);
      j++;
    }
    for (int k = l; k < i; k++) Add(node[k].c, -node[k].cnt);
    return;
  }
}
using namespace CDQ;

signed main() {
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> e[i].a >> e[i].b >> e[i].c;
  sort(e + 1, e + n + 1, CmpA);
  int tmp = 0;
  for (int i = 1; i <= n; i++) {
    tmp++;
    if (e[i] != e[i + 1]){
      num++;
      node[num].a=e[i].a;
      node[num].b=e[i].b;
      node[num].c=e[i].c;
      node[num].cnt = tmp;
      tmp = 0;
    }
  }
  // cerr << num << "\n";
  Cdq(1, num);
  for (int i = 1; i <= num; i++) ans[node[i].res + node[i].cnt - 1] += node[i].cnt;
  for (int i = 0; i < n; i++) printf("%d\n", ans[i]);

  return 0;
}