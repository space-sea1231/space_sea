#include<bits/stdc++.h>
#define QWQ

using namespace std;
const int MAXN = 4e5 + 5;
int n, a[MAXN];
unsigned dp[MAXN];
unsigned check(){
  unsigned ans = 0;
  for (int i = 1; i <= n; i++){
    dp[i] = 1;
  }
  a[0] = 998244353;
  for (int i = 1; i <= n; i++){
    if (a[i - 1] < a[i]){
      dp[i] += dp[i - 1];
    }
    ans += dp[i];
  }
  return ans;
}
void Solve(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  unsigned ans = check();
  for (int i = 1; i <= n; i++){
    for (int j = i + 1; j <= n; j++){
      swap(a[i], a[j]);
      ans = max(ans, check());
      swap(a[i], a[j]);
    }
  }
  cout << ans << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifndef QWQq
  freopen("wei.in", "r", stdin);
  freopen("wei.out", "w", stdout);
  #endif
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
/*
1 2 3
1
2
3
1 2
2 3
1 2 3
*/