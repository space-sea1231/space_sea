#include <bits/stdc++.h>
using namespace std;
#define N 1000005
int t, n;
char s[N];
vector<int> p;
inline void solve(int x) {
   p.push_back(x);
   if (s[x] & 1) s[x - 1] &= 48, s[x + 1] &= 48;
   else s[x - 1] ^= 1, s[x + 1] ^= 1;
}
int main() {
   freopen("shi.in", "r", stdin);
   freopen("shi.out", "w", stdout);
   ios::sync_with_stdio(0);
   cin.tie(0), cout.tie(0);
   cin >> t;
   while (t--) {
      cin >> s + 1, n = strlen(s + 1);
      if (n <= 3) {
         if (n < 3 || s[1] & 1 || s[2] & 1 || s[3] & 1) {
            int ans = 0;
            for (int i = 1; i <= n; i++) ans += s[i] & 1;
            cout << ans << " 0\n\n";
         }
         else cout << "2 1\n2\n";
         continue;
      }
      if (n == 4) {
         if (s[1] & 1)
            if (s[2] & 1)
               if (s[3] & 1)
                  if (s[4] & 1) cout << "4 0\n\n";
                  else cout << "3 0\n\n";
               else
                  if (s[4] & 1) cout << "3 0\n\n";
                  else cout << "3 3\n2 3 2\n";
            else
               if (s[3] & 1)
                  if (s[4] & 1) cout << "3 0\n\n";
                  else cout << "2 0\n\n";
               else
                  if (s[4] & 1) cout << "3 4\n3 2 3 2\n";
                  else cout << "3 1\n3\n";
         else
            if (s[2] & 1)
               if (s[3] & 1)
                  if (s[4] & 1) cout << "3 0\n\n";
                  else cout << "3 3\n2 3 2\n";
               else
                  if (s[4] & 1) cout << "2 0\n\n";
                  else cout << "3 2\n3 2\n";
            else
               if (s[3] & 1)
                  if (s[4] & 1) cout << "3 3\n3 2 3\n";
                  else cout << "3 2\n2 3\n";
               else
                  if (s[4] & 1) cout << "3 1\n2\n";
                  else cout << "2 1\n2\n";
         continue;
      }
      bool flag = 0;
      for (int i = 1; i <= n; i++)
         if (!(s[i] & 1))
            flag = 1;
      if (!flag) { cout << n << " 0\n\n"; continue; }
      p.clear();
      for (int i = n; i > 2; i--)
         if (s[i] & 1)
            solve(i - 1);
      if (s[1] & 1 && s[2] & 1) solve(2);
      if (s[1] & 1) solve(3), solve(2), solve(3);
      if (s[2] & 1) solve(3), solve(2), solve(3), solve(2);
      for (int i = 1; i < n; i++) {
         if (s[i] & 1) continue;
         if (s[i + 1] & 1)
            if (i + 2 < n) solve(i + 2), solve(i + 1);
            else break;
         else
            if (i + 1 < n) solve(i + 1);
            else break;
      }
      if (!(s[n - 2] & 1) && !(s[n] & 1)) solve(n - 3), solve(n - 2), solve(n - 3), solve(n - 1), solve(n - 2);
      int ans = 0;
      for (int i = 1; i <= n; i++) ans += s[i] & 1;
      cout << ans << " " << p.size() << "\n";
      for (auto i : p) cout << i << " ";
      cout << "\n";
   }
   return 0;
}