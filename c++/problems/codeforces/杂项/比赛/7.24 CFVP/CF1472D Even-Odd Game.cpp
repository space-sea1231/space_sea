#include <iostream>
#include <stdio.h>
#include <queue>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 3e5 + 10;

int t;
int n;
int a[N];
priority_queue<int> alice, bob;

int Top(bool flag) {
  if (flag == false) {
    if (alice.empty() == false) {
      int tmp = alice.top();
      alice.pop();
      return tmp;
    }
    else {
      return 0;
    }
  }
  if (flag == true) {
    if (bob.empty() == false) {
      int tmp = bob.top();
      bob.pop();
      return tmp;
    }
    else {
      return 0;
    }
  }
  return 0;
}

signed main() {
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    /*Input*/
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    /*Init*/
    while (alice.empty() == false) alice.pop();
    while (bob.empty() == false) bob.pop();
    for (int i = 1; i <= n; i++) {
      if (a[i] % 2 == 0) alice.push(a[i]);
      if (a[i] % 2 == 1) bob.push(a[i]);
    }
    /*Solve*/
    int suma = 0, sumb = 0;
    for (int i = 1; i <= n; i = i + 2) {
      int idxa = Top(0), idxb = Top(1);
      #ifdef __Debug
        printf("i=%d idxa=%d idxb=%d\n", i, idxa, idxb);
      #endif
      if (idxa > idxb) {
        suma += idxa;
        idxa = Top(0);
      }
      else {
        idxb = Top(1);
      }
      if (idxb > idxa) {
        sumb += idxb;
        idxb = Top(0);
      }
      else {
        idxa = Top(1);
      }
    }
    if (suma > sumb) printf("Alice\n");
    if (suma < sumb) printf("Bob\n");
    if (suma == sumb) printf("Tie\n");
  }
  return 0;
}