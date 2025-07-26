#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)

using i64 = int64_t;

const int kMaxN = 2E3 + 5;

int n;
std::array<int, kMaxN> p, lp, rp;
std::array<std::array<i64, kMaxN>, kMaxN> ans;
void Proc() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> p[i];
  for (int i = 1; i <= n; ++i) {
    lp[i] = (i > 1 && p[i - 1] < p[i] ? lp[i - 1] : i);
  }
  for (int i = n; i; --i) {
    rp[i] = (i < n && p[i] < p[i + 1] ? rp[i + 1] : i);
  }
  for (int l = 1; l <= n; ++l) {
    ans[l][l - 1] = 0;
    for (int r = l; r <= n; ++r) {
      ans[l][r] = ans[l][r - 1] + r - std::max(l, lp[r]) + 1;
    }
  }
  i64 res = ans[1][n];
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 2; j <= n; ++j) {
      i64 cur = ans[1][i - 1] + ans[i + 1][j - 1] + ans[j + 1][n];
      // int l = i - lp[i] + 1, r = std::min(rp[i], j - 1) - i + 1;
      // if (i > 1 && p[i - 1] > p[j]) l = 1;
      // if (i < n && p[i + 1] < p[j]) r = 1;
      // cur += i64{l} * r;
      // int u = j - std::max(i + 1, lp[j]) + 1, v = rp[j] - j + 1;
      // if (j > 1 && p[j - 1] > p[i]) u = 1;
      // if (j < n && p[j + 1] < p[i]) v = 1;
      // cur += i64{u} * v;
      // if (rp[i + 1] >= j - 1 && p[j] < p[i + 1] && p[i] > p[j - 1]) {
      //   cur += i64{l} * v;
      // }
      std::swap(p[i], p[j]);
      int l = i, r = i;
      while (l > 1 && p[l - 1] < p[l]) --l;
      while (r + 1 < j && p[r] < p[r + 1]) ++r;
      cur += i64{i - l + 1} * (r - i + 1);
      int u = j, v = j;
      while (u - 1 > i && p[u - 1] < p[u]) --u;
      while (v < n && p[v] < p[v + 1]) ++v;
      cur += i64{j - u + 1} * (v - j + 1);
      bool ok = true;
      for (int k = i; k < j; ++k) ok &= p[k] < p[k + 1];
      if (ok) {
        cur += i64{i - l + 1} * (v - j + 1);
      }
      res = std::max(res, cur);
      std::swap(p[i], p[j]);
    }
  }
  for (int i = 1; i < n; ++i) {
    i64 cur = ans[1][i - 1] + ans[i + 2][n];
    std::swap(p[i], p[i + 1]);
    int l = i, r = i, j = i + 1;
    while (l > 1 && p[l - 1] < p[l]) --l;
    while (r + 1 < j && p[r + 1] > p[r]) ++r;
    cur += i - l + 1;
    int u = j, v = j;
    while (u - 1 > i && p[u - 1] < p[u]) --u;
    while (v < n && p[v + 1] > p[v]) ++v;
    cur += v - j + 1;
    if (p[i] < p[j]) cur += i64{i - l + 1} * (v - j + 1);
    res = std::max(res, cur);
    std::swap(p[i], p[i + 1]);
  }
  std::cout << (res & ((i64{1} << 32) - 1)) << '\n';
}

auto main() -> int {
  freopen("wei.in", "r", stdin);
  freopen("wei.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  int t;
  for (std::cin >> t; t; --t) Proc();
  return 0;
}