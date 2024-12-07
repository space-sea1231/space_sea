/*
  ! 前途似海，来日方长。
  ! Created: 2024/10/17 07:35:01
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
const int N = 1e7 + 10;
const int mod = 998244353;

int n, m, a[N], p[N], v[N];

inline void solve() {
  cin >> n, m = 0;
  fro(i, 1, n) {
    cin >> p[2 * i - 1];
    cin >> p[2 * i - 0];
    if (p[2 * i - 1] != 0 && p[2 * i - 0] != 0) {
      v[p[2 * i - 1]] = 1;
      v[p[2 * i - 0]] = 1;
    }
  }
  fro(i, 1, n + n) if (v[i] == 0) a[++m] = i;
  int ns = 1;
  int x = a[m / 2];
  int zuo = m / 2;
  int you = m / 2;
  fro(i, 1, n) {
    if (p[2 * i - 1] == 0 && p[2 * i - 0] == 0) {
      continue;
    }
    if (p[2 * i - 1] == 0 || p[2 * i - 0] == 0) {
      int y = p[2 * i - 1] + p[2 * i - 0];
      if (y <= x) zuo--; else you--;
    }
  }
  fro(i, 1, n) {
    if (p[2 * i - 1] == 0 && p[2 * i - 0] == 0) {
      ns = 1ll * ns * zuo % mod;
      ns = 1ll * ns * you % mod;
      ns = 2 * ns % mod;
      zuo--, you--;
      continue;
    }
    if (p[2 * i - 1] == 0 || p[2 * i - 0] == 0) {
      int y = p[2 * i - 1] + p[2 * i - 0];
      if (y <= x) {
        ns = 1ll * ns * you % mod;
        you--;
      } else {
        ns = 1ll * ns * zuo % mod;
        zuo--;
      }
    }
  }
  cout << ns << "\n";
  fro(i, 1, n + n) v[i] = 0;
}

signed main() {
  JYFILE19();
  int t;
  cin >> t;
  while (t--) solve();
  return 0;
}

bool ED;
inline void JYFILE19() {
  freopen("wo.in", "r", stdin);
  freopen("wo.out", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 512;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}