#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

class Fenwick {
private:
    int n;
    vector<int> tree;

public:
    Fenwick() : n(0) {}

    explicit Fenwick(int n) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        tree.assign(n + 1, 0);
    }

    void add(int pos, int value) {
        // 外部坐标为 0-based
        ++pos;
        for (int i = pos; i <= n; i += i & -i) {
            tree[i] += value;
        }
    }

    // 返回坐标 [0, pos] 的和，pos 为 0-based
    int prefixSum(int pos) const {
        if (pos < 0) return 0;

        ++pos;
        int result = 0;
        for (int i = pos; i > 0; i -= i & -i) {
            result += tree[i];
        }
        return result;
    }
};

/*
 * 计算：
 * result[i] = #{j | X[j] > X[i] 且 Y[j] > Y[i]}
 */
vector<int64> countGreater2D(const vector<int>& X,
                             const vector<int>& Y) {
    int n = static_cast<int>(X.size());

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [&](int lhs, int rhs) {
        return X[lhs] > X[rhs];
    });

    Fenwick bit(n);
    vector<int64> result(n, 0);

    int inserted = 0;

    for (int id : order) {
        // 已插入的点全部满足 X[j] > X[id]
        // Y[j] > Y[id] 的数量：
        // inserted - #{Y[j] <= Y[id]}
        result[id] = inserted - bit.prefixSum(Y[id]);

        bit.add(Y[id], 1);
        ++inserted;
    }

    return result;
}

/*
 * 计算：
 * result[i] =
 * #{j | A[j] > A[i], B[j] > B[i], C[j] > C[i]}
 *
 * 首先按照 A 从大到小排序。
 * 然后用 CDQ 分治统计前面的点中 B、C 均更大的点。
 */
vector<int64> countGreater3D(const vector<int>& A,
                             const vector<int>& B,
                             const vector<int>& C) {
    int n = static_cast<int>(A.size());

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [&](int lhs, int rhs) {
        return A[lhs] > A[rhs];
    });

    vector<int> temp(n);
    vector<int64> result(n, 0);
    Fenwick bit(n);

    auto cdq = [&](auto&& self, int left, int right) -> void {
        if (left >= right) return;

        int mid = (left + right) >> 1;

        self(self, left, mid);
        self(self, mid + 1, right);

        /*
         * 递归结束后：
         * order[left..mid] 和 order[mid+1..right]
         * 分别已经按照 B 从大到小排列。
         *
         * 左半部分的点在原始 A 顺序中更靠前，
         * 因此一定满足 A[left-point] > A[right-point]。
         */
        int pointer = left;
        int inserted = 0;

        for (int i = mid + 1; i <= right; ++i) {
            int rightId = order[i];

            while (pointer <= mid &&
                   B[order[pointer]] > B[rightId]) {
                bit.add(C[order[pointer]], 1);
                ++pointer;
                ++inserted;
            }

            // 已加入的点都满足 B 更大。
            // 再统计其中 C 更大的点。
            result[rightId] +=
                inserted - bit.prefixSum(C[rightId]);
        }

        // 撤销树状数组中的修改
        for (int i = left; i < pointer; ++i) {
            bit.add(C[order[i]], -1);
        }

        // 将两个按照 B 降序排列的区间归并
        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j <= right) {
            if (B[order[i]] > B[order[j]]) {
                temp[k++] = order[i++];
            } else {
                temp[k++] = order[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = order[i++];
        }

        while (j <= right) {
            temp[k++] = order[j++];
        }

        for (int p = left; p <= right; ++p) {
            order[p] = temp[p];
        }
    };

    cdq(cdq, 0, n - 1);

    return result;
}

int64 choose2(int64 x) {
    if (x < 2) return 0;
    return x * (x - 1) / 2;
}

int64 choose3(int64 x) {
    if (x < 3) return 0;
    return x * (x - 1) * (x - 2) / 6;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int> A(n), B(n), C(n);

        for (int& x : A) cin >> x;
        for (int& x : B) cin >> x;
        for (int& x : C) cin >> x;

        vector<int64> dAB = countGreater2D(A, B);
        vector<int64> dAC = countGreater2D(A, C);
        vector<int64> dBC = countGreater2D(B, C);
        vector<int64> dABC = countGreater3D(A, B, C);

        // U 为空时产生 (n,n,n)
        int64 answer = 1;

        // 恰好一个见证点
        answer += n;

        // 恰好两个见证点
        int64 twoWitnesses = choose2(n);
        for (int i = 0; i < n; ++i) {
            twoWitnesses -= dABC[i];
        }
        answer += twoWitnesses;

        // 恰好三个见证点
        int64 threeWitnesses = choose3(n);

        for (int i = 0; i < n; ++i) {
            threeWitnesses -= choose2(dAB[i]);
            threeWitnesses -= choose2(dAC[i]);
            threeWitnesses -= choose2(dBC[i]);

            threeWitnesses += 2 * choose2(dABC[i]);
        }

        answer += threeWitnesses;

        cout << answer << '\n';
    }

    return 0;
}