#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m, o;
int a[N], b[N];
int opt[N], x[N], y[N];

namespace SegmentTree {
    struct Node {
        int sum;
        int vis = -1;
    };

    Node node[N << 2];

    void Build(int x, int l, int r) {
        if (l == r) {
            node[x].sum = b[l];
            return;
        }
        int mid = l + r >> 1;
        Build(x << 1, l, mid);
        Build(x << 1 | 1, mid + 1, r);
        node[x].sum = node[x << 1].sum + node[x << 1 | 1].sum;
        node[x].vis = -1;
    }

    void Down(int x, int l, int r) {
        if (node[x].vis == -1) return;
        int mid = l + r >> 1;
        node[x << 1].sum = node[x].vis * (mid - l + 1);
        node[x << 1 | 1].sum = node[x].vis * (r - mid);
        node[x << 1].vis = node[x].vis;
        node[x << 1 | 1].vis = node[x].vis;
        node[x].vis = -1;
    }
    int Query(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) return node[x].sum;
        Down(x, l, r);
        int mid = l + r >> 1, sum = 0;
        if (L <= mid) sum += Query(x << 1, l, mid, L, R);
        if (mid + 1 <= R) sum += Query(x << 1 | 1, mid + 1, r, L, R);
        return sum;
    }
    
    void Change(int x, int l, int r, int L, int R, int val) {
        if (L > R) return;
        if (L <= l && r <= R) {
            node[x].vis = val;
            node[x].sum = (r - l + 1) * val;
            return ;
        }
        Down(x, l, r);
        int mid = l + r >> 1;
        if (L <= mid) Change(x << 1, l, mid, L, R, val);
        if (mid + 1 <= R) Change(x << 1 | 1, mid + 1, r, L, R, val);
        node[x].sum = node[x << 1].sum + node[x << 1 | 1].sum;
    }
} using namespace SegmentTree;

bool Check(int mid) {
    for (int i = 1; i <= n; i++) b[i] = (a[i] >= mid);
    Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int sum = Query(1, 1, n, x[i], y[i]);
        if (opt[i] == 0) {
            Change(1, 1, n, x[i], y[i] - sum, 0);
            Change(1, 1, n, y[i] - sum + 1, y[i], 1);
        }
        else {
            Change(1, 1, n, x[i], x[i] + sum - 1, 1);
            Change(1, 1, n, x[i] + sum, y[i], 0);
        }
    }
    return Query(1, 1, n, o, o);
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> opt[i] >> x[i] >> y[i];
    cin >> o;
    int l = 1, r = n, ans = 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (Check(mid)) {
            l = mid + 1;
            ans = mid;
        }
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
/*
010111
*/