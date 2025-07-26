/*
  ! 前途似海，来日方长。
  ! Created: 2024/10/17 08:49:41
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define int long long
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

int n, m, ns, al, p[N], b[N], pr[N], sf[N], sm[N], vl[N];
vector<pii> ad[N];
vector<int> dl[N];

inline void pup(int p, int mid) {
  vl[p] = max(vl[mid<<1], vl[mid<<1|1]);
}
inline void build(int p, int l, int r) {
  if (l == r) vl[p] = -sm[l];
  else {
    int mid = (l + r) >> 1;
    build(mid<<1, l, mid);
    build(mid<<1|1, mid + 1, r);
    pup(p, mid);
  }
}
inline void upd(int p, int l, int r, int k, int x) {
  if (l == r) vl[p] = x;
  else {
    int mid = (l + r) >> 1;
    if (mid >= k) upd(mid<<1, l, mid, k, x); else upd(mid<<1|1, mid + 1, r, k, x);
    pup(p, mid);
  }
}
inline int ask(int p, int l, int r, int k) {
  if (l == r) return vl[p];
  int mid = (l + r) >> 1;
  return (mid >= k ? ask(mid<<1, l, mid, k) : ask(mid<<1|1, mid + 1, r, k));
}
inline int ask(int p, int l, int r, int L, int R) {
  if (L <= l && r <= R) return vl[p];
  int mid = (l + r) >> 1;
  int num = -1e18;
  if (mid >= L) num = max(num, ask(mid<<1, l, mid, L, R));
  if (mid <  R) num = max(num, ask(mid<<1|1, mid + 1, r, L, R));
  return num;
}
char buf[1<<21], s[1<<21], *p1, *p2;
#define gc() (p1==p2&&(p2=(p1=buf)+cin.rdbuf()->sgetn(buf,1<<21),p1==p2)?EOF:*p1++)
template<typename T> inline void read(T &x) {
  x = 0; int q = 1; char z;
  while(!isdigit(z = gc())) if(z == '-') q = -1;
  while(isdigit(z)) x = x * 10 + (z ^ 48), z = gc(); x *= q;
}

inline void sol() {
  read(n), ns = al = 0;
  fro(i, 1, n) read(p[i]);
  pr[1] = 1;
  fro(i, 2, n) {
    pr[i] = 0;
    if (p[i] > p[i - 1]) pr[i] = pr[i - 1];
    pr[i]++;
  }
  sf[n] = 1;
  pre(i, n - 1, 1) {
    sf[i] = 0;
    if (p[i] < p[i + 1]) sf[i] = sf[i + 1];
    sf[i]++;
  }
  fro(i, 1, n) {
    if (pr[i] == 1) {
      ns = ns + sf[i] * (sf[i] + 1) / 2;
      al = al + sf[i] * (sf[i] + 1) / 2;
    }
  }
  ns -= n;
  al -= n;
  fro(i, 1, n) {
    if (1 < i && i < n) {
      if (p[i - 1] < p[i] && p[i] < p[i + 1]) {
        sm[i] = pr[i - 1] * sf[i + 1] + pr[i - 1] + sf[i + 1];
      }
      else if (p[i] < p[i + 1])
        sm[i] = sf[i + 1];
      else if (p[i] > p[i - 1])
        sm[i] = pr[i - 1];
    } else {
      if (i == 1 && p[i] < p[i + 1]) sm[i] = sf[i + 1];
      if (i == n && p[i] > p[i - 1]) sm[i] = pr[i - 1];
    }
  }
  build(1, 1, n);
  fro(i, 1, n) {
    if (1 < i && i < n && p[i - 1] < p[i + 1]) {
      if (p[i - 1] > 1) {
        ad[1].eb(p[i], sf[i + 1] - sm[i]);
        dl[p[i - 1] - 1].eb(p[i]);
      }
      ad[p[i - 1]].eb(p[i], pr[i - 1] * sf[i + 1] + pr[i - 1] + sf[i + 1] - sm[i]);
      dl[p[i + 1]].eb(p[i]);
      if (p[i + 1] < n) {
        ad[p[i + 1] + 1].eb(p[i], pr[i - 1] - sm[i]);
        dl[n].eb(p[i]);
      }
    } else {
      if (i < n) {
        ad[1].eb(p[i], sf[i + 1] - sm[i]);
        dl[p[i + 1]].eb(p[i]);
      }
      if (1 < i) {
        ad[p[i - 1]].eb(p[i], pr[i - 1] - sm[i]);
        dl[n].eb(p[i]);
      }
    }
  }
  fro(i, 1, n) b[p[i]] = i;
  fro(i, 1, n) {
    int x = b[i];
    for (auto j : ad[i]) {
      upd(1, 1, n, j.x, j.y);
    }
    int c1 = 0; if (n >= x - 1 && x - 1 >= 1) c1 = ask(1, 1, n, p[x - 1]), upd(1, 1, n, p[x - 1], -1e18);
    int c2 = 0; if (n >= x + 0 && x + 0 >= 1) c2 = ask(1, 1, n, p[x + 0]), upd(1, 1, n, p[x + 0], -1e18);
    int c3 = 0; if (n >= x + 1 && x + 1 >= 1) c3 = ask(1, 1, n, p[x + 1]), upd(1, 1, n, p[x + 1], -1e18);
    if (1 < x && x < n && p[x - 1] < p[x + 1]) {
      if (p[x - 1] > 1) {
        ns = max(ns, al + ask(1, 1, n, 1, p[x - 1] - 1) + sf[x + 1] - sm[x]);
      }
      ns = max(ns, al + ask(1, 1, n, p[x - 1], p[x + 1]) + pr[x - 1] * sf[x + 1] + pr[x - 1] + sf[x + 1] - sm[x]);
      if (p[x + 1] < n) {
        ns = max(ns, al + ask(1, 1, n, p[x + 1] + 1, n) + pr[x - 1] - sm[x]);
      }
    } else {
      if (x < n) ns = max(ns, al + ask(1, 1, n, 1, p[x + 1]) + sf[x + 1] - sm[x]);
      if (1 < x) ns = max(ns, al + ask(1, 1, n, p[x - 1], n) + pr[x - 1] - sm[x]);
      if (1 < x && x < n) {
        ns = max(ns, al + ask(1, 1, n, p[x + 1], p[x - 1]) - sm[x]);
      } else if (1 == x) {
        ns = max(ns, al + ask(1, 1, n, p[x + 1], n) - sm[x]);
      } else if (n == x) {
        ns = max(ns, al + ask(1, 1, n, 1, p[x - 1]) - sm[x]);
      }
    }
    if (n >= x - 1 && x - 1 >= 1) upd(1, 1, n, p[x - 1], c1);
    if (n >= x + 0 && x + 0 >= 1) upd(1, 1, n, p[x + 0], c2);
    if (n >= x + 1 && x + 1 >= 1) upd(1, 1, n, p[x + 1], c3);
    for (auto j : dl[i]) {
      upd(1, 1, n, j, -sm[b[j]]);
    }
  }
  int j = 0;
  int lasrr = 0;
  int lasll = 0;
  fro(i, 1, n) {
    if (pr[i] == 1) {
      if (j) {
        if (p[i] < p[lasll] && p[lasrr] < p[j]) {
          int nm = al;
          nm -= sf[i] - 1;
          nm -= pr[j] - 1;
          int p1 = 1; if (j - 1 >= 1 && p[i] > p[j - 1]) p1 += pr[j - 1], nm += pr[j - 1];
          int p2 = 1; if (i + 1 <= n && p[j] < p[i + 1]) p2 += sf[i + 1], nm += sf[i + 1];
          nm += p1 * p2;
          nm += p1 * (lasrr - lasll + 1);
          nm += p2 * (lasrr - lasll + 1);
          ns = max(ns, nm);
        }
      }
      lasll = i;
    }
    if (sf[i] == 1) j = lasrr, lasrr = i;
  }
  fro(i, 1, n - 1) {
    if (p[i] < p[i + 1]) {
      int nm = al;
      nm -= pr[i] * sf[i + 1];
      if (i - 1 >= 1 && p[i + 1] > p[i - 1]) nm += pr[i - 1];
      if (i + 2 <= n && p[i + 0] < p[i + 2]) nm += sf[i + 2];
      ns = max(ns, nm);
    } else {
      int nm = al;
      nm -= pr[i] - 1;
      nm -= sf[i + 1] - 1;
      int p1 = 1; if (i - 1 >= 1 && p[i + 1] > p[i - 1]) p1 += pr[i - 1], nm += pr[i - 1];
      int p2 = 1; if (i + 2 <= n && p[i + 0] < p[i + 2]) p2 += sf[i + 2], nm += sf[i + 2];
      nm += p1 * p2;
      ns = max(ns, nm);
    }
  }
  cout << (ns + n) % (1ll << 32) << "\n";
  fro(i, 1, n) {
    ad[i].clear();
    dl[i].clear();
    pr[i] = sf[i] = sm[i] = 0;
  }
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
  freopen("wei.in", "r", stdin);
  freopen("wei.out", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 512;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}