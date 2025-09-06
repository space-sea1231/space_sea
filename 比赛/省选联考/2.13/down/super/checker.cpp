#include "testlib.h"
#include <vector>
#include <string>

int main(int argc, char** argv) {
  registerTestlibCmd(argc, argv);
  int n = inf.readInt(), m = inf.readInt();
  std::vector<std::vector<int>> s(n, std::vector<int>(n, 0));
  for (int i = 0; i < m; ++i) {
    int x = inf.readInt() - 1, y = inf.readInt() - 1;
    s[x][y] = s[y][x] = 1;
  }
  std::vector<std::vector<int>> t(n, std::vector<int>(n, 0));
  for (int i = 0; i < m; ++i) {
    int x = inf.readInt() - 1, y = inf.readInt() - 1;
    t[x][y] = t[y][x] = 1;
  }
  std::string jans = ans.readToken();
  std::string pans = ouf.readToken();
  bool consvalid = true;
  if (pans == "YES") {
    int cnt = ouf.readInt(0, 3'000'000);
    for (int i = 0; i < cnt; ++i) {
      int a = ouf.readInt(1, n) - 1, b = ouf.readInt(1, n) - 1;
      int c = ouf.readInt(1, n) - 1, d = ouf.readInt(1, n) - 1;
      consvalid &= (s[a][b] && s[c][d] && !s[a][c] && !s[b][d]);
      s[a][b] ^= 1, s[c][d] ^= 1, s[a][c] ^= 1, s[b][d] ^= 1;
      s[b][a] ^= 1, s[d][c] ^= 1, s[c][a] ^= 1, s[d][b] ^= 1;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        consvalid &= (s[i][j] == t[i][j]);
      }
    }
  }
  if (jans == "NO") {
    if (pans == "YES" && consvalid) quitf(_fail, "666 zhe ge ru shi gui.");
    if (pans == jans) quitf(_ok, "Accepted.");
    quitf(_wa, "Wrong answer.");
  } else {
    if (pans == "YES") {
      if (consvalid) quitf(_ok, "Accepted.");
      quitp(0.2, "Construction is wrong.");
    } else {
      quitf(_wa, "Wrong answer.");
    }
  }
}