#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;

int n, a[N], v[N];

unsigned dp[N];

unsigned DP( int x, int y ) {
  swap ( a[x], a[y] );
  unsigned res = 0, len = 0;
  for ( int i = 1; i <= n; ++i) {
    if (a[i] > a[i - 1]) {
      ++len;
    } else {
      len = 1;
    }
    res += len;
  }
  swap ( a[x], a[y] );
  return res;
}

void solve() {
  cin >> n;
  for ( int i = 1; i <= n; cin >> a[i++] ) {
  }
  unsigned ans = DP(0, 0);
  for ( int i = 1; i <= n; ++i ) {
    for ( int j = 1; j < i; ++j ) {
      if (a[j] > a[i]) {
        ans = max(ans, DP(i, j));
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  freopen ( "wei.in", "r", stdin );
  freopen ( "wei.out", "w", stdout );
  ios :: sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while (t--) solve();
  return 0;
}
