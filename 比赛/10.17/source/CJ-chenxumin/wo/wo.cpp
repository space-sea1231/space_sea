#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6 + 5, MOD = 998244353;
int t, n, a[N], vis[N], v2[N], b[N];

signed main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  freopen("wo.in", "r", stdin);
  freopen("wo.out", "w", stdout);
  cin >> t;
  vis[0]  = v2[0] = 1;
  for(int i = 1; i <= 2e6; i++)vis[i] = vis[i - 1] * i % MOD;
  for(int i = 1; i <= 2e6; i++)v2[i] = v2[i - 1] * 2 % MOD;
  for(; t; t--){
    cin >> n;
    int m = 1, mid = n;
    for(int i = 1; i <= n * 2; i++){
      cin >> a[i];
      if(i % 2 == 0){
        if(a[i] > 0 && a[i - 1] > 0){
          if(a[i] > mid && a[i - 1] > mid)mid--;
          else if(a[i] <= mid && a[i - 1] <= mid)mid++;
        }else{
          b[++m] = a[i - 1];
          b[++m] = a[i];
        }
      }
    }
    int cnt1 = m / 2, cnt2 = m / 2, cnt3 = 0;
    for(int i = 1; i <= m; i++){
      if(b[i]){
        if(b[i] > mid)cnt2--;
        else cnt1--;
      }
      if(i % 2 == 0 && b[i] == 0 && b[i - 1] == 0)cnt3++;
    }
    cout << (vis[cnt1] * vis[cnt2] % MOD) * v2[cnt3] % MOD << '\n';
  }
  return 0;
}