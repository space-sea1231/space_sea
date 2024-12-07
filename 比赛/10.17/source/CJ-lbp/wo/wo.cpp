#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)

using i64 = int64_t;

const int kMaxN = 2E6 + 5, kMod = 998244353;
auto Power(int a, int b, int p = kMod) {
  int r = 1;
  for (; b; b >>= 1, a = i64{a} * a % p) {
    if (b & 1) r = i64{r} * a % p;
  }
  return r;
}
auto Inv(int a, int p = kMod) { return Power(a, p - 2, p); }
std::array<int, kMaxN> fac, ifac;
void Math() {
  for (int i = fac[0] = 1; i < kMaxN; ++i) fac[i] = i64{fac[i - 1]} * i % kMod;
  ifac.back() = Inv(fac.back());
  for (int i = kMaxN - 1; i; --i) ifac[i - 1] = i64{ifac[i]} * i % kMod;
}
auto Binom(int x, int y) -> int {
  if (x < 0 || y < 0 || x < y) return 0;
  return i64{fac[x]} * ifac[y] % kMod * ifac[x - y] % kMod;
}

int n, m, ptt, ct, k;
std::array<int, kMaxN> p;
std::array<bool, kMaxN> q, c;
void Proc() {
  std::cin >> n, m = k = 0;
  for (int i = 1; i <= n * 2; ++i) q[i] = c[i] = false;
  for (int i = 1; i <= n * 2; ++i) std::cin >> p[i];
  for (int i = 1; i < n * 2; i += 2) {
    if (p[i] && p[i + 1]) {
      c[p[i]] = c[p[i + 1]] = true;
      continue;
    }
    if (p[i]) q[p[i]] = true;
    if (p[i + 1]) q[p[i + 1]] = true;
    m += (!p[i] && !p[i + 1]), ++k;
  }
  int sum = 0, ans = 1, s = 0;
  for (ptt = 1, ct = 0; ptt <= n * 2; ++ptt) {
    ct += !c[ptt];
    if (ct == k) break;
  }
  for (int i = 1; i <= n * 2; ++i) {
    if (c[i]) continue;
    if (q[i]) {
      if (i > ptt) ans = i64{ans} * sum % kMod, --sum, --s;
    } else {
      sum += (i <= ptt), ++s;
    }
  }
  ans = i64{ans} * Binom(s - m, m) % kMod * fac[s - m * 2] % kMod;
  ans = i64{ans} * fac[m] % kMod * Power(2, m) % kMod * fac[m] % kMod;
  std::cout << ans << '\n';
}

auto main() -> int {
  freopen("wo.in", "r", stdin);
  freopen("wo.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  int t;
  for (Math(), std::cin >> t; t; --t) Proc();
  return 0;
}