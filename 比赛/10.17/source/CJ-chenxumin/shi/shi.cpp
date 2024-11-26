#include<bits/stdc++.h>
using namespace std;
int t, n;
string s;
vector<int> ans;
void dfs(int l, int r){
  if(r - l == 2){
    ans.push_back(l + 1);
    return;
  }
  ans.push_back(l + 1);
  ans.push_back(r - 1);
}
void solve(){
  cin >> s;
  n = s.size();
  s = ' ' + s;
  int cnt = 0;
  for(int i = 1; i <= n; i++){
    cnt += s[i] - '0';
  }
  ans.clear();
  if(cnt == 0){
    if(n % 2)cout << n - 1 << ' ';
    else cout << n - 2 << ' ';
    cout << 0 << '\n';
    return;
  }
  for(int k = 1; k <= 20; k++){
    for(int i = 2; i < n; i++){
      if(s[i - 1] == '0' && s[i] == '0'&& ans.size() < 13 * n){
        s[i - 1] = '1';
        s[i + 1] = (s[i + 1] == '0' ? '1' : '0');
        ans.push_back(i);
      }
    }
  }
  int sum = 0, ans2;
  for(int i = 1; i <= n; i++)sum += s[i] - '0';
  if(n <= 3){
    if(s == " 000" || s == " 101" || s == " 110" || s == " 011")cout << 2 << ' ';
    else if(s == "010" || s == " 111")cout << 3 << ' ';
    else if(s == " 100" || s == " 001")cout << 1 << '\n';
  }else if(cnt == n)cout << max(sum, n) << ' ';
  else cout << max(n - 1, sum) << ' ';
  cout << ans.size() << '\n';
  for(int i : ans)cout << i << ' ' ;
  cout << '\n';
}
int main(){
  // freopen("shi.in", "r", stdin);
  // freopen("shi.out", "w", stdout);
  cin >> t;
  for(; t; t--, solve());
  return 0;
}
