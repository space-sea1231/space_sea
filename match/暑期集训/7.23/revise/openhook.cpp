#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>
#define __Debug

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int N = 1e6 + 10;
const int INF = 2e9 + 10;

int n;
int a[N], b[N];
stack<int> l, r;
vector<int> vec;

bool Cmp(int srcA, int srcB) {
  return srcA > srcB;
}
signed main(){
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  /*Init*/
  sort(a + 1, a + n + 1);
  sort(b + 1, b + n + 1);
  a[n + 1] = INF;
  /*Solve*/
  for (int i = n; i >= 1; i--) {
    if (a[i] < a[i + 1]) {
      if (a[i] < a[i + 1] - 1) {
        l.push(a[i] + 1);
        r.push(a[i + 1] - 1);
      }
    }
    else {
      vec.push_back(l.top() - a[i]);
      l.top()++;
      if (l.top() > r.top()) l.pop(), r.pop();
    }
  }
  /*Output*/
  sort(vec.begin(), vec.end(), Cmp);
  int siz = vec.size();
  ull ans = 0;
  for (int i = 1; i <= siz; i++) {
    ans += (ull)vec[i - 1] * b[i];
  }
  printf("%llu\n", ans);

  return 0;
}