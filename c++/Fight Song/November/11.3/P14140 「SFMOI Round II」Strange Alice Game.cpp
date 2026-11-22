    #include <bits/stdc++.h>
    using namespace std;

    struct BIT {
        int n;
        vector<int> t;
        BIT(int n) : n(n), t(n + 1, 0) {}
        void add(int i, int v) {
            for (; i <= n; i += i & -i) t[i] += v;
        }
        int sum(int i) {
            int s = 0;
            for (; i > 0; i -= i & -i) s += t[i];
            return s;
        }
        // 树状数组上二分，找第 k 个 1 的位置
        int kth(int k) {
            int pos = 0;
            int pw = 1;
            while (pw <= n) pw <<= 1;
            for (pw >>= 1; pw; pw >>= 1) {
                if (pos + pw <= n && t[pos + pw] < k) {
                    pos += pw;
                    k -= t[pos];
                }
            }
            return pos + 1;
        }
    };

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        
        int n, k, q;
        cin >> n >> k >> q;
        vector<int> a(n + 1);
        vector<int> idx(n);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            idx[i - 1] = i;
        }

        // 1. 求 L_i
        sort(idx.begin(), idx.end(), [&](int x, int y) {
            return a[x] < a[y];
        });
        vector<int> L(n + 1);
        BIT bit(n);
        for (int i : idx) {
            int cnt = bit.sum(i - 1);
            if (cnt < k) {
                L[i] = 1;
            } else {
                int p = bit.kth(cnt - k + 1);
                L[i] = p + 1;
            }   
            bit.add(i, 1);
        }

        // 2. 处理询问
        vector<tuple<int, int, int>> queries(q);
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            queries[i] = {l, r, i};
        }
        sort(queries.begin(), queries.end()); // 按 l 排序

        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 1);
        sort(ord.begin(), ord.end(), [&](int x, int y) {
            return L[x] < L[y];
        });

        BIT bit2(n);
        vector<int> ans(q);
        int ptr = 0;
        for (auto [l, r, id] : queries) {
            while (ptr < n && L[ord[ptr]] <= l) {
                bit2.add(ord[ptr], 1);
                ++ptr;
            }
            ans[id] = bit2.sum(r) - bit2.sum(l - 1);
        }

        for (int i = 0; i < q; ++i) {
            cout << ans[i] << '\n';
        }

        return 0;
    }