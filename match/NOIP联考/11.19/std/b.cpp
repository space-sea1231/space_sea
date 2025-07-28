#include <iostream>

constexpr int mod = 0x3b800001;
int n, k;
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
int fac[10000007], ifac[10000007], inv[10000007];
int dp[10000007];

int main() {
  std::freopen("b.in", "r", stdin);
  std::freopen("b.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n >> k;
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = 1LL * fac[i - 1] * i % mod;
  }
  ifac[n] = qpow(fac[n]);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * (i + 1LL) % mod;
  }
  for (int i = 1; i <= n; ++i) {
    inv[i] = 1LL * fac[i - 1] * ifac[i] % mod;
  }
  if (k >= n) {
    std::cout << fac[n] << '\n';
    return 0;
  }
  dp[0] = 1;
  int ans = 0;
  for (int i = 1; i < n; ++i) {
    dp[i] = dp[i - 1];
    if (i - k - 1 >= 0) {
      dp[i] = (dp[i] - dp[i - k - 1] + mod) % mod;
    }
    dp[i] = 1LL * dp[i] * inv[n - i] % mod;
    if (i >= n - k) {
      ans = (ans + 1LL * fac[n - 1] * dp[i]) % mod;
    }
    dp[i] = (dp[i] + dp[i - 1]) % mod;
  }
  std::cout << ans << '\n';
  return 0;
}