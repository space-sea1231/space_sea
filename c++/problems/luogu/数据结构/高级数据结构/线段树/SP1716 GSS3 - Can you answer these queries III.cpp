#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e4 + 10;
const int INF = 0x3f3f3f3f;

int n, q;
int a[N];

struct SegmentTree {
    struct Node {
        int sum;
        int ans;
        int lsum, rsum;
    };
    
    Node node[N << 2];
    
    Node PushUp(const Node L, const Node R) {
        Node tmp;
        tmp.sum = L.sum + R.sum;
        tmp.lsum = max(L.lsum, L.sum + R.lsum);
        tmp.rsum = max(R.rsum, R.sum + L.rsum);
        tmp.ans = max(max(L.ans, R.ans), L.rsum + R.lsum);
        return tmp;
    }

    void Build(int x, int l, int r) {
        if (l == r) {
            node[x].sum = a[l];
            node[x].ans = a[l];
            node[x].lsum = node[x].rsum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(x << 1, l, mid);
        Build(x << 1 | 1, mid + 1, r);
        node[x] = PushUp(node[x << 1], node[x << 1 | 1]);        
        return;
    }

    void Change(int x, int l, int r, int pos, int val) {
        if (l == r) {
            node[x].sum = val;
            node[x].ans = val;
            node[x].lsum = node[x].rsum = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) Change(x << 1, l, mid, pos, val);
        else if (pos > mid) Change(x << 1 | 1, mid + 1, r, pos, val);
        node[x] = PushUp(node[x << 1], node[x << 1 | 1]);
        return;
    }

    Node Query(int x, int l, int r, const int L, const int R) {
        if (L <= l && r <= R) return node[x];
        int mid = (l + r) >> 1;
        if (R <= mid) return Query(x << 1, l, mid, L, R);
        if (L > mid) return Query(x << 1 | 1, mid + 1, r, L, R);
        return PushUp(Query(x << 1, l, mid, L, R), Query(x << 1 | 1, mid + 1, r, L, R));
    }
};

SegmentTree seg;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    seg.Build(1, 1, n);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 0) seg.Change(1, 1, n, x, y);
        if (opt == 1) printf("%d\n", seg.Query(1, 1, n, x, y).ans);
    }
    return 0;
}