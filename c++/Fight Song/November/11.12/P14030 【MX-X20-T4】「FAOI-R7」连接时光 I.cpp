#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Fenwick {
    int n;
    vector<int> tree;

    explicit Fenwick(int n) : n(n), tree(n + 1) {
        // 初始时 1~n 每个数字都还存在，出现次数均为 1。
        for (int i = 1; i <= n; ++i) {
            tree[i] = i & -i;
        }
    }

    void add(int x, int delta) {
        for (; x <= n; x += x & -x) {
            tree[x] += delta;
        }
    }

    // 返回当前剩余数字中第 k 小的数字。
    int kth(int k) const {
        int pos = 0;
        int step = 1;
        while ((step << 1) <= n) step <<= 1;

        for (; step; step >>= 1) {
            int nxt = pos + step;
            if (nxt <= n && tree[nxt] < k) {
                pos = nxt;
                k -= tree[nxt];
            }
        }

        return pos + 1;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n + 1);
    vector<int> recallyears(n + 1, 0);
    vector<int> suffixBest(n + 2, 0);
    vector<int> p(n + 1);

    int r = 1;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];

        if (a[i] >= 0) {
            recallyears[i] = i - 1;
            r = i;
        }
    }

    // suffixBest[i]：a[i...n] 中最大值的位置。
    suffixBest[n] = n;
    for (int i = n - 1; i >= 1; --i) {
        int j = suffixBest[i + 1];
        suffixBest[i] = (a[i] >= a[j] ? i : j);
    }

    // 覆盖尚未覆盖的负数后缀。
    for (int x = r; x < n; ) {
        int j = suffixBest[x + 1];
        recallyears[j] = j - x;
        x = j;
    }

    ll answer = 0;
    for (int i = 1; i <= n; ++i) {
        answer += a[i] * recallyears[i];
    }

    // 根据逆序计数还原排列。
    Fenwick bit(n);

    for (int i = n; i >= 1; --i) {
        int rank = i - recallyears[i];
        p[i] = bit.kth(rank);
        bit.add(p[i], -1);
    }

    cout << answer << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << p[i] << (i == n ? '\n' : ' ');
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