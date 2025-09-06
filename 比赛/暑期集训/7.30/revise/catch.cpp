#include <iostream>
#include <stdio.h>
#include <vector>
#include <assert.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5+10;

int n, m, k;
bool ans[N];
bool vis[N];
vector<int> vec1, vecn;

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m >> k;
  /*Init*/
  if (n == 2 && k == 1) {
    printf("impossible\n");
    return 0;
  }
  /*Input*/
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
  }
  bool flag = false;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;  
    if (min(u, v) == 1) vec1.push_back(max(u, v));
    if (max(u, v) == n) vecn.push_back(min(u, v));
    if (min(u, v) == 1 && max(u, v) == n) flag = true;
  }
  /*Solve*/
  int cnt = 1;
  bool fflag = false;
  if (k < n-k) {
    k = n-k;
    fflag = true;
  }
  if (flag == true) {
    cnt++;
    ans[1] = ans[n] = true;
  }
  else {
    if (vec1.size() < vecn.size()) {
      ans[1] = true;
      for (int idx:vec1) {
        ans[idx] = true;
        if (++cnt == k) break;
      }
    }
    else if (vec1.size() >= vecn.size()) {
      ans[n] = true;
      for (int idx:vecn) {
        ans[idx] = true;
        if (++cnt == k) break;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%c", (ans[i] == true || ++cnt <= k)^fflag == true ? 'U':'P');
  }
  return 0;
}