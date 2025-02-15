#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 5;
int n, a[N], f[N];
signed main() {
  freopen("wei.in", "r", stdin);
  freopen("wei.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    cin >> n;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
      f[i] = 1;
      for(int j = 1; j < i; j++) {
        if(a[j] < a[i]) {
          f[i] += f[j];
        }
      }
      ans += f[i];
    }
    for(int i = 1; i < n; i++) {
      for(int j = i + 1; j <= n; j++) {
        swap(a[i], a[j]);
        int tans = 0;
        for(int k = 1; k <= n; k++) {
          f[k] = 1;
          for(int l = 1; l < k; l++) {
            if(a[l] < a[k]) {
              f[k] += f[l];
            }
          }
          tans += f[k];
        }
        ans = max(ans, tans);
        swap(a[i], a[j]);
      }
    }
    cout << ans % (1ll << 32) << '\n';
  }
  return 0;
}