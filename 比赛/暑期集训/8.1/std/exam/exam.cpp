#include <bits/stdc++.h>
using namespace std;

const int N = 8010;
int n, m, k, p[N], v[N], a[N], b[N];
int f1[N], bel[110], f2[N];

int main(){
  freopen("exam.in", "r", stdin);
  freopen("exam.out", "w", stdout);
  scanf("%d%d%d", &n, &m, &k);
  for(int i = 1; i <= k; ++ i){
    scanf("%d", &p[i]);
  }
  for(int i = 1; i <= k; ++ i){
    scanf("%d", &v[i]);
    for(int j = p[i-1]+1; j <= p[i]; ++ j){
      bel[j] = i;
    }
  }
  memset(f1, 0xcf, sizeof(f1));
  f1[0] = 0;
  for(int i = 1; i <= n; ++ i){
    scanf("%d%d", &a[i], &b[i]);
  }
  for(int i = 1; i <= n; ++ i){
    for(int j = a[i]; j <= m; ++ j){
      f1[j] = max(f1[j], f1[j-a[i]] + b[i]);
    }
  }
  for(int i = 1; i <= m; ++ i){
    if(f1[i] <= 0) continue;
    int fr = v[bel[(100 * f1[i] - 1) / i + 1]];
    for(int j = i; j <= m; ++ j){
      f2[j] = max(f2[j], f2[j-i] + fr * i);
    }
  }
  printf("%d\n", f2[m]);
  return 0;
}