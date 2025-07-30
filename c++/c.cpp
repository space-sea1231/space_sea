#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 8e3 + 10;

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
};

int a[N];
int ans[N];
Binary bin;

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  for (int i = 2; i <= n; i++) cin >> a[i];
  /*Init*/
  for (int i = 1; i <= n; i++) bin.Add(i, 1);
  /*Solve*/
  for (int i = n; i >= 1; i--) {
    int l = 1, r = n;
    while (l <= r) {
      int mid = (l+r)>>1;
      if (bin.Query(mid) < a[i]) l = mid+1;
      else r = mid-1;
    }
    ans[i] = r;
    bin.Add(r, -1);
  }
  /*Output*/
  for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
  return 0;
}