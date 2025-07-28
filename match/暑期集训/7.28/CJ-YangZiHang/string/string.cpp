#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s, tmp;

namespace pts1 {
  const int N = 20;

  int a[N];
  string d;
  string t[N];
}

namespace pts2 {
  const int N = 1e6 + 10;

  int a[N];
  ull cnt[N];
  string d;
}

signed main() {
  freopen("string.in", "r", stdin);
  freopen("string.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  cin >> n >> s >> tmp;
  if (n <= 10) {
    using namespace pts1;
    t[0] = tmp;
    int slen = s.size();
    for (int i = 1; i <= n; i++) {
      int k;
      cin >> k;
      for (int j = 1; j <= k; j++) {
        cin >> a[i];
        t[i] = t[i] + t[a[i]];
      }
      cin >> d;
      t[i] = t[i] + d;
      int cnt = 0;
      int len = t[i].size();
      for (int j = 0; j < len - slen + 1; j++) {
        if (t[i][j] == s[0]) {
          if (t[i].substr(j, slen) == s) {
            cnt++;
          }
        } 
      }
      printf("%d\n", cnt);
    }
    return 0;
  }
  else {
    using namespace pts2;
    cnt[0] = tmp.size();
    int slen = s.size();
    for (int i = 1; i <= n; i++) {
      int k;
      cin >> k;
      for (int j = 1; j <= k; j++) {
        cin >> a[i];
        cnt[i] = cnt[i] + cnt[a[i]];
      }
      cin >> d;
      cnt[i] = cnt[i] + (ull)d.size();
      printf("%llu\n", (ull)(cnt[i] - slen + 1));
    }
  }
  return 0;
}