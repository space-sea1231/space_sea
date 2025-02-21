#include <bits/stdc++.h>

using namespace std;

const int N = 8 + 5;

int t, n, a[N];

void solve() {
  cin >> n;
  for ( int i = 1; i <= n * 2; ++i ) {
    cin >> a[i];
  }
  int p[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int mx = 0, ans = 0;
  do {
    bool flag = 0;
    for ( int i = 1; i <= n * 2; ++i ) {
      flag |= a[i] && a[i] != p[i];
    }
    if (flag) continue;
    int res = 0;
    for ( int i = 1; i <= n; ++i ) {
      res += abs(p[i * 2] - p[i * 2 - 1]);
    }
    if (res > mx) {
      mx = res, ans = 1;
    } else if (res == mx) {
      ++ans;
    }
  } while (next_permutation ( p + 1, p + 2 * n + 1 ));
  cout << ans << '\n';
}

int main() {
  freopen ( "wo.in", "r", stdin );
  freopen ( "wo.out", "w", stdout );
  ios :: sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
