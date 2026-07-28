#include <iostream>
#include <cmath>

long double pi = acosl(-1);
constexpr int mod = 0x3b800001;
int n, m;

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n >> m;
  int ans = 0;
  int s1 = 0, s2 = 0;
  for (int i = 1; i <= n; ++i) {
    s1 = (s1 + 1LL * i * (n - i + 1)) % mod;
    s1 = (s1 + 1LL * i * (n - i)) % mod;
    s2 = (s2 + 1LL * i * i) % mod;
    s2 = (s2 + 1LL * i * (i - 1)) % mod;
  }
  int ans_pi = 0, ans_1 = 0;
  for (int i = 1; i < m; ++i) {
    if (pi * i > 2 * m) {
      ans_1 = (ans_1 + 1LL * s1 * (m + m)) % mod;
      ans_1 = (ans_1 + 1LL * s2 * (m + m)) % mod;
    } else {
      ans_1 = (ans_1 - 1LL * s1 * (m + m) % mod + mod) % mod;
      ans_1 = (ans_1 + 1LL * s2 * (m + m) % mod + mod) % mod;
      ans_pi = (ans_pi + 2LL * i * s1) % mod;
    }
  }
  for (int i = 1, j = n + n; i <= n + n; ++i, --j) {
    ans_1 = (ans_1 + 1LL * m * i % mod * j) % mod;
  }
  std::cout << ans_pi << ' ' << ans_1 << '\n';
  return 0;
}