#include <iostream>
#include <stdio.h>
#include <unordered_map>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 6e7 + 10;
const int M = 2e5 + 10;

int n;
int num = M;
ll cnt[N];
bool vis[M];
unordered_map<int, int> unmap;

signed main() {
  freopen("divisor.in", "r", stdin);
  freopen("divisor.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    /*Solve*/
    int tmp = a;
    for (int j = 2; j*j <= tmp; j++) {
      if (tmp%j == 0) {
        cnt[j] += a;
        while (tmp%j == 0) tmp /= j;
      }
    }
    if (tmp > 1) {
      if (tmp <= 1e5) {
        cnt[tmp] += a;
        continue;
      }
      if (unmap[tmp] == 0) unmap[tmp] = ++num;
      cnt[unmap[tmp]] += a;
    }
  }
  /*Output*/
  ll ans = 0;
  for (int i = 2; i <= num; i++) ans = max(ans, cnt[i]);
  printf("%lld\n", ans);
  return 0;
}