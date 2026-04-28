#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m;
int a[N], tmp[N];

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
        if (l == r) return p;
        int mid = l + r >> 1;
        node[p].l = Build(l, mid);
        node[p].r = Build(mid + 1, r);
        return p;
    }

    int Change(int l, int r, int pos, int ver) {
        int p = ++num;
        node[p] = node[ver];
        node[p].sum++;
        if (l == r) return p;
        int mid = l + r >> 1;
        if (pos <= mid) node[p].l = Change(l, mid, pos, node[ver].l);
        if (mid + 1 <= pos) node[p].r = Change(mid + 1, r, pos, node[ver].r);
        return p;
    }

    int Query(int l, int r, int pos, int verl, int verr) {
        if (l == r) return l;
        int mid = l + r >> 1, x = node[node[verr].l].sum - node[node[verl].l].sum;
        if (x >= pos) return Query(l, mid, pos, node[verl].l, node[verr].l);
        else return Query(mid + 1, r, pos - x, node[verl].r, node[verr].r);
    }
} using namespace PST;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp[i] = a[i];
    }
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    root[0] = Build(1, len);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(tmp + 1, tmp + len + 1, a[i]) - tmp;
        // printf("a[%d]=%d\n", i, a[i]);
        root[i] = Change(1, n, a[i], root[i - 1]);
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        printf("%d\n", tmp[Query(1, n, k, root[l - 1], root[r])]);
    }
    return 0;
}