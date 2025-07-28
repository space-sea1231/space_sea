#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 50;

ll n;
char c[N];
int siz;

signed main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> c >> n;
  /*Init*/
  siz = strlen(c);
  /*Solve*/
  while (siz < n) {
    ll tmp = siz;
    while (tmp < n) tmp = (tmp << 1);
    tmp = (tmp >> 1);
    n = n - (tmp + 1);
    if (n == 0) n = tmp; 
  }
  /*Output*/
  printf("%c\n", c[n - 1]);

  return 0;
}
/*
COW WCO OCOWWC
*/