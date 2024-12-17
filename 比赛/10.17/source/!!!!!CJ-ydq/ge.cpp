/*
  ! 前途似海，来日方长。
  ! Created: 2024/10/17 10:41:22
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
const int mod = 998442353;

int n, m, s[20], h[20];
vector<int> p[20];
vector<int> r[20];
struct Node {
  i64 num, len;
  inline void upd(Node x, Node y) {
    if (x.len + y.len < len) {
      len = x.len + y.len;
      num = x.num * y.num % mod;
    } else if (x.len + y.len == len) {
      num = (num + x.num * y.num) % mod;
    }
  }
  inline void upd(Node x) {
    if (x.len < len) {
      len = x.len;
      num = x.num;
    } else if (x.len == len) {
      num = (num + x.num) % mod;
    }
  }
  inline void add(Node x) {
    len = len + x.len;
    num = num * x.num % mod;
  }
};
Node f[1 << 16][16];
Node g[16][16];

namespace Math {
int Fc[5000010], Iv[5000010];
template<typename T> inline void add(T&x, int y) { if ((x += y) >= mod) x -= mod; }
template<typename T> inline void del(T&x, int y) { if ((x -= y) < 0) x += mod; }
template<typename T> inline void add(T&x, int y, int z) { x = (x + (long long) y * z) % mod; }
template<typename T> inline void mo(T&x) { x = (x % mod + mod) % mod; }
inline long long power(long long x, long long y) {
  long long res = 1;
  while (y) { if (y & 1) res = res * x % mod; x = x * x % mod, y /= 2; }
  return res;
}
inline void init(int n) {
  Fc[0] = 1;
  for (int i = 1; i <= n; i++) Fc[i] = (long long) Fc[i - 1] * i % mod; Iv[n] = power(Fc[n], mod - 2);
  for (int i = n; i >= 1; i--) Iv[i - 1] = (long long) Iv[i] * i % mod;
}
inline long long C(int x, int y) { return (x < 0 || y < 0 || x < y ? 0 : (long long) Fc[x] * Iv[y] % mod * Iv[x - y] % mod); }
} using namespace Math;

inline void solve() {
  cin >> n >> m;
  map<vector<int>, int> mp;
  int k = 0;
  fro(i, 0, m - 1) {
    h[i] = 0;
    p[i].clear();
    p[i].resize(n + 1);
    fro(j, 1, n) cin >> p[i][j];
    if (mp.count(p[i]) == 0) {
      r[mp[p[i]] = k++] = p[i];
    }
  }
  fro(i, 0, m - 1) cin >> s[i], h[mp[p[i]]] |= s[i];
  m = k;
  fro(i, 0, m - 1)
    fro(j, 0, m - 1) {
      if (i == j) continue;
      i64 siz = 0;
      i64 num = 1;
      fro(k, 1, n) {
        siz += abs(r[i][k] - r[j][k]);
      }
      num = Fc[siz];
      fro(k, 1, n) {
        num = num * Iv[abs(r[i][k] - r[j][k])] % mod;
      }
      g[i][j] = {num, siz};
    }
  bool flag = 0;
  fro(i, 0, m - 1) if (h[i]) flag = 1;
  if (flag == 0) { cout << "NIE\n"; return; }
  fro(i, 0, (1 << m) - 1) fro(j, 0, m - 1)  f[i][j] = {0, 1000000000};
  fro(i, 0, m - 1) {
    if (h[i] == 1) {
      f[1 << i][i] = {1, 0};
    }
  }
  fro(i, 0, (1 << m) - 1) {
    fro(j, 0, m - 1) {
      if ((i >> j) & 1) {
        fro(k, 0, m - 1) {
          if ((((i >> k) & 1)) == 0) {
            f[i | (1 << k)][k].upd(f[i][j], g[j][k]);
          }
        }
      }
    }
  }
  Node ans = {0, 1000000000};
  fro(i, 0, m - 1)
    ans.upd(f[(1 << m) - 1][i]);
  cout << ans.len << " " << ans.num << "\n";
}

signed main() {
  JYFILE19();
  int t;
  cin >> t;
  init(5000000);
  while (t--) solve();
  return 0;
}

bool ED;
inline void JYFILE19() {
  freopen("ge.in", "r", stdin);
  freopen("ge.out", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 512;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}