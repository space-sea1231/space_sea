#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;
const int N=1e6+10;
int n, m;
struct Node {
  int val;
  int id;
  bool operator<(const Node srcb) const{
    return val>srcb.val;
  }
}a[N], b[N];
signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i<=n; i++){
    cin >> a[i].val;
    a[i].id=i;
  }
  for (int j = 1; j <= n; j++) {
    cin >> b[i].val;
    b[i].id=i;
    b[i].val+=a[i].val;
  }
  
  return 0;
}