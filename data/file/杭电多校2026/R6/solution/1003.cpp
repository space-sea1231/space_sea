#include <bits/extc++.h>
#include <bits/stdc++.h>
#define rep(i,l,r) for (int i = l; i <= r; i ++)
#define rrp(i,l,r) for (int i = l; i >= r; i --)
#define len(x) (int)x.size()
using namespace std;
typedef long long LL;
const int V = 1e7 + 5, B = 1000;

int phi[V], pr[V / 10], tot;
bitset<V> vis; LL f[V], ans[B + 5];

void prework(int n = 1e7) {
  phi[1] = 1;
  rep (i, 2, n) {
    if (!vis[i]) pr[++ tot] = i, phi[i] = i - 1;
    rep (j, 1, tot) {
      if (i > n / pr[j]) break;
      vis[i * pr[j]] = 1;
      if (i % pr[j] == 0) {
        phi[i * pr[j]] = phi[i] * pr[j];
        break;
      }
      phi[i * pr[j]] = phi[i] * (pr[j] - 1);
    }
  }
}

LL query(int x) { return phi[x] * f[x]; }

int n;

void fakemain() {
  fill(f, f + V, 0);
  fill(ans, ans + B + 5, 0);
  cin >> n;
  for (int x; n --; ) cin >> x, f[x] = max(f[x], (LL)phi[x]);
  rep (i, 1, tot) rrp (j, (V - 5) / pr[i], 1) 
    f[j] = max(f[j], f[j * pr[i]]);
  rep (i, 1, V - 5) f[i] = 1LL * f[i] * i / phi[i];
  rep (i, 1, tot) rep (j, 1, (V - 5) / pr[i]) 
    f[j * pr[i]] = max(f[j * pr[i]], f[j]);
  rep (i, 1, V - 5) ans[i % B] ^= f[i] * phi[i] * ((i - 1) / B + 1);
  rep (i, 0, B - 1) cout << ans[i] << '\n';
}

int main() {
  cin.tie(0)->ios::sync_with_stdio(0);
  int T;
  prework();
  cin >> T;
  while (T --) fakemain();
  cerr << 1. * clock() / CLOCKS_PER_SEC << "s\n";
  return 0;
}
