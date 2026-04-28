#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m;
int a[N];

namespace PST {
    struct Node {
        int sum;
        int l, r;
    };

    int num;
    int root[N];
    Node node[N << 5];
    
    int Build(int l, int r) {
        int p = ++num;
        if (l == r) {
            node[p].sum = a[l];
            return p;
        }
        int mid = l + r >> 1;
        node[p].l = Build(l, mid);
        node[p].r = Build(mid + 1, r);
        return p;
    }

    int Change(int l, int r, int pos, int val, int ver) {
        int p = ++num;
        node[p] = node[ver];
        if (l == r) {
            node[p].sum = val;
            return p;
        }
        int mid = l + r >> 1;
        if (pos <= mid) node[p].l = Change(l, mid, pos, val, node[ver].l);
        if (mid + 1 <= pos) node[p].r = Change(mid + 1, r, pos, val, node[ver].r);
        return p;
    }

    int Query(int l, int r, int pos, int ver) {
        if (l == r) return node[ver].sum;
        int mid = l + r >> 1;
        if (pos <= mid) return Query(l, mid, pos, node[ver].l);
        if (mid + 1 <= pos) return Query(mid + 1, r, pos, node[ver].r);
        return 0;
    }
} using namespace PST;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    root[0] = Build(1, n);
    for (int i = 1; i <= m; i++) {
        int ver, opt;
        cin >> ver >> opt;
        if (opt == 1) {
            int x, y;
            cin >> x >> y;
            root[i] = Change(1, n, x, y, root[ver]);
        }
        if (opt == 2) {
            int x;
            cin >> x;
            printf("%d\n", Query(1, n, x, root[ver]));
            root[i] = root[ver];
        }
    }
    return 0;
}