#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>
// #define __Debug

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int N = 2e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

#ifdef __Debug
  struct Tmp {
    int val, step;
  };

  vector<Tmp> vec;
#else
  struct Node {
    int val, cnt;
  };

  vector<int> vec;
#endif

bool Cmp(int a, int b) {
  return a > b;
}

int n;
int a[N], b[N];
stack<Node> stay;
Node node[N];

signed main() {
  freopen("openhook.in", "r", stdin);
  freopen("openhook.out", "w", stdout);
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  /*Input*/
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  /*Init*/
  sort(a + 1, a + n + 1);
  sort(b + 1, b + n + 1);
  int tmp = 0, num = 0;
  for (int i = 1; i <= n; i++) {
    tmp++;
    if (a[i] != a[i + 1]) {
      num++;
      node[num].val = a[i];
      node[num].cnt = tmp;
      tmp = 0;
    }
  }
  node[num + 1].val = INF;
  /*Solve*/
  #ifdef __Debug
    // for (int i = 1; i <= num; i++) {
    //   printf("Debug1: %d %d\n", node[i].val, node[i].cnt);
    // }
  #endif
  for (int i = 1; i <= num; i++) {
    if (node[i + 1].val - node[i].val >= node[i].cnt) {
      for (int j = 1; j < node[i].cnt; j++) {
        #ifdef __Debug
          vec.push_back((Tmp){node[i].val, j});
        #else
          vec.push_back(j);
        #endif
      }
      int last = node[i + 1].val - node[i].val - node[i].cnt;
      while (last > 0 && stay.empty() == false) {
        Node tmp = stay.top();
        if (tmp.cnt <= last) {
          for (int j = node[i + 1].val - last; j <= node[i + 1].val - last + tmp.cnt - 1; j++) {
            #ifdef __Debug
            vec.push_back((Tmp){tmp.val, j - tmp.val});
            #else
            vec.push_back(j - tmp.val);
            #endif
          }
          last -= tmp.cnt;
          stay.pop();
        }
        else {
          for (int j = node[i + 1].val - last; j <= node[i + 1].val - 1; j++) {
            #ifdef __Debug
              vec.push_back((Tmp){tmp.val, j - tmp.val});
            #else
              vec.push_back(j - tmp.val);
            #endif
          }
          stay.top().cnt -= last;
        }
      }
    }
    else {
      for (int j = 1; j < node[i + 1].val - node[i].val; j++){
        #ifdef __Debug
          vec.push_back((Tmp){node[i].val, j});
        #else
          vec.push_back(j);
        #endif
      }
      stay.push((Node){node[i].val, node[i].cnt - node[i + 1].val + node[i].val});
    }
  }
  int l = node[num].val + node[num].cnt - 1;
  while (stay.empty() == false) {
    Node tmp = stay.top();
    for (int i = l; i <= l + tmp.cnt - 1; i++) {
      #ifdef __Debug
        vec.push_back((Tmp){tmp.val, i - tmp.val});
      #else
        vec.push_back(i - tmp.val);
      #endif
    }
    l += tmp.cnt;
    stay.pop();
  }
  #ifdef __Debug
    for (auto idx:vec) {
      printf("%d %d\n", idx.val, idx.step);
    }
  #endif
  /*output*/
  sort(vec.begin(), vec.end(), Cmp);
  int siz = vec.size();
  ull ans = 0;
  for (int i = 0; i < siz; i++) {
    ans += (ull)vec[i] * b[i + 1];
  }
  printf("%llu", ans);

  return 0;
}