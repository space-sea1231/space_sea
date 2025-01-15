/*
  ! 前途似海，来日方长。
  ! Created: 2024/10/17 08:03:55
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

using i64 = long long;
using pii = pair<int, int>;

bool ST;
const int N = 1e6 + 10;
const int mod = 998244353;

int n, m;
string t;
vector<int> ns;

inline int count() {
  int cnt = 0;
  for (auto i : t) if (i == '1') cnt++;
  return cnt;
}
inline void nand(int x) {
  if (t[x] == '0') {
    t[x - 1] ^= 1;
    t[x + 1] ^= 1;
  } else {
    t[x - 1] = '0';
    t[x + 1] = '0';
  }
  ns.eb(x + 1);
}
inline void sol() {
  cin >> t, n = t.length(), ns.clear();
  fro(i, 2, n - 1) {
    if (t[i - 2] == '0' && t[i - 1] == '0' && t[i - 0] == '0') {
      nand(i - 1);
    }
    if (t[i - 2] == '0' && t[i - 1] == '1' && t[i - 0] == '0') {
      if (i + 1 < n) {
        nand(i - 0);
        nand(i - 1);
      }
    }
    if (t[i - 2] == '0' && t[i - 1] == '0' && t[i - 0] == '1') {
      nand(i - 1);
    }
    if (t[i - 2] == '0' && t[i - 1] == '1' && t[i - 0] == '1') {
      if (i + 1 < n) {
        nand(i - 0);
        nand(i - 1);
      }
    }
  }
  if (n >= 4) {
    if (t[n - 4] == '1' && t[n - 3] == '1' && t[n - 2] == '0' && t[n - 1] == '0') {
      nand(n - 2);
      nand(n - 3);
      nand(n - 2);
      nand(n - 3);
      nand(n - 2);
    }
  }
  if (n >= 5) {
    if (t[n - 5] == '1' && t[n - 4] == '1' && t[n - 3] == '0' && t[n - 2] == '1' && t[n - 1] == '0') {
      nand(n - 4);
      nand(n - 3);
      nand(n - 4);
      nand(n - 2);
      nand(n - 3);
    }
  }
  cout << count() << " " << ns.size() << "\n";
  for (auto i : ns) cout << i << " ";
  cout << "\n";
}

signed main() {
  JYFILE19();
  int t;
  cin >> t;
  while (t--) sol();
  return 0;
}

bool ED;
inline void JYFILE19() {
  freopen("shi.in", "r", stdin);
  freopen("shi.out", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 32;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}