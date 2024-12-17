#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)

using i64 = int64_t;

const int kMaxN = 1 << 6;

int n;
std::string a;
std::array<std::vector<std::pair<int, int>>, kMaxN> adj;
std::array<std::vector<int>, kMaxN> op;
int ans;
std::vector<int> out;
void Dfs(int u, int rt) {
  for (auto p : adj[u]) {
    if (p.first == rt || op[p.first].size()) continue;
    op[p.first] = op[u], op[p.first].emplace_back(p.second);
    Dfs(p.first, rt);
  }
}
void Bru() {
  for (int s = 0; s < (1 << n); ++s) adj[s].clear();
  for (int s = 0; s < (1 << n); ++s) {
    for (int i = 1; i + 1 < n; ++i) {
      int t;
      if (s >> i & 1) {
        t = s & ~(1 << (i - 1)) & ~(1 << (i + 1));
      } else {
        t = s ^ (1 << (i - 1)) ^ (1 << (i + 1));
      }
      adj[t].emplace_back(s, i);
    }
  }
  int sta = 0;
  for (int i = 0; i < n; ++i) sta |= (a[i] - '0') << i;
  ans = __builtin_popcount(sta), out.clear();
  for (int s = 0; s < (1 << n); ++s) {
    for (int i = 0; i < (1 << n); ++i) op[i].clear();
    Dfs(s, s);
    if (op[sta].size() && __builtin_popcount(s) > ans) {
      ans = __builtin_popcount(s);
      out = op[sta];
    }
  }
  std::cout << ans << ' ' << out.size() << '\n';
  std::reverse(ALL(out));
  for (int t : out) std::cout << t + 1 << ' ';
  std::cout << '\n';
}
void Op(int i) {
  out.emplace_back(i);
  if (a[i] == '1') {
    a[i - 1] = a[i + 1] = '0';
  } else {
    a[i - 1] ^= 1, a[i + 1] ^= 1;
  }
}
void Proc() {
  std::cin >> a, n = a.size();
  if (n <= 6) return Bru();
  if (std::count(ALL(a), '1') == n) {
    std::cout << n << " 0\n\n";
    return;
  }
  out.clear();
  for (int i = 0; i + 2 < n; ++i) {
    if (a[i] == '1') Op(i + 1);
  }
  if (a[n - 2] == '1' && a[n - 1] == '1') Op(n - 2);
  if (a[n - 2] == '1' && a[n - 1] == '0') {
    Op(n - 4), Op(n - 3), Op(n - 4);
  } else if (a[n - 2] == '0' && a[n - 1] == '1') {
    Op(n - 3), Op(n - 2), Op(n - 3);
  }
  int i;
  for (i = 0; i + 5 < n; i += 3) {
    Op(i + 1), Op(i + 3), Op(i + 2), Op(i + 4), Op(i + 3);
  }
  if (i == n - 1) {
  } else if (i == n - 2) {
    Op(n - 3), Op(n - 2), Op(n - 3);
  } else if (i == n - 3) {
    Op(n - 2);
  } else if (i == n - 4) {
    Op(n - 3), Op(n - 4), Op(n - 3), Op(n - 2), Op(n - 4), Op(n - 3);
  } else if (i == n - 5) {
    Op(n - 2), Op(n - 4), Op(n - 3);
  }
  std::cout << n - 1 << ' ' << out.size() << '\n';
  for (int t : out) std::cout << t + 1 << ' ';
  std::cout << '\n';
}

auto main() -> int {
  freopen("shi.in", "r", stdin);
  freopen("shi.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  int t;
  for (std::cin >> t; t; --t) Proc();
  return 0;
}