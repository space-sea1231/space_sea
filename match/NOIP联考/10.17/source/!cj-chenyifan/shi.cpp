#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n;
bool a[N];
// a nand b = !(a | b)
int main() {
  freopen("shi.in", "r", stdin);
  freopen("shi.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    string s;
    cin >> s;
    n = s.size();
    int flag = 0;
    for(int i = 0; i < n; i++) {
      a[i + 1] = s[i] - '0';
      flag += a[i + 1];
    }
    cout << n - 1 << '\n';
  }
  return 0;
}