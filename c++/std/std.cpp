#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5+10;

int n, m, k;
bool ans[N];
bool vis[N];
vector<int> vecu, vecp;

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m >> k;
  /*Init*/
  if (n == 2 && k == 1) {
    printf("impossible\n");
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
  }
  bool flag = false;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    if (u == 1) vecp.push_back(v);
    if (u == n) vecu.push_back(v);
    if (v == 1) vecp.push_back(u);
    if (v == n) vecu.push_back(u);
    if ((u == 1 && v == n) || (u == n && v == 1)) flag = true;
  }
  int sumu = k, sump = n-k;
  if (flag == true) {
    if (sumu >= 2) {
      sumu -= 2;
      ans[1] = ans[n] = false;
    }
    else if (sump >= 2) {
      sump -= 2;
      ans[1] = ans[n] = true;
    }
    for (int i = 2; i < n; i++) {
      if (sumu > 0) {
        sumu--;
        ans[i] = false;
      }
      else if (sump > 0) {
        sump--;
        ans[i] = true;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (ans[i] == false) printf("U");
      else if (ans[i] == true) printf("P");
    }
    printf("\n");
    return 0;
  }
  if (sumu == n) {
    sumu -= 2;
    ans[1] = ans[n] = false;
  }
  else if (sump == n) {
    sump -= 2;
    ans[1] = ans[n] = true;
  }
  else {
    sumu--, sump--;
    ans[1] = false;
    ans[n] = true;
  }
  for (int idx:vecu) {
    if (sumu > 0) {
      sumu--;
      ans[idx] = false;
    }
    else if (sump > 0) {
      sump--;
      ans[idx] = true;
    }
    vis[idx] = true;
  }
  for (int idx:vecp) {
    if (sump > 0) {
      sump--;
      ans[idx] = true;
    }
    else if (sumu > 0) {
      sumu--;
      ans[idx] = false;
    }
    vis[idx] = true;
  }
  for (int i = 2; i < n; i++) {
    if (vis[i] == true) continue;
    if (sump > 0) {
      sump--;
      ans[i] = true;
    }
    else if (sumu > 0) {
      sumu--;
      ans[i] = false;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i] == false) printf("U");
    else if (ans[i] == true) printf("P");
  }
  printf("\n");
  /*Init*/
  /*Solve*/
  /*Output*/
  return 0;
}