#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

struct Fenwick {
    int n = 0;
    vector<int> tree;

    Fenwick() = default;
    explicit Fenwick(int n_) {
        reset_size(n_);
    }

    void reset_size(int n_) {
        n = n_;
        tree.assign(n + 1, 0);
    }

    void clear() {
        fill(tree.begin(), tree.end(), 0);
    }

    void add(int index, int value) {
        for (++index; index <= n; index += index & -index) {
            tree[index] += value;
        }
    }

    int sum_prefix(int count) const {
        int result = 0;
        for (int index = count; index > 0; index -= index & -index) {
            result += tree[index];
        }
        return result;
    }
};

int main() {
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r;
    int64 k;
    cin >> n >> r >> k;

    vector<int64> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }

    vector<int64> sa(n + 1), sb(n + 1), sc(n + 1);
    for (int i = 1; i <= n; ++i) {
        sa[i] = sa[i - 1] + a[i];
        sb[i] = sb[i - 1] + b[i];
        sc[i] = sc[i - 1] + c[i];
    }

    const int starts = n - r + 1;
    vector<int64> f(starts), g(starts), h(starts);
    for (int i = 0; i < starts; ++i) {
        f[i] = sa[i] - sb[i] + sb[i + r] - sa[i + r];
        g[i] = sb[i] - sc[i] + sb[i + r] - sa[i + r];
        h[i] = sa[i] - sb[i] + sc[i + r] - sb[i + r];
    }

    vector<int64> values_f = f;
    vector<int64> values_h = h;
    sort(values_f.begin(), values_f.end());
    values_f.erase(unique(values_f.begin(), values_f.end()), values_f.end());
    sort(values_h.begin(), values_h.end());
    values_h.erase(unique(values_h.begin(), values_h.end()), values_h.end());

    vector<int> rank_f(starts), rank_h(starts);
    for (int i = 0; i < starts; ++i) {
        rank_f[i] = (int)(lower_bound(values_f.begin(), values_f.end(), f[i]) - values_f.begin());
        rank_h[i] = (int)(lower_bound(values_h.begin(), values_h.end(), h[i]) - values_h.begin());
    }

    Fenwick bit_f((int)values_f.size()), bit_h((int)values_h.size());

    auto count_not_greater = [&](int64 answer) {
        const int64 limit = answer - sa[n];
        int64 count = 0;

        bit_f.clear();
        for (int i = 0; i < starts; ++i) {
            int add_pos = i - r;
            if (add_pos >= 0) {
                bit_f.add(rank_f[add_pos], 1);
            }
            int allowed = (int)(upper_bound(values_f.begin(), values_f.end(), limit - f[i]) - values_f.begin());
            count += bit_f.sum_prefix(allowed);
            if (count >= k) {
                return count;
            }
        }

        bit_h.clear();
        for (int i = 0; i < starts; ++i) {
            if (i - 1 >= 0) {
                bit_h.add(rank_h[i - 1], 1);
            }
            if (i - r >= 0) {
                bit_h.add(rank_h[i - r], -1);
            }
            int allowed = (int)(upper_bound(values_h.begin(), values_h.end(), limit - g[i]) - values_h.begin());
            count += bit_h.sum_prefix(allowed);
            if (count >= k) {
                return count;
            }
        }

        return count;
    };

    int64 low = 0;
    int64 high = sc[n];
    while (low < high) {
        int64 mid = low + (high - low) / 2;
        if (count_not_greater(mid) >= k) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << low << '\n';
    return 0;
}
