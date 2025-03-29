#include "testlib.h"

int main(int argc, char **argv) {
  registerTestlibCmd(argc, argv);
  inf.readInt();
  int t = inf.readInt();
  for (int t_ = 1; t_ <= t; t_++) {
    setTestCase(t_);
    int n = inf.readInt();
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) l[i] = inf.readInt(), r[i] = inf.readInt();
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = ouf.readInt(i ? l[i] : -1, r[i] - 1, "a_" + std::to_string(i + 1));
      if (!i && a[i] == -1) break;
      if (!i) ensuref(a[i] >= l[i], "Integer parameter [name=a_1] equals to %d, "
        "violates the range [%d, %d]", a[i], l[i], r[i] - 1);
    }
    int x = ans.readInt();
    if (a[0] == -1) {
      if (x == -1) continue;
      quitf(_wa, "jury found an answer, participant did not");
    }
    std::map<int, int> mp;
    for (int i = 0; i < n; i++) {
      for (int x : {a[i] - 1, a[i], a[i] + 1}) {
        if (mp.count(x)) {
          quitf(_wa, "the solution is invalid: |a_%d - a_%d| <= 1", mp[x] + 1, i + 1);
        }
      }
      mp[a[i]] = i;
    }
    if (x == -1) quitf(_fail, "??? participant found an answer, jury did not");
  }
  quitf(_ok, "Accepted :)");
}