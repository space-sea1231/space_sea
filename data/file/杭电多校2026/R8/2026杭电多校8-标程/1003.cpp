#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAX_N = 100000;
const int B = 320;

int fac[MAX_N + 1], ifac[MAX_N + 1];

int powerMod(int a, int b) {
    int result = 1;

    while (b) {
        if (b & 1) {
            result = 1LL * result * a % MOD;
        }
        a = 1LL * a * a % MOD;
        b >>= 1;
    }

    return result;
}

void initCombinations() {
    fac[0] = 1;

    for (int i = 1; i <= MAX_N; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }

    ifac[MAX_N] = powerMod(fac[MAX_N], MOD - 2);

    for (int i = MAX_N; i >= 1; --i) {
        ifac[i - 1] = 1LL * ifac[i] * i % MOD;
    }
}

int combination(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }

    return 1LL * fac[n] * ifac[k] % MOD
         * ifac[n - k] % MOD;
}

int calculateByFormula(int length, int distance) {
    if (length <= 0) {
        return 1;
    }

    int result = 1;

    for (int selected = 1;
         1LL + 1LL * (selected - 1) * distance <= length;
         ++selected) {
        int available =
            length - (selected - 1) * (distance - 1);

        result += combination(available, selected);

        if (result >= MOD) {
            result -= MOD;
        }
    }

    return result;
}

struct Query {
    int x;
    int k;
};

void solve() {
    int n, q;
    cin >> n >> q;

    int smallLimit = min(B, n);

    vector<Query> queries(q);
    vector<vector<int>> groups(smallLimit + 1);

    for (int i = 0; i < q; ++i) {
        cin >> queries[i].x >> queries[i].k;

        if (queries[i].k <= smallLimit) {
            groups[queries[i].k].push_back(i);
        }
    }

    vector<int> answer(q);
    vector<int> dp(n + 1);
    vector<int> totalByK(n + 1, -1);

    for (int k = 1; k <= smallLimit; ++k) {
        if (groups[k].empty()) {
            continue;
        }

        dp[0] = 1;

        for (int length = 1; length <= n; ++length) {
            int chooseLast =
                length >= k ? dp[length - k] : 1;

            dp[length] = dp[length - 1] + chooseLast;

            if (dp[length] >= MOD) {
                dp[length] -= MOD;
            }
        }

        for (int id : groups[k]) {
            int x = queries[id].x;
            int leftLength = max(0, x - k);
            int rightLength = max(0, n - x - k + 1);

            int containingX =
                1LL * dp[leftLength] * dp[rightLength] % MOD;

            answer[id] = dp[n] - containingX;

            if (answer[id] < 0) {
                answer[id] += MOD;
            }
        }
    }

    for (int id = 0; id < q; ++id) {
        int x = queries[id].x;
        int k = queries[id].k;

        if (k <= smallLimit) {
            continue;
        }

        int leftLength = max(0, x - k);
        int rightLength = max(0, n - x - k + 1);

        if (totalByK[k] == -1) {
            totalByK[k] = calculateByFormula(n, k);
        }

        int left = calculateByFormula(leftLength, k);
        int right = calculateByFormula(rightLength, k);

        int containingX = 1LL * left * right % MOD;

        answer[id] = totalByK[k] - containingX;

        if (answer[id] < 0) {
            answer[id] += MOD;
        }
    }

    for (int value : answer) {
        cout << value << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    initCombinations();

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
