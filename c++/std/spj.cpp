#include "testlib.h"

#include <deque>
#include <vector>

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    const int T = inf.readInt();
    for (int tc = 1; tc <= T; ++tc) {
        const int n = inf.readInt();
        const int m = inf.readInt();
        const int k = inf.readInt();
        std::vector<int> a(m);
        for (int& x : a) x = inf.readInt(1, k, "a_i");

        const int op = ouf.readInt(m, 2 * m, "op");
        // front is the bottom; back is the top.
        std::vector<std::deque<int>> stacks(n + 1);
        int used = 0;
        for (int step = 1; step <= op; ++step) {
            const int type = ouf.readInt(1, 2, "type");
            const int s = ouf.readInt(1, n, "s");
            if (type == 1) {
                if (used == m) {
                    quitf(_wa, "Case %d, operation %d: the deck is empty",
                          tc, step);
                }
                const int x = a[used++];
                auto& st = stacks[s];
                if (!st.empty() && st.back() == x) {
                    st.pop_back();
                } else {
                    st.push_back(x);
                }
            } else {
                const int t = ouf.readInt(1, n, "t");
                if (s == t) {
                    quitf(_wa, "Case %d, operation %d: stacks must be distinct",
                          tc, step);
                }
                auto& lhs = stacks[s];
                auto& rhs = stacks[t];
                // No matching bottom cards (including an empty stack): no-op.
                if (!lhs.empty() && !rhs.empty() && lhs.front() == rhs.front()) {
                    lhs.pop_front();
                    rhs.pop_front();
                }
            }
        }

        if (used != m) {
            quitf(_wa, "Case %d: %d cards remain in the deck", tc, m - used);
        }
        for (int s = 1; s <= n; ++s) {
            if (!stacks[s].empty()) {
                quitf(_wa, "Case %d: stack %d still contains %d cards",
                      tc, s, static_cast<int>(stacks[s].size()));
            }
        }
    }

    if (!ouf.seekEof()) quitf(_wa, "Extra output after the last case");
    quitf(_ok, "All %d cases cleared", T);
}
