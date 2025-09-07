#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5+10;

int n;

struct Binary {
  int sum[N];
  
  int Lowbit(int x) { return x&-x; }
  
  void Add(int pos, int val) {
    for (int i = pos; i <= n; i += Lowbit(i)) sum[i] += val;
    return;
  }
  
  int Query(int pos) {
    int ans = 0;
    for (int i = pos; i > 0; i -= Lowbit(i)) ans += sum[i];
    return ans;
  }

  void Clear() {
    for (int i = 1; i <= n; i++) sum[i] = 0;
    return;
  }
};

ll ans1, ans2;
int a[N];
int l[N], r[N];
Binary bin;

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  /*Solve1*/
  for (int i = 1; i <= n; i++) {
    l[i] = bin.Query(a[i]-1);
    bin.Add(a[i], 1);
  }
  bin.Clear();
  for (int i = n; i >= 1; i--) {
    r[i] = bin.Query(a[i]-1);
    bin.Add(a[i], 1);
  }
  bin.Clear();
  for (int i = 1; i <= n; i++) ans2 += (ll)l[i]*r[i];
  #ifdef __Debug
    for (int i = 1; i <= n; i++) printf("Debug1: l[%d]=%d r[%d]=%d\n", i, l[i], i, r[i]);
  #endif
  /*Solve2*/
  for (int i = 1; i <= n; i++) {
    l[i] = bin.Query(n-a[i]);
    bin.Add(n-a[i]+1, 1);
  }
  bin.Clear();
  for (int i = n; i >= 1; i--) {
    r[i] = bin.Query(n-a[i]);
    bin.Add(n-a[i]+1, 1);
  }
  bin.Clear();
  for (int i = 1; i <= n; i++) ans1 += (ll)l[i]*r[i];
  #ifdef __Debug
    for (int i = 1; i <= n; i++) printf("Debug1: l[%d]=%d r[%d]=%d\n", i, l[i], i, r[i]);
  #endif
  /*Output*/
  printf("%lld %lld", ans1, ans2);
  return 0;
}