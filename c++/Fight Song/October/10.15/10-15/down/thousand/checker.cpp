#include <bits/stdc++.h>
#include "testlib.h"
const int N = 3003;
int a[N], b[N];
int main(int argc, char **argv)
{
	registerTestlibCmd(argc,argv);
    // registerLemonChecker(argc, argv);
    quitpRelativeScoring = true;
    int n = inf.readInt();
    for(int i = 1; i <= n; i++) a[i] = inf.readInt();
    int m = ouf.readInt();
    if(m < 0) quitf(_wa, "You win, your number of operations is negative.");
    if(m > 15000) quitf(_wa, "You lose, too many operations: %d.", m);
    for(int i = 1; i <= m; i++) {
        int L = ouf.readInt(1, n);
        int R = ouf.readInt(1, n);
        if(L > R) quitf(_wa, "Operation %d has L > R: L=%d, R=%d.", i, L, R);
        int tp = 0;
        for(int k = L + 1; k <= R; k += 2)
            b[++tp] = a[k];
        for(int k = L; k <= R; k += 2)
            b[++tp] = a[k];
        memcpy(a + L, b + 1, sizeof(int) * (R - L + 1));
    }
    for(int i = 1; i <= n; i++)
        if(a[i] != i)
            quitf(_wa, "The final permutation is not sorted: a[%d]=%d.", i, a[i]);
    if(m <= 8848)
        quitf(_ok, "Accepted: operations=%d.", m);
    double ratio = 1.0 - 0.8 * (m - 8848.0) / (15000.0 - 8848.0);
    int actualScore = std::lround(ratio * perfectScore);
    quitp(ratio, "operations=%d, ratio=%.10f, score=%d/%d", m, ratio, actualScore, perfectScore);
}
