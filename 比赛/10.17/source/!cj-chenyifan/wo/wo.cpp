#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5, Mod = 998244353;
int n, p[N << 1], a[N], tot, ans, maxi = -1;
bool vis[N << 1];
inline void dfs(int x, int sum) {
  if(x > n * 2) {
    if(maxi < sum) {
      maxi = sum;
      ans = 1;
    } else if(maxi == sum) {
      ans = (ans + 1) % Mod;
    }
    return ;
  }
  if(p[x] && p[x + 1]) { dfs(x + 2, sum + abs(p[x] - p[x + 1]));}
  else if(p[x]) {
    for(int i = 1; i <= n * 2; i++) if(!vis[i]) {
      vis[i] = 1;
      p[x + 1] = i;
      dfs(x + 2, sum + abs(p[x] - p[x + 1]));
      vis[i] = 0;
    }
    p[x + 1] = 0;
  } else if(p[x + 1]) {
    for(int i = 1; i <= n * 2; i++) if(!vis[i]) {
      vis[i] = 1;
      p[x] = i;
      dfs(x + 2, sum + abs(p[x] - p[x + 1]));
      vis[i] = 0;
    }
    p[x] = 0;
  } else {
    for(int i = 1; i <= n * 2; i++) if(!vis[i]) {
      vis[i] = 1;
      p[x] = i;
      for(int j = 1; j <= n * 2; j++) if(!vis[j]) {
        vis[j] = 1;
        p[x + 1] = j;
        dfs(x + 2, sum + abs(p[x] - p[x + 1]));
        vis[j] = 0;
      }
      p[x + 1] = vis[i] = 0;
    }
    p[x] = 0;
  }
}
signed main() {
  freopen("wo.in", "r", stdin);
  freopen("wo.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    tot = 0, maxi = -1, ans = 0;
    cin >> n;
    for(int i = 1; i <= n * 2; i++) { vis[i] = 0; }
    for(int i = 1; i <= n * 2; i++) {
      cin >> p[i];
      vis[p[i]] = 1;
    }
    // if(n <= 10) {
      dfs(1, 0);
      cout << ans << '\n';
    //   continue;
    // }
    // int cnt = 0;
    // for(int i = 1; i <= n; i++) {
    //   int u = i * 2 - 1, v = i << 1;
    //   if(!p[u] && p[v]) { a[++tot] = p[v]; }
    //   if(p[u] && !p[v]) { a[++tot] = p[u]; }
    //   cnt += !p[u] && !p[v];
    // }
    // for(int i = 1; i <= n; i++) {

    // }
  }
  return 0;
}