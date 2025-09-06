#include <iostream>
#include <stdio.h>
#include <vector>
#include <assert.h>
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
  bool vis[N];

  void Add(int u, int v) {
    cnt++;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
  }
  
  int dist = INF;

  void Search1(int u, int fa, int dis) {
    vis[u] = true;
    dis += a[u];
    if (u == n) {
      dist = min(dist, dis);
      vis[u] = false;
      return;
    } 
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      if (vis[v] == true) continue;
      Search1(v, u, dis);
    }
    vis[u] = false;
    return;
  }

  int num;
  vector<int> node;
  vector<int> vec[N];

  void Search2(int u, int fa, int dis) {
    vis[u] = true;
    dis += a[u];
    if (dis > dist) return;
    node.emplace_back(u);
    if (u == n) {
      vec[++num] = node;
      node.pop_back();
      vis[u] = false;
      return;
    } 
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      if (vis[v] == true) continue;
      Search2(v, u, dis);
    }
    vis[u] = true;
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

namespace Pts2 {
  const int N = 1e5+10;
  const int INF = 0x3f3f3f3f;

  int a[N];
  int cnt[N];
}

namespace Pts3 {
  const int N = 1e5+10;

  bool ans[N];
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
    using namespace Pts2;
    /*Output*/
    if (n == 2) {
      printf("impossible\n");
      return 0;
    }
    int minn = INF;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (i == 1 || i == n) continue;
      minn = min(minn, a[i]);
    }
    bool fflag = false;
    for (int i = 1; i <= m; i++) {
      int u, v;
      cin >> u >> v;
      if (u == 1 || u == n) cnt[v]++;
      if (v == 1 || v == n) cnt[u]++;
      if ((u == 1 && v == n) || (u == n && v == 1)) fflag = true;
    }
    if (fflag == false) {
      for (int i = 1; i <= n; i++) {
        if (i == 1) printf("U");
        else if (i > 1) printf("P");
      }
      printf("\n");
      return 0;
    }
    int flag = 0;
    for (int i = 2; i < n; i++) {
      if (cnt[i] < 2) {
        flag = i;
        break;
      }
    }
    if (flag == 0) {
      for (int i = 2; i < n; i++) {
        if (a[i] != minn && flag == false) {
          flag = i;
        }
      }
    }
    if (flag != 0) {
      for (int i = 1; i <= n; i++) {
        if (flag == i) printf("U");
        else printf("P");
      }
      printf("\n");
    }
    else printf("impossible\n");
    return 0;
  }
  else {
    using namespace Pts3;
    for (int i = 1; i <= n; i++) {
      int a;
      cin >> a;
    }
    bool flag = false;
    for (int i = 1; i <= m; i++) {
      int u, v;
      cin >> u >> v;
      if ((u == 1 && v == n) || (u == n && v == 1)) flag = true;
    }
    int sum1 = n-k, sum2 = k;
    if (flag == true) {
      if (sum1 >= 2) {
        sum1 -= 2;
        ans[1] = ans[n] = false;
      }
      else if (sum2 >= 2) {
        sum2 -= 2;
        ans[1] = ans[n] = true;
      }
    }
    else {
      if (sum1 == n) {
        sum1 -= 2;
        ans[1] = ans[n] = false;
      }
      else if (sum2 == n) {
        sum2 -= 2;
        ans[1] = ans[n] = true;
      }else {
        sum1--, sum2--;
        ans[1] = false, ans[n] = true;
      }
    }
    for (int i = 2; i < n; i++) {
      if (sum1 > 0) {
        sum1--;
        ans[i] = false;
      }
      else if (sum2 > 0) {
        sum2--;
        ans[i] = true;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (ans[i] == false) printf("P");
      else if (ans[i] == true) printf("U");
    }
    return 0;
  }
  /*Init*/
  /*Solve*/
  /*Output*/
  return 0;
}