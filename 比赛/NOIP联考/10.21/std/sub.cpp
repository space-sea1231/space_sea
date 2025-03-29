#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

constexpr int mod = 0x3b800001;
int qpow(long long p, int q = mod - 2) {
  int ans = 1;
  while (q != 0) {
    if ((q & 1) != 0) {
      ans = ans * p % mod;
    }
    p = p * p % mod, q >>= 1;
  }
  return ans;
}

bool chk(std::vector<int> v) {
  int n = int(v.size());
  for (int i = 1; i < (1 << n); ++i) {
    int c[3] = {0, 0, 0}, mn = n, mx = 0;
    for (int j = 0; j < n; ++j) {
      if ((i >> j) & 1) {
        ++c[v[j] - 1];
        mn = std::min(mn, j), mx = std::max(mx, j);
      }
    }
    if (mx - mn + 1 != __builtin_popcount(i) &&
        std::max({c[0], c[1], c[2]}) * 2 < __builtin_popcount(i)) {
      return false;
    }
  }
  return true;
}
std::map<std::vector<int>, int> mem;
int bf(std::vector<int> V) {
  if (mem.find(V) != mem.end()) {
    return mem[V];
  }
  int c = 0, t = 1;
  for (int i : V) {
    if (i == 0) {
      ++c, t *= 3;
    }
  }
  int ans = 0;
  for (int i = 0; i < t; ++i) {
    int I = i;
    std::vector<int> v;
    for (int j : V) {
      if (j != 0) {
        v.push_back(j);
      } else {
        v.push_back(I % 3 + 1), I /= 3;  
      }
    }
    ans += chk(v);
  }
  return mem[V] = ans;
}

int n, q;
int y[1000007];
int c[1000007][4];

int main() {
  std::freopen("sub.in", "r", stdin);
  std::freopen("sub.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    std::cin >> y[i];
    for (int j = 0; j <= 3; ++j) {
      c[i][j] = c[i - 1][j] + (y[i] == j);
    }
  }
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    if (r - l + 1 <= 4) {
      std::vector<int> v;
      for (int i = l; i <= r; ++i) {
        v.push_back(y[i]);
      }
      std::cout << bf(v) << '\n';
      continue;
    }
    int c0 = c[r][0] - c[l - 1][0];
    int cc = 0;
    for (int i = 1; i <= 3; ++i) {
      if (c[r][i] == c[l - 1][i]) {
        ++cc;
      }
    }
    if (cc == 0) {
      std::cout << 0 << '\n';
    } else if (cc == 1) {
      std::cout << qpow(2, c0) << '\n';
    } else if (cc == 2) {
      std::cout << qpow(2, c0 + 1) - 1 << '\n';
    } else {
      std::cout << 3LL * qpow(2, c0) % mod - 3 << '\n';
    }
  }
  return 0;
}