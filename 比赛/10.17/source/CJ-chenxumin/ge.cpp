#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 18, MOD = 998442353, L = 5e6 + 5;
int t, n, m, dp[N][1 << N], sum[N][1 << N], v[N][N], v2[N][N], vv[L], v3[L], b[L];
struct Node{
  int x[N];
}a[N];
int dis(int x, int y){
  if(v[x][y] != -1)return v[x][y];
  v[x][y] = 0;
  for(int i = 1; i <= n; i++){
    v[x][y] = (v[x][y] + abs(a[x].x[i] - a[y].x[i])) % MOD;
  }
  return v[x][y];
}
int go(int x, int y){
  if(v2[x][y] != -1)return v2[x][y];
  int cnt = 0;
  for(int i = 1; i <= n; i++){
    cnt += abs(a[x].x[i] - a[y].x[i]);
  }
  v2[x][y] = vv[cnt];
  for(int i = 1; i <= n; i++){
    v2[x][y] = (v2[x][y] * v3[abs(a[x].x[i] - a[y].x[i])]) % MOD;
  }
  return v2[x][y];
}
void solve(int x){
  cin >> n >> m;
  fill(&dp[0][0], &dp[m][1 << m] + 1, 1e18);
  fill(&sum[0][0], &sum[m][1 << m] + 1, 0);
  fill(&v[0][0], &v[m][m] + 1, -1);
  fill(&v2[0][0], &v2[m][m] + 1, -1);
  for(int i = 0; i < m; i++){
    for(int j = 1; j <= n; j++){
      cin >> a[i].x[j];
    }
  }
  int vis = 0;
  for(int i = 0, y; i < m; i++){
    cin >> y;
    if(y){
      dp[i][(1 << i)] = 0;
      sum[i][(1 << i)] = 1;
      vis = 1;
    }
  }
  if(!vis){
    cout << "NIE\n";
    return;
  }
  for(int i = 1; i < (1 << m); i++){
    for(int j = 0; j < m; j++){
      for(int k = 0; k < m; k++){
        if(!((i >> k) & 1) && j != k){
          if(dp[j][i] + dis(j, k) < dp[k][i | (1 << k)]){
            dp[k][i | (1 << k)] = dp[j][i] + dis(j, k);
            sum[k][i | (1 << k)] = go(j, k) * sum[j][i] % MOD;
          }else if(dp[j][i] + dis(j, k) == dp[k][i | (1 << k)]){
            sum[k][i | (1 << k)] = (sum[k][i | (1 << k)] + go(j, k) * sum[j][i]) % MOD;
          }
        }
      }
    }
  }
  int ans1 = 1e18, ans2 = 0;
  for(int i = 0; i < m; i++){
    if(dp[i][(1 << m) - 1] == ans1)ans2 = (ans2 + sum[i][(1 << m) - 1]) % MOD;
    else if(dp[i][(1 << m) - 1] < ans1){
      ans1 = dp[i][(1 << m) - 1];
      ans2 = sum[i][(1 << m) - 1];
    }
  }
  cout << ans1 << ' ' << ans2 << '\n';
}
signed main(){
  freopen("ge.in", "r", stdin);
  freopen("ge.out", "w", stdout);
  vv[0] = v3[0] = 1;
  b[1] = 1;
  b[0] = 1;
  for(int i = 2; i <= 5e6; i++){
    b[i] = (MOD - MOD / i) * b[MOD % i] % MOD;
  }
  for(int i = 1; i <= 5e6; i++){
    vv[i] = vv[i - 1] * i % MOD;
    v3[i] = v3[i - 1] * b[i] % MOD;
  }
  cin >> t;
  for(int i = 1; t; t--, solve(i), i++);
  return 0;
}