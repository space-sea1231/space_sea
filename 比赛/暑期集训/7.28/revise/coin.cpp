#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n, m;
int a[N], b[N];
ll suma[N], sumb[N];

signed main(){
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  for (int i=1; i<=n; i++){
    cin >> a[i];
  }
  for (int i=1; i<=n; i++){
    cin >> b[i];
  }
  /*Init*/
  for (int i=1; i<=n; i++){
    b[i]+=a[i];
  }
  sort(a+1, a+n+1, greater<int>());
  sort(b+1, b+n+1, greater<int>());
  for (int i=1; i<=n; i++){
    suma[i]=suma[i-1]+a[i];
    sumb[i]=sumb[i-1]+b[i];
  }
  /*Solve*/
  ll ans=0;
  int posa=0, posb=0;
  for (int i=1; i<=m; i++){
    if (posa>0&&b[posb+1]>a[posa]+a[posa+1]) posb++, posa--;
    else posa++;
    ans^=suma[posa]+sumb[posb];
  }
  printf("%lld\n", ans);

  return 0;
}
/*
1 101 1
100 1 100
a[2]
b[1]
a[2]+b[1]
*/