#include <bits/stdc++.h>

using namespace std;

const int N = 18, Mod = 998442353, Max = INT_MAX >> 1;

struct Array {
  int a[11];
  bool operator < ( const Array &i ) const {
    return a[1] < i.a[1] || a[1] == i.a[1] && a[2] < i.a[2]  || a[1] == i.a[1] && a[2] == i.a[2] && a[3] < i.a[3] ||
      a[1] == i.a[1] && a[2] == i.a[2] && a[3] == i.a[3] && a[4] < i.a[4] || a[1] == i.a[1] && a[2] == i.a[2] && a[3] == i.a[3] && a[4] == i.a[4]
      && a[5] < i.a[5] || a[1] == i.a[1] && a[2] == i.a[2] && a[3] == i.a[3] && a[4] == i.a[4]
      && a[5] == i.a[5] && a[6] < i.a[6] || a[1] == i.a[1] && a[2] == i.a[2] && a[3] == i.a[3] && a[4] == i.a[4]
      && a[5] == i.a[5] && a[6] == i.a[6] && a[7] < i.a[7] || a[1] == i.a[1] && a[2] == i.a[2] && a[3] == i.a[3] && a[4] == i.a[4]
      && a[5] == i.a[5] && a[6] == i.a[6] && a[7] == i.a[7] && a[8] < i.a[8] || a[1] == i.a[1] && a[2] == i.a[2] && a[3] == i.a[3] && a[4] == i.a[4]
      && a[5] == i.a[5] && a[6] == i.a[6] && a[7] == i.a[7] && a[8] == i.a[8] && a[9] < i.a[9] || a[1] == i.a[1] && a[2] == i.a[2] && a[3] == i.a[3] && a[4] == i.a[4]
      && a[5] == i.a[5] && a[6] == i.a[6] && a[7] == i.a[7] && a[8] == i.a[8] && a[9] == i.a[9] && a[10] < i.a[10];
  }
};

int t, n, m, dp[1 << N][N], sum[1 << N][N], p[N][N], dis[N][N], w[N][N];

map<Array, int> f;

int dist( int x, int y ) {
  int res = 0;
  for ( int i = 1; i <= n; ++i ) {
    res += abs(p[x][i] - p[y][i]);
  }
  return res;
}

int get_w( Array a ) {
  int flag = 0;
  for ( int i = 1; i <= n; ++i ) {
    flag |= a.a[i];
  }
  if (!flag) return 1;
  int res = 0;
  for ( int i = 1; i <= n; ++i ) {
    if (a.a[i]) {
      a.a[i]--;
      res += get_w(a);
      a.a[i]++;
    }
  }
  return f[a] = res;
}

int add( int x, int y ) {
  return (x + y) % Mod;
}

int mul( int x, int y ) {
  return x % Mod * y % Mod;
}

void solve() {
  cin >> n >> m;
  for ( int i = 0; i < m; ++i ) {
    for ( int j = 1; j <= n; ++j ) {
      cin >> p[i][j];
    }
  }
  for ( int i = 0; i < (1 << m); ++i ) {
    for ( int j = 0; j < m; ++j ) {
      dp[i][j] = Max, sum[i][j] = 0;
    }
  }
  for ( int i = 0; i < m; ++i ) {
    for ( int j = 0; j < i; ++j ) {
      dis[i][j] = dis[j][i] = dist(i, j);
      w[i][j] = w[j][i] = get_w({0, abs(p[i][1] - p[j][1]), abs(p[i][2] - p[j][2]), abs(p[i][3] - p[j][3]),
                            abs(p[i][4] - p[j][4]), abs(p[i][5] - p[j][5]), abs(p[i][6] - p[j][6]),
                            abs(p[i][7] - p[j][7]), abs(p[i][8] - p[j][8]), abs(p[i][9] - p[j][9]),
                            abs(p[i][10] - p[j][10])});
   }
  }
  for ( int i = 0; i < m; ++i ) {
    int x; cin >> x;
    if (x) {
      dp[1 << i][i] = 0, sum[1 << i][i] = 1;
    }
  }
  for ( int i = 0; i < (1 << m); ++i ) {
    for ( int j = 0; j < m; ++j ) {
      if (i >> j & 1) {
        for ( int k = 0; k < m; ++k ) {
          if (!(i >> k & 1)) {
            if (dp[i | (1 << k)][k] > dp[i][j] + dis[j][k]) {
              dp[i | (1 << k)][k] = dp[i][j] + dis[j][k];
              sum[i | (1 << k)][k] = mul(sum[i][j], w[j][k]);
            } else if (dp[i | (1 << k)][k] == dp[i][j] + dis[j][k]) {
              sum[i | (1 << k)][k] = add(sum[i | (1 << k)][k], mul(sum[i][j], w[j][k]));
            }
          }
        }
      }
    }
  }
  int mx = Max, ans = 0;
  for ( int i = 0; i < m; ++i ) {
    if (dp[(1 << m) - 1][i] < mx) {
      mx = dp[(1 << m) - 1][i];
      ans = sum[(1 << m) - 1][i];
    } else if (dp[(1 << m) - 1][i] == mx) {
      ans = add(ans, sum[(1 << m) - 1][i]);
    }
  }
  if (mx == Max) {
    cout << "NIE" << '\n';
  } else {
    cout << mx << " " << ans << '\n';
  }
}

int main() {
  freopen ( "ge.in", "r", stdin );
  freopen ( "ge.out", "w", stdout );
  ios :: sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
