#include <bits/stdc++.h>
#define ALL(x) begin(x), end(x)
#define All(x, l, r) &x[l], &x[r] + 1
using namespace std;
void file() {
  freopen("wo.in", "r", stdin);
  freopen("wo.out", "w", stdout);
}
using ll = long long;

const int mod = 998244353;
int qpow(int x, int y) {
  int b = x, r = 1;
  for(; y; b = (ll)b * b % mod, y /= 2)
    if(y & 1) r = (ll)r * b % mod;
  return r;
}

const int kL = 2e6 + 5;
int n;
array<int, kL> p;
array<bool, kL> flag;

void solve() {
  cin >> n;
  int N = 2 * n, cnt = N;
  fill(All(flag, 1, N), 0);
  for(int i = 1; i <= N; i++) cin >> p[i];
  for(int i = 1; i <= n; i++) {
    int x = p[2 * i - 1], y = p[2 * i];
    if(x && y) {
      flag[x] = flag[y] = 1;
      cnt -= 2;
    }
  }
  int limit, cu = cnt / 2, cd = cnt / 2, ans = 1;
  for(int i = 1, c = 0; i <= N; i++) {
    if(flag[i]) continue;
    if(++c * 2 == cnt) { limit = i; break; }
  }
  for(int i = 1; i <= n; i++) {
    int x = p[2 * i - 1], y = p[2 * i];
    if(x && y) continue;
    if(!x && !y) continue;
    if(x + y <= limit) cd--;
    else cu--;
  }
  for(int i = 1; i <= n; i++) {
    int x = p[2 * i - 1], y = p[2 * i];
    if(x && y) continue;
    if(!x && !y) continue;
    if(x + y <= limit) ans = (ll)ans * cu-- % mod;
    else ans = (ll)ans * cd-- % mod;
  }
  for(int i = 1; i <= cu; i++)
    ans = 2ll * ans * i % mod * i % mod;
  cout << ans << "\n";
}

int main() {
  file();
  ios::sync_with_stdio(0); cin.tie(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}