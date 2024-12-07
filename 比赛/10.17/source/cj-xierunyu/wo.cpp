#include<bits/stdc++.h>
#define QWQ
#define int long long

using namespace std;
const int MAXN = 2e6 + 5, Mod = 998244353;
int n, a[MAXN];
bool vis[MAXN];
int check(auto g){
  int cnt = 0, ans = 0;
  for (int i = 1; i <= 2 * n; i += 2){
    int A = a[i], B = a[i + 1];
    if (!A){
      A = g[cnt++];
    }
    if (!B){
      B = g[cnt++];
    }
    ans += abs(A - B);
  }
  return ans;
}
void Solve(){
  cin >> n;
  for (int i = 1; i <= 2 * n; i++){
    vis[i] = 0;
  }
  for (int i = 1; i <= 2 * n; i++){
    cin >> a[i];
    vis[a[i]] = 1;
  }
  vector<int> g;
  for (int i = 1; i <= 2 * n; i++){
    if (!vis[i]){
      g.push_back(i);
    }
  }
  int ans = 0, cnt = 0;
  do{
    int t = check(g);
    if (t > cnt){
      cnt = t, ans = 1;
    }else if (t == cnt){
      ans++;
    }
  }while(next_permutation(g.begin(), g.end()));
  cout << ans << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifndef QWQq
  freopen("wo.in", "r", stdin);
  freopen("wo.out", "w", stdout);
  #endif
  int t;
  cin >> t;
  while (t--){
    Solve();
  }  
  return 0;
}