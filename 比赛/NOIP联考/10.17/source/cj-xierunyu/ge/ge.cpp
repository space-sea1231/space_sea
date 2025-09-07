#include<bits/stdc++.h>
#define QWQ
#define int long long

using namespace std;
const int Mod = 998442353;
int n, m, p[20][20], a[20], fact[20];
bool vis[20];
int check(){
  int ans = 0;
  for (int i = 2; i <= m; i++){
    for (int j = 1; j <= n; j++){
      ans += abs(p[a[i]][j] - p[a[i - 1]][j]);
    }
  }
  return ans;
}
void Solve(){
  cin >> n >> m;
  for (int i = 1; i <= m; i++){
    a[i] = i;
    for (int j = 1; j <= n; j++){
      cin >> p[i][j];
    }
  }
  for (int i = 1; i <= m; i++){
    cin >> vis[i];
  }
  int ans = 4e18, cnt = 0;
  do{
    if (!vis[a[1]]){
      continue;
    }
    int t = check();
    if (t < ans){
      ans = t, cnt = (n == 1 ? 1 : fact[n + 1]);
    }else if (t == ans){
      (cnt += (n == 1 ? 1 : fact[n + 1])) %= Mod;
    }
  }while(next_permutation(a + 1, a + m + 1));
  cout << ans << ' ' << cnt << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifndef QWQq
  freopen("ge.in", "r", stdin);
  freopen("ge.out", "w", stdout);
  #endif
  fact[0] = 1;
  for (int i = 1; i < 20; i++){
    fact[i] = fact[i - 1] * i % Mod;
  }
  int t;
  cin >> t;
  while (t--){
    Solve();
  }  
  return 0;
}