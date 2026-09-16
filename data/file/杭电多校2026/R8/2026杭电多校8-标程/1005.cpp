#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

const int64 MOD = 1000000007LL;

struct Run {
    int start;
    int length;
    int bit;
};

struct SideInfo {
    vector<int> need;
    vector<int64> minimum;
};

static SideInfo buildSide(
    const vector<int64> &cost,
    const vector<int> &rank,
    int K,
    bool takeLeft
) {
    int N = static_cast<int>(cost.size()) - 1;

    SideInfo result;
    result.need.resize(K);
    result.minimum.resize(K);

    int maximumRank = 0;
    int64 minimumCost = (1LL << 62);

    for (int d = 0; d < K; ++d) {
        int position = takeLeft ? d + 1 : N - d;

        maximumRank = max(maximumRank, rank[position]);
        minimumCost = min(minimumCost, cost[position]);

        result.need[d] = maximumRank - d;
        result.minimum[d] = minimumCost;
    }

    return result;
}

static int64 calculateCorrection(
    const vector<Run> &runs,
    const SideInfo &side,
    const vector<int64> &rankValue,
    const vector<int64> &rankPrefix,
    int K
) {
    int block = static_cast<int>(sqrt(K)) + 1;
    int64 answer = 0;

    // Entirely contained in one equal-character run.
    for (const Run &run : runs) {
        if (run.bit != (&side == nullptr)) {
            // This condition is intentionally unused; runs are filtered outside.
        }

        int required = side.need[0];
        int64 minimumCost = side.minimum[0];

        for (int length = max(1, required);
             length <= run.length;
             ++length) {
            int64 difference =
                (minimumCost - rankValue[length + 1]) % MOD;
            int64 count = run.length - length + 1;

            answer = (
                answer + difference % MOD * (count % MOD)
            ) % MOD;
        }
    }

    vector<const Run *> shortRuns;
    vector<const Run *> longRuns;

    for (const Run &run : runs) {
        if (run.length < block) {
            shortRuns.push_back(&run);
        } else {
            longRuns.push_back(&run);
        }
    }

    // For short runs, fix the length inside the last run and build
    // prefix sums over d.
    vector<int64> prefix(K + 1);

    for (int r = 1; r < block; ++r) {
        prefix[0] = 0;

        for (int d = 1; d <= K - r; ++d) {
            int64 value = 0;

            if (side.need[d] <= r) {
                value =
                    side.minimum[d] - rankValue[d + r + 1];
                value %= MOD;
            }

            prefix[d] = (prefix[d - 1] + value) % MOD;
        }

        for (int d = K - r + 1; d <= K; ++d) {
            prefix[d] = prefix[d - 1];
        }

        for (const Run *run : shortRuns) {
            if (run->length >= r) {
                int D = run->start - 1;
                answer += prefix[D];
                answer %= MOD;
            }
        }
    }

    // There are at most O(K / block) long runs. For each one,
    // sum all d using value-prefix sums.
    for (const Run *run : longRuns) {
        int length = run->length;
        int D = run->start - 1;

        for (int d = 1; d <= D; ++d) {
            int first = max(1, side.need[d]);

            if (first > length) {
                continue;
            }

            int64 count = length - first + 1;
            int64 value =
                (count % MOD) * (side.minimum[d] % MOD) % MOD;

            int left = d + first + 1;
            int right = d + length + 1;

            int64 removed =
                (rankPrefix[right] - rankPrefix[left - 1]) % MOD;

            value = (value - removed) % MOD;
            answer = (answer + value) % MOD;
        }
    }

    return (answer % MOD + MOD) % MOD;
}

static int64 solveCase(
    int N,
    int K,
    const vector<int64> &cost,
    const string &A
) {
    vector<int> order(N);
    iota(order.begin(), order.end(), 1);

    sort(order.begin(), order.end(), [&](int x, int y) {
        if (cost[x] != cost[y]) {
            return cost[x] > cost[y];
        }
        return x < y;
    });

    vector<int> rank(N + 1);
    vector<int64> rankValue(N + 1);
    vector<int64> topSum(K + 1);

    for (int i = 1; i <= N; ++i) {
        int position = order[i - 1];
        rank[position] = i;
        rankValue[i] = cost[position];

        if (i <= K) {
            topSum[i] =
                (topSum[i - 1] + rankValue[i]) % MOD;
        }
    }

    vector<int64> rankPrefix(N + 1);
    for (int i = 1; i <= N; ++i) {
        rankPrefix[i] =
            (rankPrefix[i - 1] + rankValue[i]) % MOD;
    }

    int64 answer = 0;

    for (int length = 1; length <= K; ++length) {
        int64 count = K - length + 1;
        answer = (
            answer + topSum[length] * (count % MOD)
        ) % MOD;
    }

    vector<Run> zeroRuns;
    vector<Run> oneRuns;

    for (int left = 0; left < K;) {
        int right = left;
        while (right < K && A[right] == A[left]) {
            ++right;
        }

        Run run{
            left + 1,
            right - left,
            A[left] - '0'
        };

        if (run.bit == 0) {
            zeroRuns.push_back(run);
        } else {
            oneRuns.push_back(run);
        }

        left = right;
    }

    SideInfo leftSide = buildSide(cost, rank, K, true);
    SideInfo rightSide = buildSide(cost, rank, K, false);

    int64 correction = 0;

    correction += calculateCorrection(
        oneRuns,
        leftSide,
        rankValue,
        rankPrefix,
        K
    );
    correction %= MOD;

    correction += calculateCorrection(
        zeroRuns,
        rightSide,
        rankValue,
        rankPrefix,
        K
    );
    correction %= MOD;

    answer = (answer - correction) % MOD;
    return (answer + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<int64> cost(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> cost[i];
        }

        string A;
        cin >> A;

        cout << solveCase(N, K, cost, A) << '\n';
    }

    return 0;
}
