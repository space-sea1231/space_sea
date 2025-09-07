#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;

namespace SegmentTree {
    struct Node {
        bool flag;
        int sum;
    };

    Node node[N << 2];

    void PushDown(int x, int l, int r) {
        if (node[x].flag == false) return;
        int mid = (l + r) >> 1;
        node[x].flag = false;
        node[x << 1].flag ^= true;
        node[x << 1].sum = mid - l + 1 - node[x << 1].sum;
        node[x << 1 | 1].flag ^= true;
        node[x << 1 | 1].sum = r - mid - node[x << 1 | 1].sum;
        return;
    }

    void PushUp(int x) {
        node[x].sum = node[x << 1].sum + node[x << 1 | 1].sum;
        return;
    }

    void Change(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            node[x].flag ^= true;
            node[x].sum = r - l + 1 - node[x].sum;
            return;
        }
        PushDown(x, l, r);
        int mid = (l + r) >> 1;
        if (mid >= L) Change(x << 1, l, mid, L, R);
        if (mid < R) Change(x << 1 | 1, mid + 1, r, L, R);
        PushUp(x);
        return;
    }

    int Query(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) return node[x].sum;
        PushDown(x, l, r);
        int mid = (l + r) >> 1, ans = 0;
        if (mid >= L) ans += Query(x << 1, l, mid, L, R);
        if (mid < R) ans += Query(x << 1 | 1, mid + 1, r, L, R);
        return ans;
    }
}

using namespace SegmentTree;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if (opt == 0) Change(1, 1, n, l, r);            
        else if (opt == 1) printf("%d\n", Query(1, 1, n, l, r));
    }
    return 0;
}