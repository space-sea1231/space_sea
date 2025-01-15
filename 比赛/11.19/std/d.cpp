#include <iostream>
#include <algorithm>

constexpr int mod = 0x3b9aca07;
int qpow(long long p, int q = mod - 2) {
  int ans = 1;
  while (q) {
    if (q & 1) {
      ans = ans * p % mod;
    }
    p = p * p % mod, q >>= 1;
  }
  return ans;
}
int fac[65537], ifac[65537];
void precalc(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = 1LL * fac[i - 1] * i % mod;
  }
  ifac[n] = qpow(fac[n]);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * (i + 1LL) % mod;
  }
}
int C(int n, int m) {
  if (!(0 <= m && m <= n)) {
    return 0;
  }
  return 1LL * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, m, a[107];
int dp[107][1 << 17];

int main() {
  std::freopen("d.in", "r", stdin);
  std::freopen("d.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  precalc(1 << 16);
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    std::cin >> a[i];
  }
  std::sort(a + 1, a + m + 1, std::greater<>());
  dp[0][0] = 1;
  for (int i = 1; i <= m; ++i) {
    for (int j = 0; j < (1 << n); ++j) {
      dp[i][j] = dp[i - 1][j];
      for (int k = 0; k < n; ++k) {
        if ((j >> k) & 1) {
          dp[i][j] = (dp[i][j] + 1LL * dp[i - 1][j ^ (1 << k)] * C((1 << n) - a[i] - (j ^ (1 << k)), (1 << k) - 1)) % mod;
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < (1 << n); ++i) {
    int d = dp[m][i];
    if (__builtin_parity(i)) {
      d = mod - d;
    }
    for (int j = 0; j < n; ++j) {
      if ((i >> j) & 1) {
        d = 1LL * d * fac[1 << j] % mod;
      }
    }
    ans = (ans + 1LL * d * fac[(1 << n) - 1 - i]) % mod;
  }
  std::cout << ans * (1LL << n) % mod << '\n';
  return 0;
}