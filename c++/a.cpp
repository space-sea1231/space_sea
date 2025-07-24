#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 4e7 + 10;
const int M = 3e7 + 7e6;
const int EXP = 262143;

int t, n;
int a[N];
int sum[N], f[N];
int bucket[M];

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> t;
  while (t--) {
    cin >> n;
    int k = 0;
    if (n == N) {
      int x, y;
      cin >> x >> y;
      a[1] = 0;
      for (int i = 2; i <= n; i++) {
        a[i] = (a[i - 1] * x + y + i) & EXP;
        k = max(k, a[i] + 1);
      }
    }
    else{
      for (int i = 1; i <= n; i++) {
        cin >> a[i];
        k = max(k, a[i] + 1);
      }
    }
    /*Init*/
    for (int i = 0; i <= n; i++) {
      bucket[i] = 0;
      sum[i] = 0;
      f[i] = 0;
    }
    sum[0] = f[0] = 1;
    /*Solve*/
    int l = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (bucket[a[i]] == 0) {
        cnt++;
      }
      bucket[a[i]]++;
      if (cnt == k) {
        while (bucket[a[l + 1]] > 1) {
          l++;
          bucket[a[l]]--;
        }
      }
      f[i] = sum[l];
      sum[i] = sum[i - 1] + f[i];
      #ifdef __Debug
        printf("Debug: f[%d]=%d\n", i, f[i]);
      #endif
    }
    printf("%d\n", f[n]);
  }
  return 0;
}