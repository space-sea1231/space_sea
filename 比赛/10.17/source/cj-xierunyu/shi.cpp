#include<bits/stdc++.h>
#define QWQ

using namespace std;
int n, ANS;
string s;
vector<int> t;
int checksum(){
  int ans = 0;
  for (int i = 1; i <= n; i++){
    ans += s[i] - '0';
  }
  return ans;
}
int check(auto q){
  string T = s;
  for (auto v : q){
    if (s[v] == '0'){
      s[v - 1] ^= 1;
      s[v + 1] ^= 1;
    }else {
      s[v - 1] = s[v + 1] = '0';
    }
  }
  int ans = checksum();
  s = T;
  return ans;
}
void dfs(int x, vector<int> q){
  if (x == n){
    if (check(q) > ANS){
      ANS = check(q);
      t = q;
    }
    return ;
  }
  dfs(x + 1, q);
  q.push_back(x);
  dfs(x + 1, q);
  q.pop_back();
}
void Solve(){
  cin >> s;
  n = s.size();
  s = ' ' + s;
  t.clear();
  ANS = 0;
  if (checksum() == 0){
    cout << (n <= 2 ? 0 : n - n % 2) << " 0\n";
    return ;
  }
  // else if (n <= 20){
  //   dfs(2, {});
  //   cout << "0 " << t.size() << '\n';
  //   for (auto v : t){
  //     cout << v << ' ';
  //   }
  //   cout << '\n';
  //   cerr << ANS << '\n';
  //   return ;
  // }
  for (int T = 1; T <= 10; T++){
    for (int i = 2; i < n; i++){
      if (s[i] == '0' && s[i + 1] == '0' && s[i + 2] == '0'){
        continue;
      }
      if (s[i] == '0' && (s[i - 1] == '0' || s[i + 1] == '0')){
        t.push_back(i);
        s[i + 1] ^= 1;
        s[i - 1] ^= 1;
      }
    }
  }
  cout << "0 " << t.size() << '\n';
  for (auto v : t){
    cout << v << ' ';
  }
  cout << '\n';
  // cerr << s << '\n';
}
signed main(){
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifndef QWQq
  freopen("shi.in", "r", stdin);
  freopen("shi.out", "w", stdout);
  #endif
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}