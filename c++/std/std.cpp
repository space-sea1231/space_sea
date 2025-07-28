#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n, m;
int a[N<<1];

signed main(){
  cin.tie(nullptr)->ios::sycn_with_stdio(false);
  /*Input*/
  cin >> n >> m;
  for (int i=1; i<=n; i++) {
    cin >> a[i];
  }
  for (int i=1; i<=n; i++) {
    cin >> a[i+n];
    a[i+n] = a[i+n] + a[i];
  }
  /*Init*/
  sort(a+1, a+(n<<1)+1, greater<int>());
  /*Solve*/
  int ans = 0;
  for (int i=1; i<=m; i++) {
    ans = ans + a[i];
  }
  printf("%d\n", ans);

  return 0;
}