#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;

int t;
int n;
int a[N];

bool Cmp(int a, int b) {
  return a > b;
}

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    int suma = 0, sumb = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1, Cmp);
    for (int i = 1; i <= n; i++) {
      if (suma > sumb) sumb = sumb + a[i];
      else suma = suma + a[i];
    }
    if (suma == sumb) printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}