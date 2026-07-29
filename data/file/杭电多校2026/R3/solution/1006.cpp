#include <bits/stdc++.h>
using namespace std;

/*
    在 [1,n] 中构造字典序最小的最大反链：
    任意两个选中的数不能互相整除。

    每个奇数 p 对应一条链：
        p, 2p, 4p, ...

    从每条链中选一个 p * 2^{f[p]}。

    对于奇数 p < r 且 p | r，需要：
        f[p] > f[r].
*/

class ChainConstruction {
private:
    int n;

    // 所有不超过 n 的奇数。
    vector<int> odd;

    /*
        L[p] <= f[p] <= U[p]

        数组只在 p 为奇数时使用。
    */
    vector<int> L, U;

    // 该奇数链是否已经确定。
    vector<bool> chosen;

    // feasible() 中计算出的最小可行指数。
    vector<int> need;

    /*
        判断当前所有上下界约束是否存在合法补全。

        因为 p | r 且 p < r 时要求 f[p] > f[r]，
        所以从大到小计算 need。
    */
    bool feasible() {
        fill(need.begin(), need.end(), 0);

        for (int idx = (int)odd.size() - 1; idx >= 0; --idx) {
            int p = odd[idx];

            need[p] = L[p];

            /*
                r 是 p 的真奇数倍数：
                    r = 3p, 5p, 7p, ...

                要求：
                    f[p] >= f[r] + 1.
            */
            for (long long r = 3LL * p; r <= n; r += 2LL * p) {
                need[p] = max(need[p], need[(int)r] + 1);
            }

            if (need[p] > U[p]) {
                return false;
            }
        }

        return true;
    }

public:
    explicit ChainConstruction(int n) : n(n) {
        L.assign(n + 1, 0);
        U.assign(n + 1, 0);
        chosen.assign(n + 1, false);
        need.assign(n + 1, 0);

        for (int p = 1; p <= n; p += 2) {
            odd.push_back(p);

            // 最大的 q，使 p * 2^q <= n。
            int q = 0;
            long long x = p;

            while (x * 2 <= n) {
                x *= 2;
                ++q;
            }

            L[p] = 0;
            U[p] = q;
        }
    }

    vector<int> solve() {
        vector<int> answer;

        // 从小到大枚举候选数字。
        for (int x = 1; x <= n; ++x) {
            int p = x;
            int q = 0;

            // x = p * 2^q，其中 p 为奇数。
            while ((p & 1) == 0) {
                p >>= 1;
                ++q;
            }

            // 该奇数链已经选过一个数。
            if (chosen[p]) {
                continue;
            }

            /*
                正常情况下 q 应该等于当前 L[p]。

                q < L[p]：这个候选此前已经被排除。
                q > L[p]：理论上顺序扫描时不会跳过中间指数；
                         这里保留判断以增强健壮性。
            */
            if (q < L[p] || q > U[p]) {
                continue;
            }

            int oldL = L[p];
            int oldU = U[p];

            // 临时固定 f[p] = q，即尝试选择 x。
            L[p] = q;
            U[p] = q;

            if (feasible()) {
                // 存在包含 x 的合法补全，贪心地选择 x。
                chosen[p] = true;
                answer.push_back(x);
            } else {
                /*
                    不存在 f[p] = q 的合法补全。

                    恢复上界，并排除当前指数 q。
                */
                L[p] = max(oldL, q + 1);
                U[p] = oldU;
            }
        }

        return answer;
    }
};

static bool checkAnswer(int n, const vector<int>& ans) {
    int expectedSize = (n + 1) / 2;

    if ((int)ans.size() != expectedSize) {
        return false;
    }

    for (int x : ans) {
        if (x < 1 || x > n) {
            return false;
        }
    }

    for (int i = 0; i < (int)ans.size(); ++i) {
        for (int j = i + 1; j < (int)ans.size(); ++j) {
            if (ans[j] % ans[i] == 0 || ans[i] % ans[j] == 0) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        ChainConstruction solver(n);
        vector<int> answer = solver.solve();

        cout << answer.size() << '\n';
        for (int i = 0; i < (int)answer.size(); ++i) {
            if (i) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';

        // 调试时可以使用：
        // assert(checkAnswer(n, answer));
    }

    return 0;
}