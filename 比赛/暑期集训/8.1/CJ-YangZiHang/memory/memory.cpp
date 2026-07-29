#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, m;
int ans[N];

struct SegmentTree {
    struct Node {
        int maxn;
    };

    Node node[N << 2];

    void Down(int x) {
        node[x << 1].maxn = node[x].maxn;
        node[x << 1 | 1].maxn = node[x].maxn;
        return;
    }
    void PushUp(int x) {
        node[x].maxn = max(node[x << 1].maxn, node[x << 1 | 1].maxn);
        return;
    }
    void Add(int x, int l, int r, const int L, const int R, int val) {
        if (L <= l && r <= R) {
            node[x].maxn = max(node[x].maxn, val);
            return;
        }
        Down(x);
        int mid = (l + r) >> 1;
        if (L <= mid) Add(x << 1, l, mid, L, R, val);
        else if (mid < R) Add(x << 1 | 1, mid + 1, r, L, R, val);
        PushUp(x);
    }
    int Query(int x, int l, int r, const int L, const int R) {
        if (L <= l && r <= R) {
            return node[x].maxn;
        }
        Down(x);
        int mid = (l + r) >> 1;
        if (R <= mid) return Query(x << 1, l, mid, L, R);
        else if (mid < L) return Query(x << 1 | 1, mid + 1, r, L, R);
        return max(Query(x << 1, l, mid, L, R), Query(x << 1 | 1, mid + 1, r, L, R));
    }
};

SegmentTree seg;

signed main() {
    freopen("memory.in", "r", stdin);
    freopen("memory.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            seg.Add(1, 1, n, l, r, k);
        }
        if (opt == 3) {
            int l, r;
            cin >> l >> r;
            printf("%d\n", seg.Query(1, 1, n, l, r));
        }
    }
    return 0;
}