#include <bits/stdc++.h>
#define ALL(x) begin(x), end(x)
#define All(x, l, r) &x[l], &x[r] + 1
using namespace std;
void file() {
  freopen("wei.in", "r", stdin);
  freopen("wei.out", "w", stdout);
}
using ll = long long;

const int kL = 4e5 + 5, inf = 1e9;
int n;
array<int, kL> p, l, r;

void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> p[i];
  l[0] = l[1] = 1; r[n] = r[n + 1] = n;
  for(int i = 2; i <= n; i++)
    l[i] = (p[i] > p[i - 1]) ? l[i - 1] : i;
  for(int i = n - 1; i; i--)
    r[i] = (p[i] < p[i + 1]) ? r[i + 1] : i;
  ll sum = 0;
  for(int i = 1; i <= n; i++) sum += r[i] - i + 1;
  ll ans = sum;
  for(int i = 1; i <= n; i++)
    for(int j = i + 1; j <= n; j++) {
      ll cur = sum;
      cur -= (ll)(i - l[i] + 1) * (r[i] - i + 1);
      cur -= (ll)(j - l[j] + 1) * (r[j] - j + 1);
      if(r[i] >= j) cur += (ll)(i - l[i] + 1) * (r[j] - j + 1);
      swap(p[i], p[j]);
      int il = (p[i] > p[i - 1]) ? l[i - 1] : i;
      int jr = (p[j] < p[j + 1]) ? r[j + 1] : j;
      int ir = (p[i] < p[i + 1]) ? ((i + 1 == j) ? jr : r[i + 1]) : i;
      int jl = (p[j] > p[j - 1]) ? ((i + 1 == j) ? il : l[j - 1]) : j;
      if(p[i] > p[j]) {
        ir = min(ir, j - 1);
        jl = max(jl, i + 1);
      }else {
        if((ir == j - 1) && (p[j - 1] < p[j])) ir = jr;
        if((jl == i + 1) && (p[i] < p[i + 1])) jl = il;
      }
      cur += (ll)(i - il + 1) * (ir - i + 1);
      cur += (ll)(j - jl + 1) * (jr - j + 1);
      if(ir >= j) cur -= (ll)(i - il + 1) * (jr - j + 1);
      ans = max(ans, cur);
      swap(p[i], p[j]);
    }
  cout << (unsigned int)ans << "\n";
}

int main() {
  file();
  ios::sync_with_stdio(0); cin.tie(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}