#include <bits/stdc++.h>
using namespace std;
#define N 2000005
#define mod 998244353
int t, n, p[N], f[N];
int main() {
   freopen("wo.in", "r", stdin);
   freopen("wo.out", "w", stdout);
   ios::sync_with_stdio(0);
   cin.tie(0), cout.tie(0);
   cin >> t;
   while (t--) {
      cin >> n;
      for (int i = 1; i <= n << 1; i++) cin >> p[i], f[i] = 0;
      int cnt = n;
      for (int i = 1; i <= n << 1; i += 2)
         if (p[i] && p[i + 1])
            cnt--;
      int x = cnt, y = cnt;
      for (int i = n << 1; i && cnt; i--) {
         if (!~f[i]) continue;
         f[i] = 1, cnt--;
      }
      for (int i = 1; i <= n << 1; i += 2) {
         if (p[i] && p[i + 1]) continue;
         if (p[i])
            if (!f[p[i]]) x--;
            else y--;
         if (p[i + 1])
            if (!f[p[i + 1]]) x--;
            else y--;
      }
      int ans = 1;
      for (int i = 1; i <= n << 1; i += 2) {
         if (p[i] && p[i + 1]) continue;
         if (!p[i] && !p[i + 1]) ans = 2ll * ans % mod * x % mod * y % mod, x--, y--;
         if (p[i])
            if (f[p[i]]) ans = 1ll * ans * x % mod, x--;
            else ans = 1ll * ans * y % mod, y--;
         if (p[i + 1])
            if (f[p[i + 1]]) ans = 1ll * ans * x % mod, x--;
            else ans = 1ll * ans * y % mod, y--;
      }
      cout << ans << "\n";
   }
   return 0;
}