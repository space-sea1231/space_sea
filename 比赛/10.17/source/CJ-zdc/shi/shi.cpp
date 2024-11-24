#include <bits/stdc++.h>
#define ALL(x) begin(x), end(x)
#define All(x, l, r) &x[l], &x[r] + 1
using namespace std;
void file() {
  freopen("shi.in", "r", stdin);
  freopen("shi.out", "w", stdout);
}
using ll = long long;

const int kL = 1e6 + 5;
int n;
vector<bool> a;

namespace Task1 {
  const int cL = 1005;
  array<int, cL> last;
  array<bool, cL> vis;

  int modify(int s, int p) {
    if((s >> p) & 1)
      s &= ~((1 << p - 1) | (1 << p + 1));
    else s ^= ((1 << p - 1) ^ (1 << p + 1));
    return s;
  }

  void BFS(int s) {
    vis.fill(0);
    last.fill(0);
    queue<int> q;
    q.push(s); vis[s] = 1;
    int ans = s;
    while(q.size()) {
      int x = q.front(); q.pop();
      if(__builtin_popcount(ans) < __builtin_popcount(x))
        ans = x;
      for(int i = 2; i < n; i++) {
        int to = modify(x, i);
        if(!vis[to]) {
          vis[to] = 1;
          last[to] = x;
          q.push(to);
        }
      }
    }
    vector<int> vec;
    for(int i = ans; i ^ s; i = last[i]) {
      int to = last[i];
      for(int j = 2; j < n; j++)
        if(modify(to, j) == i) {
          vec.push_back(j); break;
        }
    }
    reverse(ALL(vec));
    cout << "0 " << vec.size() << "\n";
    for(int k : vec)
      cout << k << " ";
    cout << "\n";
  }

  void solve() {
    int S = 0;
    for(int i = 1; i <= n; i++) S += (1 << i) * a[i];
    BFS(S);
  }
}

namespace Task2 {
  vector<int> ans;
  void modify(int x) {
    a[x - 1] = !a[x - 1] && !a[x];
    a[x + 1] = !a[x + 1] && !a[x];
    ans.push_back(x);
  }

  void solve0() {
    int cur = 0;
    for(; cur + 6 <= n; cur += 3) {
      modify(cur + 2);
      modify(cur + 4);
      modify(cur + 3);
      modify(cur + 5);
      modify(cur + 4);
    }
    int rem = n - cur;
    if(rem == 5) {
      modify(cur + 2);
      modify(cur + 4);
      modify(cur + 3);
    }else if(rem == 4) {
      modify(cur);
      modify(cur - 1);
      cur -= 3;
      modify(cur + 2);
      modify(cur + 4);
      modify(cur + 3);
      modify(cur + 6);
      modify(cur + 5);
      modify(cur + 4);
    }else modify(cur + 2);
  }

  bool check() {
    for(int i = 1; i <= n; i++)
      if(!a[i]) return 0;
    return 1;
  }

  void solve() {
    if(check()) return void(cout << "0 0\n\n");
    ans.clear();
    for(int i = n; i > 2; i--)
      if(a[i]) modify(i - 1);
    if(a[2]) modify(2);
    if(!a[1] && !a[2]) solve0();
    else if(a[1]) {
      modify(3);
      modify(2);
      modify(3);
      solve0();
    }else {
      modify(3);
      modify(2);
      modify(3);
      modify(2);
      solve0();
    }
    cout << "0 " << ans.size() << "\n";
    for(int i : ans)
      cout << i << " ";
    cout << "\n";
  }
}

void solve() {
  string str;
  cin >> str;
  n = str.size();
  a = vector<bool> (n + 1, 0);
  for(int i = 1; i <= n; i++) a[i] = (str[i - 1] == '1');
  if(n <= 2) return void(cout << "0 0\n\n");
  if(n == 3) {
    if(!a[2] && (a[1] + a[3] < 2 - a[1] - a[3]))
      cout << "0 1\n2\n";
    else cout << "0 0\n\n";
    return ;
  }
  (n <= 5) ? Task1::solve() : Task2::solve();
}

int main() {
  file();
  ios::sync_with_stdio(0); cin.tie(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}