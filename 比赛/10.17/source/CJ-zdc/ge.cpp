#include <bits/stdc++.h>
#define ALL(x) begin(x), end(x)
#define All(x, l, r) &x[l], &x[r] + 1
using namespace std;
void file() {
  freopen("ge.in", "r", stdin);
  freopen("ge.out", "w", stdout);
}
using ll = long long;

const int mod = 998442353;
int qpow(int x, int y) {
  int b = x, r = 1;
  for(; y; b = (ll)b * b % mod, y /= 2)
    if(y & 1) r = (ll)r * b % mod;
  return r;
}

const int kL = 4e6 + 5;
array<int, kL> mul, imul;

void init(int N = kL - 1) {
  mul[0] = 1;
  for(int i = 1; i <= N; i++)
    mul[i] = (ll)mul[i - 1] * i % mod;
  imul[N] = qpow(mul[N], mod - 2);
  for(int i = N - 1; ~i; i--)
    imul[i] = (ll)imul[i + 1] * (i + 1) % mod;
}

const ll inf = 1e18;
struct info {
  ll dis, f;
  info() { dis = inf; f = 0; }
  info(ll _d, ll _f) { dis = _d; f = _f; }
};
info operator + (info x, info y) {
  if(x.dis ^ y.dis) return (x.dis < y.dis) ? x : y;
  return info(x.dis, (x.f + y.f) % mod);
}
info operator * (info x, info y) {
  return info(x.dis + y.dis, x.f * y.f % mod);
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> pos (m, vector<int> (n, 0));
  for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++) cin >> pos[i][j];
  vector<int> flag (m, 0);
  for(int i = 0; i < m; i++) cin >> flag[i];
  if(*max_element(ALL(flag)) == 0)
    return void(cout << "NIE\n");
  vector<vector<info>> g (m, vector<info> (m, info()));
  vector<vector<info>> f (1 << m, vector<info> (m, info()));
  for(int i = 0; i < m; i++)
    for(int j = 0; j < m; j++) {
      int sum = 0;
      for(int k = 0; k < n; k++)
        sum += abs(pos[i][k] - pos[j][k]);
      int cnt = mul[sum];
      for(int k = 0; k < n; k++)
        cnt = (ll)cnt * imul[abs(pos[i][k] - pos[j][k])] % mod;
      g[i][j] = info(sum, cnt);
    }
  for(int i = 0; i < m; i++)
    if(flag[i]) f[1 << i][i] = info(0, 1);
  for(int S = 1; S < (1 << m); S++) {
    for(int i = 0; i < m; i++) {
      if(!((S >> i) & 1)) continue;
      for(int j = 0; j < m; j++)
        if(!((S >> j) & 1))
          f[S ^ (1 << j)][j] = f[S ^ (1 << j)][j] + f[S][i] * g[i][j];
    }
  }
  info ans;
  for(int i = 0; i < m; i++)
    ans = ans + f[(1 << m) - 1][i];
  cout << ans.dis << " " << ans.f << "\n";
}

int main() {
  file();
  ios::sync_with_stdio(0); cin.tie(0);
  init();
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}