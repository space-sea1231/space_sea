#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

class Fenwick {
private:
    int n;
    vector<ull> tree;

public:
    explicit Fenwick(int n = 0) : n(n), tree(n + 1, 0) {}

    void add(int position, ull value) {
        for (int i = position; i <= n; i += i & -i) {
            tree[i] += value;
        }
    }

    ull query(int position) const {
        ull result = 0;

        for (int i = position; i > 0; i -= i & -i) {
            result += tree[i];
        }

        return result;
    }
};

class RangeFenwick {
private:
    int n;
    Fenwick coefficient;
    Fenwick constant;

    ull prefixSum(int position) const {
        if (position <= 0) {
            return 0;
        }

        return coefficient.query(position) *
                   static_cast<ull>(position)
               - constant.query(position);
    }

public:
    explicit RangeFenwick(int n = 0)
        : n(n), coefficient(n), constant(n) {}

    void rangeAdd(int left, int right, ull value) {
        coefficient.add(left, value);
        constant.add(
            left,
            value * static_cast<ull>(left - 1)
        );

        if (right < n) {
            ull negativeValue = 0ULL - value;

            coefficient.add(right + 1, negativeValue);
            constant.add(
                right + 1,
                negativeValue * static_cast<ull>(right)
            );
        }
    }

    ull rangeSum(int left, int right) const {
        return prefixSum(right) - prefixSum(left - 1);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<ull> prefixA(n + 1, 0);
    vector<ull> prefixB(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        ull a, b;
        cin >> a >> b;

        prefixA[i] = prefixA[i - 1] + a;
        prefixB[i] = prefixB[i - 1] + b;
    }

    RangeFenwick addedCoefficient(n);
    RangeFenwick addedConstant(n);

    for (ull day = 1; day <= static_cast<ull>(m); ++day) {
        int type, left, right;
        cin >> type >> left >> right;

        if (type == 1) {
            ull value;
            cin >> value;

            addedCoefficient.rangeAdd(left, right, value);
            addedConstant.rangeAdd(
                left,
                right,
                0ULL - day * value
            );
        } else {
            ull initialA =
                prefixA[right] - prefixA[left - 1];

            ull initialB =
                prefixB[right] - prefixB[left - 1];

            ull extraCoefficient =
                addedCoefficient.rangeSum(left, right);

            ull extraConstant =
                addedConstant.rangeSum(left, right);

            ull answer =
                initialA
                + day * initialB
                + day * extraCoefficient
                + extraConstant;

            cout << answer << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}

