#include "testlib.h"
#include <vector>
#include <utility>

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // registerLemonChecker(argc, argv);
    int n = inf.readInt();
    int k0 = inf.readInt();
    std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[i][j] = inf.readInt();
    int k = ouf.readInt();
    if (k < 0) quitf(_wa, "Number of operations k cannot be negative, found %d", k);
    if (k > 2 * n * n) quitf(_wa, "Number of operations k exceeds 2*n^2: k = %d, 2*n^2 = %d", k, 2 * n * n);
    for (int step = 1; step <= k; ++step) {
        int x1 = ouf.readInt(1, n, "x1");
        int y1 = ouf.readInt(1, n, "y1");
        int x2 = ouf.readInt(1, n, "x2");
        int y2 = ouf.readInt(1, n, "y2");
        if (x1 != x2 && y1 != y2)
            quitf(_wa, "Move %d is invalid: (%d, %d) and (%d, %d) are neither in the same row nor in the same column", step, x1, y1, x2, y2);
        std::swap(a[x1][y1], a[x2][y2]);
    }
    ouf.seekEof();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[i][j] != (i - 1) * n + j)
                quitf(_wa, "Matrix is not restored: A[%d][%d] = %d, expected %d", i, j, a[i][j], (i - 1) * n + j);
    if (k <= k0) quitf(_ok, "Accepted! Restored in k = %d <= k0 = %d operations.", k, k0);
    else quitp(0.4, "Partially correct: Restored in k = %d operations (k0 < k <= 2*n^2).", k);
    return 0;
}
