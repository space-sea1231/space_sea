#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

int n, m, k;

namespace Pts1 {
  const int N = 1e2+10;
  const int INF = 0x3f3f3f3f;
  int a[N];
  
  int cnt;
  int head[N], to[N<<1], nxt[N<<1];
  
  void Add(int u, int v) {
    cnt++;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
  }
  
  int dist = INF;

  void Search1(int u, int fa, int dis) {
    dis += a[u];
    if (u == n) {
      dist = min(dist, dis);
      return;
    } 
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      if (v == fa) continue;
      Search1(v, u, dis);
    }
    return;
  }

  int num;
  vector<int> node;
  vector<int> vec[N];

  void Search2(int u, int fa, int dis) {
    dis += a[u];
    if (dis > dist) return;
    node.emplace_back(u);
    if (u == n) {
      vec[++num] = node;
      node.pop_back();
      return;
    } 
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      if (v == fa) continue;
      Search2(v, u, dis);
    }
    node.pop_back();
    return;
  }

  int sum1, sum2;
  bool place[N];

  bool Check() {
    for (int i = 1; i <= num; i++) {
      bool flag = false;
      int siz = vec[i].size();
      for (int j = 0; j < siz-1; j++) {
        if (place[vec[i][j]] == place[vec[i][j+1]]) {
          flag = true;
        }
      }
      if (flag == false) return false;
    }
    return true;
  }

  void Dfs(int dep) {
    if (dep == n+1) {
      if (Check() == true) {
        for (int i = 1; i <= n; i++) {
          if (place[i] == false) printf("P");
          else if (place[i] == true) printf("U");
        }
        printf("\n");
        exit(0);
      }
    }
    if (sum1 > 0) {
      sum1--;
      place[dep] = 0;
      Dfs(dep+1);
      sum1++;
    }
    if (sum2 > 0) {
      sum2--;
      place[dep] = 1;
      Dfs(dep+1);
      sum2++;  
    }
    return;
  }
}

namespace Pts3 {
  const int N = 1e5+10;
  const int INF = 0x3f3f3f3f;

  int a[N];
}

signed main() {
  freopen("catch.in", "r", stdin);
  freopen("catch.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m >> k;
  if (n <= 15) {
    using namespace Pts1;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
      int u, v;
      cin >> u >> v;
      Add(u, v);
      Add(v, u);
    }
    /*Init*/
    Search1(1, 0, 0);
    Search2(1, 0, 0);
    #ifdef __Debug
    // printf("dist=%d\n", dist);
    #endif
    /*Solve*/
    sum1 = n-k;
    sum2 = k;
    Dfs(1);
    /*Output*/
    printf("impossible\n");
    return 0;
  }
  else if (k == 1) {
    /*Output*/
    if (n == 2) {
      printf("impossible\n");
      return 0;
    }
    for (int i = 1; i <= n; i++) {
      if (i == 1) printf("U");
      else if (i > 1) printf("P");
    }
    printf("\n");
    return 0;
  }
  else {
    using namespace Pts3;
    int minn = INF;
    for (int i = 2; i < n; i++) {
      cin >> a[i];
      minn = min(minn, a[i]);
    }
    /*Init*/
    int cnt = 0;
    for (int i = 2; i < n; i++) {
      if (a[i] == minn) cnt++;
    }
    /*Output*/
    if (k <= cnt+1 && n-k <= cnt+1) {
      printf("impossible\n");
      return 0;
    }
    if (k >= n-k) {
      int sum = n-k;
      for (int i = 1; i <= n; i++) {
        if (i == 1) printf("U"), k--;
        else if (a[i] == minn) printf("U"), k--;
        else if (sum > 0 && a[i] > minn) printf("P"), sum--;
        else if (sum == 0 && a[i] > minn) printf("U"), k--; 
      }
      printf("\n");
      return 0;
    }
    else if (k < n-k) {
      int sum = n-k;
      for (int i = 1; i <= n; i++) {
        if (i == 1) printf("P"), sum--;
        else if (a[i] == minn) printf("P"), sum--;
        else if (k > 0 && a[i] > minn) printf("U"), k--;
        else if (k == 0 && a[i] > minn) printf("P"), sum--; 
      }
      printf("\n");
      return 0;
    }
    return 0;
  }
  /*Init*/
  /*Solve*/
  /*Output*/
  return 0;
}